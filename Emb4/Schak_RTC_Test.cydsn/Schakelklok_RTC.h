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
#ifndef SCHAKELKLOK_RTC_H
    #define SCHAKELKLOK_RTC_H

    #include "..\Schakelklok.cydsn\Schakelklok_types.h"
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
        
    #define RTC_ADDRESS 0x68
    #define RTC_READ 1
    #define RTC_Write 0

    #define RTC_ADDR_SECS 0x00
    #define RTC_ADDR_MINS 0x01
    #define RTC_ADDR_HRS 0x02
    #define RTC_ADDR_DAY 0x03
    #define RTC_ADDR_DATE 0x04
    #define RTC_ADDR_MON 0x05
    #define RTC_ADDR_YR 0x06

    #define RTC_ADDR_ALARM1_SECS 0x07
    #define RTC_ADDR_ALARM1_MINS 0x08
    #define RTC_ADDR_ALARM1_HRS 0x09
    #define RTC_ADDR_ALARM1_DAYDATE 0x0A 

    #define RTC_ADDR_ALARM2_MINS 0x0B
    #define RTC_ADDR_ALARM2_HRS 0x0C
    #define RTC_ADDR_ALARM2_DAYDATE 0x0D 

    #define RTC_ADDR_CONTR1 0x0E
    #define RTC_ADDR_CONTR2 0x0F 

    #define RTC_ADDR_SRAM_START 0x14
    #define RTC_ADDR_SRAM_END 0xFF

    #define RTC_HOURS_12_24_shift 6
    #define RTC_HOURS_12 1<<RTC_HOURS_12_24_shift

    #define RTC_SRAM_MILLENIUM_CENTURY 0x14

    

    void RTC_Init();
    void RTC_Reset();

    uint8_t RTC_GetSeconds();
    uint8_t RTC_GetMinutes();
    uint8_t RTC_GetHours();
    void RTC_SetSeconds(uint8_t t);
    void RTC_SetMinutes(uint8_t t);
    void RTC_SetHours(uint8_t hrs);

    uint16_t GetMillis();
    void SetMillis(uint16_t millis);
    uint8_t RTC_GetDay();
    uint8_t RTC_GetDate();
    uint8_t RTC_GetMonth();
    uint16_t RTC_GetYear();
    void RTC_SetDay(uint8_t day);
    void RTC_SetDate(uint8_t date);
    void RTC_SetMonth(uint8_t month);
    void RTC_SetYear(uint16_t year);

    UBYTE RTC_ReadAddr(UBYTE address);
    void RTC_WriteAddr(UBYTE address, UBYTE value);

    void TimeToString(TIME_T time, char buf[12]);
    void DateToString(DATE_T date, char* buf);

    void Time_Init(volatile TIME_T* time, volatile DATE_T* date);
    void Time_doIncrement(TIME_T* time, DATE_T* date);
    void Time_CalibrateMillis();
    void incrMins(TIME_T* time, DATE_T* date);
    void incrHrs(TIME_T* time, DATE_T* date);
    void incrDate(TIME_T* time, DATE_T* date);
    void incrMonth(TIME_T* time, DATE_T* date);

#endif
/* [] END OF FILE */
