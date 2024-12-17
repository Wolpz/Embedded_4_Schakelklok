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
    - Implement current functionalities as tasks
    - Change sec counter to UNIX timestamp. Saves so much fuss and potential bugs.
    - Add alarm functionality
    - Add menu statemanager
    - (Optional) Add proper error reporting to queue
    - (Optional) Add sync for internal timekeeping
*/
#define QUEUE_DEBUG
#define QUEUE_LOGGING  


#define LCD_WIDTH   160 //LCD width
#define LCD_HEIGHT  128 //LCD height

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
//   Global volatiles initialisation
// ========================================   
const UWORD dispBuf_array[LCD_WIDTH * LCD_HEIGHT];
TIME_T systime;
DATE_T sysdate;
volatile uint8_t MS_CALIB_FLAG;
volatile uint8_t INCR_TIME_FLAG;

void* addr;

// ========================================
//   Task initialisation
// ======================================== 
typedef struct {
    uint32_t CyPins_ID;
    FUNC_QUEUE_T* queue;
} LED_args_t;
FUNCTION_ERRCODE_T LED_args_destructor(void* LED_args){
    free(LED_args);
    return ERRCODE_OK;
}
FUNCTION_ERRCODE_T setLED(void* LED_args);
FUNCTION_ERRCODE_T clearLED(void* LED_args);

#define HANDLERFUNCS {setLED, clearLED}
#define HANDLERNAMES {"UNDEFINED", "setLED", "clearLED"}
void queueLogger(QUEUE_LOG_DATA_T* log);

// Interrupts
// ========================================
//   Millisecond calibration interrupt
//      Gets capture value when 1s signal from RTC is passed, uses this to determine if counter is running too fast or too slow and adjusts counter period within accuracy margin to compensate.
// ========================================
CY_ISR(MS_CALIBRATION_INTVECT){
    // TODO add to queue
    MS_CALIB_FLAG = 1; 
    MILLIS_COUNTER_CAPT_INT_ClearPending();
}

// Whenever second counter completes, meaning 1min has passed
CY_ISR(SEC_CTR_TC_INTVECT){
    // TODO  add to queue
    INCR_TIME_FLAG = 1;
    SEC_CTR_TC_INT_ClearPending();
}

// ========================================
//   Debug defines
// ========================================
#ifdef QUEUE_DEBUG
    #define UART_DEBUG
#endif

#ifdef UART_DEBUG
// DEBUG
void UART_print(char label[], int val, int radix);
#endif


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
        CyDelay(500);
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
FUNCTION_ERRCODE_T setLED(void* LEDargs_vptr){
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
FUNCTION_ERRCODE_T clearLED(void* LEDargs_vptr){
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

// ========================================
//  Debug & logging
// ========================================
void queueLogger(QUEUE_LOG_DATA_T* log){
    char** handlerNames = log->funcData->names;
    USBUART_PutString("\r\n---!!!---\r\n");
    CyDelay(10);
    USBUART_PutString("Task failed: ");
    CyDelay(10);
    USBUART_PutString(handlerNames[log->funcId]);
    CyDelay(10);
    USBUART_PutString("\r\n---!!!---\r\n");
    CyDelay(10);
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
