/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* TODO:
    - Add menu statemanager
    - Implement current functionalities as tasks, attach to menu state manager
    - Change sec counter to UNIX timestamp. Saves so much fuss and potential bugs. Requires:
        + UNIX timestamp startpoint
        + Menu: checking valid time/date, valid UNIX
        + Get/Set Time/Date rewrite
        + Changing setting of timer
        + Calibrate time from RTC rewrite
    - Add alarm functionality
    - (Optional) Add proper error reporting to queue
    - (Optional) Add sync for internal timekeeping
*/
//#define QUEUE_DEBUG
//#define QUEUE_LOGGING  

#define LCD_WIDTH   (160)
#define LCD_HEIGHT  (128)
#define MAX_ALARMS  (20)

#include "project.h"
#include "..\Schakelklok.cydsn\Schakelklok_types.h"
#include "Schakelklok_RTC.h"
#include "Schakelklok_gfx.h"
#include "gfx_fonts.h"
#include "Schakelklok_display.h"
#include "Schakelklok_queue.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



// ========================================
//  TASK DECLARATIONS
// ========================================
typedef struct {
    uint32_t CyPins_ID;
    FUNC_QUEUE_T* queue;
} LED_args_t;
FUNC_ERRCODE_T LED_args_destructor(void* LED_args){
    free(LED_args);
    return ERRCODE_OK;
}
FUNC_ERRCODE_T setLED(void* LED_args);
FUNC_ERRCODE_T clearLED(void* LED_args);

FUNC_ERRCODE_T button_back();
FUNC_ERRCODE_T button_forward();
FUNC_ERRCODE_T button_up();
FUNC_ERRCODE_T button_down();

//FUNC_ERRCODE_T updateDisplay(GFX_OBJ_T* display_obj);

// ========================================
//  FUNCTION DECLARATIONS
// ========================================
FUNC_ERRCODE_T getTime_internal(TIME_T* time_ptr);
FUNC_ERRCODE_T getDate_internal(DATE_T* date_ptr);
void UI_modify_date(DATE_T* date, BUTTON_T button, uint8_t index);
void UI_modify_time(TIME_T* time, BUTTON_T button, uint8_t index);
uint32_t time_to_unix(TIME_T time);

FUNC_ERRCODE_T newAlarm(ALARM_T alarm, ALARM_T* list);

#define HANDLERFUNCS {setLED, clearLED}
#define HANDLERNAMES {"UNDEFINED", "setLED", "clearLED"}
void queueLogger(QUEUE_LOG_DATA_T* log);

uint8_t max_u8(uint8_t a, uint8_t b);
uint8_t min_u8(uint8_t a, uint8_t b);
void bound_u8(uint8_t* x, uint8_t a, uint8_t b);
uint16_t max_u16(uint16_t a, uint16_t b);
uint16_t min_u16(uint16_t a, uint16_t b);
void bound_u16(uint16_t* x, uint16_t a, uint16_t b);

const UWORD dispBuf_array[LCD_WIDTH * LCD_HEIGHT];

// ========================================
// Interrupts
// ========================================
volatile TIME_T SYSTIME_G;
volatile DATE_T SYSDATE_G;

volatile ALARM_T ALARM_ARR_G[MAX_ALARMS];
volatile ALARM_LINKEDLIST_T* ALARMS_TODAY_G;
// ----------------------------------------
//   Millisecond calibration interrupt
//      Gets capture value when 1s signal from RTC is passed, uses this to determine if counter is running too fast or too slow and adjusts counter period within accuracy margin to compensate.
// ----------------------------------------
CY_ISR(MS_CALIBRATION_INTVECT){
    // TODO add to queue
    MILLIS_COUNTER_CAPT_INT_ClearPending();
}

// ========================================
//   Debug defines
// ========================================
#ifdef QUEUE_DEBUG
    #define UART_DEBUG
#endif
void UART_print(char label[], int val, int radix);

// -========================================================-
//
//                          M A I N
//
// -========================================================-
int main(void)
{  
    // ========================================
    //   Interrupt setup
    // ========================================
    CyGlobalIntEnable; /* Enable global interrupts. */
    // Disable specific interrupts for setup
    MILLIS_COUNTER_CAPT_INT_Disable();
    // Set ms ctr to interrupt on capture
    MILLIS_COUNTER_CAPT_INT_SetVector(MS_CALIBRATION_INTVECT);
    SEC_CTR_TC_INT_SetVector(SEC_CTR_TC_INTVECT);
    
    // ========================================
    //   Communication setup
    // ========================================  
    I2C_Start();
    
    // ========================================
    //   RTC DEBUG
    // ======================================== 
    // 0 CTR_TC
    // 1 SQW edge
    MILLIS_CTR_CAPTSEL_Write(0x0);
    
    // ========================================
    //   Timekeeping and RTC setup
    // ========================================  
    Time_Init(&systime, &sysdate);    
    
    // ========================================
    //   Display
    // ========================================
    SPI_Module_Start();
    LCD_Init();
    
    
    DISPLAY_BUFFER_T displayBuffer;
    displayBuffer.buffer = dispBuf_array;
    displayBuffer.buffer_length = LCD_WIDTH * LCD_HEIGHT;
    displayBuffer.height = LCD_HEIGHT;
    displayBuffer.width = LCD_WIDTH;
    displayBuffer.index = 0;
    
    FONT8_T currFont;
    FONT8_T font_8x13_struct;
    font_8x13_struct.array = font_8x13;
    font_8x13_struct.name = font_8x13_name;
    font_8x13_struct.length = font_8x13_arraylength;
    font_8x13_struct.glyphs_total = font_8x13_glyphnum;
    font_8x13_struct.glyphcode_start_offset = -font_8x13_startGlyph;
    font_8x13_struct.glyph_width = font_8x13_width;
    font_8x13_struct.glyph_height = font_8x13_height;
    font_8x13_struct.glyph_size = font_8x13_height * font_8x13_width;   
    FONT8_T font_6x9_struct;
    font_6x9_struct.array = font_6x9;
    font_6x9_struct.name = font_6x9_name;
    font_6x9_struct.length = font_6x9_arraylength;
    font_6x9_struct.glyphs_total = font_6x9_glyphnum;
    font_6x9_struct.glyphcode_start_offset = -font_6x9_startGlyph;
    font_6x9_struct.glyph_width = font_6x9_width;
    font_6x9_struct.glyph_height = font_6x9_height;
    font_6x9_struct.glyph_size = font_6x9_height * font_6x9_width;   
    
    currFont = font_8x13_struct;
    
    // ========================================
    //   Task queue
    // ========================================
    Q_TASK_T taskQueue_array[QUEUE_MAXLENGTH];
    FUNC_QUEUE_T taskQueue;
    taskQueue.array = taskQueue_array;
    taskQueue.arrayLength = QUEUE_MAXLENGTH;
    taskQueue.headIndex = taskQueue.tailIndex = taskQueue.currLength = 0;

    FUNC_PTR_T handlerArray[] = HANDLERFUNCS;
    uint8_t handlerTotal = 3;
    char* handlerNames[] = HANDLERNAMES;  
    QUEUE_FUNCS_DATA_T funcData;
    funcData.amount = handlerTotal;
    funcData.names = handlerNames;
    funcData.ptrs = handlerArray;
    
    // ========================================
    //   Timing
    // ========================================
    TIME_T rtctime;
    DATE_T rtcdate;
    
    MILLIS_COUNTER_CAPT_INT_Enable();
    SEC_CTR_TC_INT_Enable();
    
    // ========================================
    //   Debug
    // ========================================
    #ifdef UART_DEBUG
    USBUART_Start(0, USBUART_5V_OPERATION);
    while(USBUART_GetConfiguration()==0);
    #endif
    
    char* strbuf[100];
    char* text = "Hello there!";
    uint8_t text_len = strlen(text);
    
    LED_args_t LEDarg = {DebugLED_Blu, &taskQueue};
    Q_TASK_T ledON;
    createTask(&ledON, setLED, NULL, &LEDarg);
    queue_addTask(&taskQueue, ledON);
    
    for(;;)
    {
        queue_handleTask(&taskQueue, &funcData, (FUNC_PTR_T)queueLogger);
        //CyDelay(500);
        /*
        if(BUTTONPRESS_REG_Read()){
            MILLIS_CTR_CAPTSEL_Write(~MILLIS_CTR_CAPTSEL_Read());
            DebugLED_Write(~DebugLED_Read());
        }
        
        if(MS_CALIB_FLAG){
            MS_CALIB_FLAG = 0;
            Time_CalibrateMillis();
        }*/
        
        /*
        if(INCR_TIME_FLAG){
            INCR_TIME_FLAG = 0;
            incrMins(&systime, &sysdate);
            DebugLED_Write(~DebugLED_Read());
        }
        
        clearBuffer(&displayBuffer, 0);
        currFont = font_8x13_struct;
        drawCircle(&displayBuffer, LCD_WIDTH/2, LCD_HEIGHT/2, 60, 0x005F, 1);
        drawString(&displayBuffer, LCD_WIDTH/2-(text_len * currFont.glyph_width)/2, LCD_HEIGHT/2-4, text, text_len, &currFont, 0xFFFF);

        
        systime.seconds = SEC_COUNTER_ReadCounter();
        systime.ms = GetMillis();
        
        rtctime.seconds = RTC_GetSeconds();
        rtctime.minutes = RTC_GetMinutes();
        rtctime.hours = RTC_GetHours();
        rtcdate.date = RTC_GetDate();
        rtcdate.day = RTC_GetDay();
        rtcdate.month = RTC_GetMonth();
        rtcdate.year = RTC_GetYear();
        rtctime.ms = 0;
        
        TimeToString(systime, strbuf);
        currFont = font_6x9_struct;
        drawString(&displayBuffer, 5 , 5, strbuf, strlen(strbuf), &currFont, 0xFFFF);
        DateToString(sysdate, strbuf);
        drawString(&displayBuffer, 5 , 15, strbuf, strlen(strbuf), &currFont, 0xFFFF);
        
        TimeToString(rtctime, strbuf);
        drawString(&displayBuffer, 5 , 25, strbuf, strlen(strbuf), &currFont, 0xF000);
        DateToString(rtcdate, strbuf);
        drawString(&displayBuffer, 5 , 35, strbuf, strlen(strbuf), &currFont, 0xF000);        
        
        
        LCD_TransferBuffer(0, 0, displayBuffer.width, displayBuffer.height, displayBuffer.buffer);
        
        CyDelay(50);
        */
    }
}

// ========================================
//  TASK DEFINITIONS
// ========================================
FUNC_ERRCODE_T setLED(void* LEDargs_vptr){
    LED_args_t* args = (LED_args_t*) LEDargs_vptr;
    CyPins_SetPin(args->CyPins_ID);
    
	Q_TASK_T task;
	LED_args_t* arg = (LED_args_t*)malloc(sizeof(LED_args_t));
    arg->CyPins_ID = args->CyPins_ID;
    arg->queue = args->queue;
	createTask(&task, clearLED, LED_args_destructor, (void*)arg);
	queue_addTask(args->queue, task);
    
    return ERRCODE_OK;
};
FUNC_ERRCODE_T clearLED(void* LEDargs_vptr){
    LED_args_t* args = (LED_args_t*) LEDargs_vptr;
    CyPins_ClearPin(args->CyPins_ID);
    
    Q_TASK_T task;
	LED_args_t* arg = (LED_args_t*)malloc(sizeof(LED_args_t));
    arg->CyPins_ID = args->CyPins_ID;
    arg->queue = args->queue;
	createTask(&task, setLED, LED_args_destructor, (void*)arg);
	queue_addTask(args->queue, task);
    
    return ERRCODE_OK;
}

FUNC_ERRCODE_T button_back();
FUNC_ERRCODE_T button_forward();
FUNC_ERRCODE_T button_up();
FUNC_ERRCODE_T button_down();

typedef struct{
    const UWORD** buffer;
    FUNC_ERRCODE_T(*sendToDisplay)(const UWORD** buffer);
} DISPLAY_OBJ_T;
FUNC_ERRCODE_T updateDisplay(DISPLAY_OBJ_T* display_obj);

// ========================================
//  FUCTION DEFINITIONS
// ========================================
uint8_t max_u8(uint8_t a, uint8_t b) {
    return (a > b ? a : b);
}
uint8_t min_u8(uint8_t a, uint8_t b) {
    return (a < b ? a : b);
}
void bound_u8(uint8_t* x, uint8_t a, uint8_t b) {
    *x = max_u8(a, min_u8(*x, b));
}
uint16_t max_u16(uint16_t a, uint16_t b){
    return (a > b ? a : b);
}
uint16_t min_u16(uint16_t a, uint16_t b){
    return (a < b ? a : b);
}
void bound_u16(uint16_t* x, uint16_t a, uint16_t b){
    *x = max_u16(a, min_u16(*x, b));
}

void UI_modify_date(DATE_T* date, BUTTON_T button, uint8_t index){
    switch (index) {
        case 0: date->date += (button == UP ? 10 : -10);        break;
        case 1: date->date += (button == UP ? 1 : -1);          break;
        case 2: date->month += (button == UP ? 10 : -10);       break; 
        case 3: date->month += (button == UP ? 1 : -1);         break;  
        case 4: date->year += (button == UP ? 1000 : -1000);    break; 
        case 5: date->year += (button == UP ? 100 : -100);      break;  
        case 6: date->year += (button == UP ? 10 : -10);        break;   
        case 7: date->year += (button == UP ? 1 : -1);          break;   
    }
    bound_u8(&date->date, 0, 39);
    bound_u8(&date->month, 1, 12);
    bound_u16(&date->year, 1970, 2037);// UNIX start/end dates :)
}

void UI_modify_time(TIME_T* time, BUTTON_T button, uint8_t index){
    switch (index) {
        case 0: time->hours += (button == UP ? 10 : -10);        break;
        case 1: time->hours += (button == UP ? 1 : -1);          break;
        case 2: time->minutes += (button == UP ? 10 : -10);       break; 
        case 3: time->minutes += (button == UP ? 1 : -1);         break;  
        case 4: time->seconds += (button == UP ? 10 : -10);      break;  
        case 5: time->seconds += (button == UP ? 1 : -1);        break;   
        case 6: time->ms += (button == UP ? 100 : -100);    break;  
        case 7: time->ms += (button == UP ? 10 : -10);    break; 
        case 8: time->ms += (button == UP ? 1 : -1);    break; 
    }
    bound_u8(&time->hours, 0, 23);
    bound_u8(&time->minutes, 0, 59);
    bound_u8(&time->seconds, 0, 59);
    bound_u16(&time->ms, 0, 999);    
}

uint32_t time_to_unix(TIME_T time){
    // TODO
}

FUNC_ERRCODE_T validateAlarm(ALARM_T alarm, ALARM_T* list){
    ALARM_T* comp;
    for(int i = 0; i < MAX_ALARMS; i++){
        comp = (list+i);
        if(alarm.days == comp->days && alarm.ms == comp->ms && alarm.time_unix == comp->time_unix){
            // Identical alarm already present
            return ERRCODE_FAIL;
        }
    }
    return ERRCODE_OK;    
}

FUNC_ERRCODE_T newAlarm(ALARM_T alarm, ALARM_T* list){
    ALARM_T* spot;
    ALARM_T* comp;
    for(int i = 0; i < MAX_ALARMS; i++){
        comp = (list+i);
        if(alarm.days == comp->days && alarm.ms == comp->ms && alarm.time_unix == comp->time_unix){
            // Identical alarm already present
            return ERRCODE_FAIL;
        }
        else{
            spot = (list+i);
        }
    }
    *spot = alarm;
    return ERRCODE_OK;
}

/*    
    DATETIME,
    MAINMENU,
    SETDATE,
    SETTIME,
    VIEW_DAYSELECT,
    VIEW_ALARMSELECT,
    VIEW_ALARMOPTIONS,
    NEWALARM,
    EDITALARM,
    DEBUGMENU,
    USBMENU
*/
FUNC_ERRCODE_T menuStateManager(MENU_T* menu, BUTTON_T button){
    MENUSTATE_T nextState;
    MENU_METADATA_T* meta = &menu->meta;
    
    switch(menu->state){
        // ============================= DATETIME ==============================
        case DATETIME:
            if(button == BACK){
                meta->index = 1;
                nextState = MAINMENU;
            }
            break;
        // ============================= MAINMENU ==============================
        case MAINMENU:
            if(button == UP){
                meta->index = max_u8(0, meta->index-1);
            }
            else if(button == DOWN){
                meta->index = min_u8(6, meta->index+1);
            }
            else if(button == BACK){
                /* DO NOTHING */
            }
            else if(button == FWD_OK){
                nextState = meta->index+1;
            }
            break;
        // ============================= SETDATE ==============================
        case SETDATE:
            switch(button){
                case UP:
                case DOWN:
                    UI_modify_date(&meta->newDate, button, meta->index);
                    break;
                case FWD_OK:
                    if(meta->index == 7){
                        if(validateDate(meta->newDate)){
                            meta->newDate.day = getDayOfWeek(meta->newDate);
                            SYSDATE_G = meta->newDate;
                            // TODO update internal UNIX counter
                            // TODO Schedule task to update date/time in RTC
                        }
                        else{
                            meta->errorCode = ERRCODE_RETRY;
                            meta->index = 0;
                        }
                    }
                    else{
                        meta->index++;
                    }
                    break;
                case BACK:                
                    if(meta->index == 0){
                        nextState = MAINMENU;
                    }
                    else{
                        meta->index--;
                    }
                    break;
            }
            break;
        // ============================= SETTIME ==============================
        case SETTIME:
            switch(button){
                case UP:
                case DOWN:
                    UI_modify_time(&meta->newTime, button, meta->index);
                    break;
                case FWD_OK:
                    if(meta->index == 8){
                       SYSTIME_G = meta->newTime;
                        // TODO update internal UNIX counter
                        // TODO Schedule task to update date/time in RTC
                    }
                    else{
                        meta->index++;
                    }
                    break;
                case BACK:                
                    if(meta->index == 0){
                        nextState = MAINMENU;
                    }
                    else{
                        meta->index--;
                    }
                    break;
            }
            break;
        // ============================= ALARM LIST: DAYS ==============================
        case VIEW_DAYSELECT:
            if(button == UP){
                meta->index = max_u8(0, meta->index-1);
            }
            else if(button == DOWN){
                meta->index = min_u8(6, meta->index+1);
            }
            else if(button == BACK){
                nextState = MAINMENU;
            }
            else if(button == FWD_OK){
                meta->daySelect = (DAY_T)meta->index;
                // TODO Gather list of alarms, pass to drawing or GFX_LIST_T
                nextState = VIEW_ALARMSELECT;
            }
            break;
        // ============================= ALARM LIST: ALARMS ==============================
        case VIEW_ALARMSELECT:
            if(button == UP){
                meta->index = max_u8(0, meta->index-1);
            }
            else if(button == DOWN){
                meta->index = min_u8(2, meta->index+1); // TODO set to alarm count
            }
            else if(button == BACK){
                nextState = VIEW_DAYSELECT;
            }
            else if(button == FWD_OK){
                if(meta->index == 0){
                    meta->selectedAlarm = NULL;
                } 
                else{
                    // TODO Get alarm struct pointer from list 
                }
                nextState = VIEW_ALARMSELECT;
            }
            break;
        // ============================= ALARM LIST: OPTIONS ==============================
        case VIEW_ALARMOPTIONS:
            if(button == UP){
                meta->index = max_u8(0, meta->index-1);
            }
            else if(button == DOWN){
                meta->index = min_u8(2, meta->index+1);
            }
            else if(button == BACK){
                nextState = VIEW_DAYSELECT;
            }
            else if(button == FWD_OK){
                switch(meta->index){
                    case 0: // EDIT
                        nextState = EDITALARM;
                        break;
                    case 1: // DELETE
                        // TODO delete alarm
                        nextState = VIEW_DAYSELECT;
                        break;
                    case 2: // CANCEL
                    default:
                        nextState = VIEW_DAYSELECT;
                }
            }
            break;
        // ============================= EDIT ALARM ==============================
        case EDITALARM:    
            switch(button){
                case UP:
                case DOWN:
                    switch(meta->index){
                        // ---- TIME SETTING ----
                        case 0 ... 7: 
                            UI_modify_time(&meta->newTime, button, meta->index);
                            break;
                        // ---- DAY SETTING ----
                        case 8 ... 15: 
                            meta->tempAlarm.days ^= (1u<<(meta->index-8));
                            break;
                    }
                    break;
                case FWD_OK:
                    if(meta->index == 15){
                        meta->tempAlarm.time_unix = time_to_unix(meta->newTime);
                        if(meta->selectedAlarm == NULL){
                            if(newAlarm(meta->tempAlarm, ALARM_ARR_G) != ERRCODE_OK){
                                meta->errorCode = ERRCODE_FAIL;
                            }
                            else{
                                nextState = VIEW_DAYSELECT;
                            }
                        }
                        else if(validateAlarm(meta->tempAlarm, ALARM_ARR_G)){
                            *meta->selectedAlarm = meta->tempAlarm;
                            nextState = VIEW_DAYSELECT;
                        }
                        else{
                            meta->errorCode = ERRCODE_FAIL;
                        }
                    }
                    else{
                        meta->index++;    
                    }
                    break;
                case BACK:                
                    if(meta->index == 0){
                        nextState = VIEW_DAYSELECT;
                    }
                    else{
                        meta->index--;
                    }
                    break;
                }
            break;
        case DEBUGMENU:
            if(meta->pulseMode_active){
                // TODO
            }
            else{
                // TODO
            }
            break;
        case USBMENU:
                // TODO
            break;
        default:
            nextState = DATETIME;
    }
    
    if(nextState != menu->state){
        // On enter state
        switch(nextState){
            case SETDATE:
                meta->newDate = UNIX_TIME_START;
                break;
            case SETTIME:
                meta->newTime = (TIME_T){0, 0, 0, 0};
                break;
            default:
                menu->state = DATETIME;
        }
        
        meta->errorCode = ERRCODE_OK;
        meta->index = 0;
        menu->state = nextState;
    }
    
    return ERRCODE_OK;
}

FUNC_ERRCODE_T drawMenu(MENU_T* menu, DISPLAY_BUFFER_T* buffer){
    // TODO
}

// ========================================
//  Debug & logging
// ========================================
void queueLogger(QUEUE_LOG_DATA_T* log){
    char** handlerNames = log->funcData->names;
    #ifdef QUEUE_LOGGING
        USBUART_PutString("\r\n---!!!---\r\n");
        CyDelay(10);
        USBUART_PutString("Task failed: ");
        CyDelay(10);
        USBUART_PutString(handlerNames[log->funcId]);
        CyDelay(10);
        USBUART_PutString("\r\n---!!!---\r\n");
        CyDelay(10);
    #else
        while(1){
            CyPins_ClearPin(DebugLED_Red);
            CyDelay(100);
            CyPins_SetPin(DebugLED_Red);
            CyDelay(100);
        }
    #endif
}

void UART_print(char label[], int val, int radix){
    char strbuf[100];
    char ibuf[30];
    itoa(val, ibuf, radix);
    sprintf(strbuf, "%s: %s\r\n", label, ibuf);
    USBUART_PutString(strbuf);
    CyDelay(10);
}

/* [] END OF FILE */
