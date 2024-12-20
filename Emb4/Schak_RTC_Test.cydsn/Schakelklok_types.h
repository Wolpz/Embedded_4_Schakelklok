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
#include "project.h"

#ifndef SCHAKELKLOK_TYPES_H 
#define SCHAKELKLOK_TYPES_H 
    
    #define ERRCODE_OK (0)
    #define ERRCODE_FAIL (1)
    #define ERRCODE_RETRY (2)
    #define ERRCODE_QUEUE_EMPTY (3)
    
    typedef uint8_t FUNC_ERRCODE_T;
    
    typedef uint16_t UWORD;
    typedef uint8_t UBYTE;
    typedef uint32_t UDOUBLE;
    
    typedef struct {
    	const char* contents;
    	uint8_t length;
    }C_STRING_T;
    C_STRING_T* newString(const char* str, uint8_t length); // TODO write
    FUNC_ERRCODE_T dropString(C_STRING_T* str); // TODO write
    
        typedef struct {
        uint8_t hours;
        uint8_t minutes;
        uint8_t seconds;
        uint16_t ms;
    } TIME_T;
    
    typedef enum {MON, TUE, WED, THU, FRI, SAT, SUN} DAY_T;
    typedef struct {
        DAY_T day;
        uint8_t date; 
        uint8_t month;
        uint16_t year;
    } DATE_T;
    
    typedef struct {
        uint32_t time_ms;
        uint8_t daysActive;
        uint8_t outputs; /* Upper 4 bits: mask, lower 4 bits: output state.*/
    } ALARM_T;
    
    typedef enum {
        BACK,
        FWD_OK,
        UP,
        DOWN
    } BUTTON_T;
    
    typedef enum {
        MAINMENU = 0,
        DATETIME = 1,
        SETDATE = 2,
        SETTIME = 3,
        VIEW_OUTPUTSELECT = 4,
        DEBUGMENU = 5,
        USBMENU = 6,
        VIEW_ALARMSELECT = 7,
        VIEW_ALARMOPTIONS = 8,
        EDITALARM = 9
    } MENUSTATE_T;
    
    typedef struct {
        uint8_t index;
        DATE_T newDate;
        TIME_T newTime;
        uint8_t outputSelect;
        uint8_t daySelect;
        ALARM_T* alarmList;
        ALARM_T* selectedAlarm;
        ALARM_T tempAlarm;
        uint8_t errorCode;
        uint8_t pulseMode_active;
    } MENU_METADATA_T;
    
    typedef struct {
        MENUSTATE_T state;
        MENU_METADATA_T meta;
    } MENU_T;
    
    typedef struct {
        TIME_T time;
        DATE_T* date;
        
    } STATUSBAR_INFO_T;

#endif
/* [] END OF FILE */
