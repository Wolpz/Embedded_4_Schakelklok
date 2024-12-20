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
#include "Schakelklok_RTC.h"




void RTC_Init(){
    // Get hours, check current 12/24h setting
    // Set to 24h
    UBYTE hrs = RTC_ReadAddr(RTC_ADDR_HRS);
    if(hrs & RTC_HOURS_12){ // If AM/PM mode enabled, and it's PM
        hrs = (hrs & 0x0F) + ((hrs>>4) & 0x1)*10;
        hrs += 12;
        RTC_SetHours(hrs);
    }
    
    // DEBUG
    RTC_SetHours(23);
    RTC_SetMinutes(59);
    RTC_SetSeconds(48);
    
    RTC_SetDate(31);
    RTC_SetDay(7);
    RTC_SetMonth(12);
    RTC_SetYear(1999);
    
    // Enable 1Hz signal generation for calibration
    RTC_WriteAddr(0x0E, 0x00); // Control register 0Eh: enable 1Hz square wave
    CyDelay(10);
}

void RTC_Reset(){
    CyPins_ClearPin(RTC_RST);
    CyDelay(20);
    CyPins_SetPin(RTC_RST);
    CyDelay(20);
}

uint8_t RTC_GetSeconds(){
    UBYTE t = RTC_ReadAddr(RTC_ADDR_SECS);
    t = (t & 0x0F) + ((t>>4) * 10);
    return t;
}
void RTC_SetSeconds(uint8_t t){
    uint8_t ones = t % 10/*0-9*/;
    uint8_t tens = ((t % 100) - ones)/10/*tens*/;
    t =  ones + ((tens&0x07)<<4);
    #ifdef DEBUG_RTC
        UART_print("Secs", t, 2);
    #endif
    RTC_WriteAddr(RTC_ADDR_SECS, t);
}
uint8_t RTC_GetMinutes(){
    UBYTE t = RTC_ReadAddr(RTC_ADDR_MINS);
    t = (t & 0x0F) + ((t>>4) * 10);
    return t;
}
void RTC_SetMinutes(uint8_t t){
    uint8_t ones = t % 10/*0-9*/;
    uint8_t tens = ((t % 100) - ones)/10/*tens*/;
    t =  ones + ((tens&0x07)<<4);
    #ifdef DEBUG_RTC
        UART_print("Mins", t, 2);
    #endif
    RTC_WriteAddr(RTC_ADDR_MINS, t);
}

uint8_t RTC_GetHours(){
    UBYTE t = RTC_ReadAddr(RTC_ADDR_HRS);
    t = (t & 0x0F) + ((t>>4) & 0x3)*10;;
    return t;
}
void RTC_SetHours(uint8_t hrs){
    uint8_t ones = hrs % 10/*0-9*/;
    uint8_t tens = ((hrs % 100) - ones)/10/*tens*/;
    hrs =  ones + ((tens&0x03)<<4);
    hrs = hrs & ~(1<<RTC_HOURS_12_24_shift);//Setting to 24h format
    #ifdef DEBUG_RTC
        UART_print("Hrs", hrs, 2);
    #endif
    RTC_WriteAddr(RTC_ADDR_HRS, hrs);
}

uint8_t RTC_GetDay(){
    UBYTE t = RTC_ReadAddr(RTC_ADDR_DAY);
    t = (t & 0x07);
    return t;
}
void RTC_SetDay(uint8_t day){
    RTC_WriteAddr(RTC_ADDR_DAY, day & 0x07);
}

uint8_t RTC_GetDate(){
    UBYTE t = RTC_ReadAddr(RTC_ADDR_DATE) & 0x3F;
    t = (t & 0x0F) + ((t>>4) * 10);
    return t;
}
void RTC_SetDate(uint8_t t){
    uint8_t ones = t % 10/*0-9*/;
    uint8_t tens = ((t % 100) - ones)/10/*tens*/;
    t =  ones + ((tens&0x03)<<4);
    #ifdef DEBUG_RTC
        UART_print("Date", t, 2);
    #endif
    RTC_WriteAddr(RTC_ADDR_DATE, t);
}

uint8_t RTC_GetMonth(){
    uint8_t t = RTC_ReadAddr(RTC_ADDR_MON);
    if(t & 1<<7){
        // update century in SRAM and reset century bit 
        uint8_t milcentury = RTC_ReadAddr(RTC_SRAM_MILLENIUM_CENTURY);
        milcentury += 1;
        RTC_WriteAddr(RTC_SRAM_MILLENIUM_CENTURY, milcentury & 0xFF);
        RTC_WriteAddr(RTC_ADDR_MON, t & ~(1<<7));
    }
    t = t & 0x1F;
    t = (t & 0x0F) + ((t>>4) * 10);
    return t;
}
void RTC_SetMonth(uint8_t t){
    uint8_t centuryBit = RTC_ReadAddr(RTC_ADDR_MON) & 1<<7;
    if(centuryBit){
        // update century in SRAM and reset century bit 
        uint8_t milcentury = RTC_ReadAddr(RTC_SRAM_MILLENIUM_CENTURY);
        milcentury += 1;
        RTC_WriteAddr(RTC_SRAM_MILLENIUM_CENTURY, milcentury & 0xFF);
    }
    uint8_t ones = t % 10/*0-9*/;
    uint8_t tens = ((t % 100) - ones)/10/*tens*/;
    t =  ones + ((tens&0x01)<<4);
    #ifdef DEBUG_RTC
        UART_print("Month", t, 2);
    #endif
    RTC_WriteAddr(RTC_ADDR_MON, t);
    
}

uint16_t RTC_GetYear(){
    uint8_t mon = RTC_ReadAddr(RTC_ADDR_MON);
    uint8_t milcentury = RTC_ReadAddr(RTC_SRAM_MILLENIUM_CENTURY);
    if(mon & 1<<7){
        // update century in SRAM and clear century bit   
        milcentury += 1;
        RTC_WriteAddr(RTC_SRAM_MILLENIUM_CENTURY, milcentury & 0xFF);
        RTC_WriteAddr(RTC_ADDR_MON, mon & ~(1<<7));
    }
    uint8_t year = RTC_ReadAddr(RTC_ADDR_YR);
    year = (year & 0x0F) + ((year>>4) * 10);
    return (year + milcentury*100);
}

void RTC_SetYear(uint16_t t){
    uint8_t ones = t % 10/*0-9*/;
    uint8_t tens = ((t % 100) - ones);
    uint8_t century = (t - ones -tens)/100;
    tens = tens/10;
    
    #ifdef DEBUG_RTC
        UART_print("Century", century & 0xFF, 2);
    #endif
    
    
    t =  ones + ((tens&0x0F)<<4);
    #ifdef DEBUG_RTC
        UART_print("Year", t, 2);
    #endif

    RTC_WriteAddr(RTC_ADDR_YR, t);
    
    // Reset century and update current century in SRAM
    uint8_t mon = RTC_ReadAddr(RTC_ADDR_MON);
    RTC_WriteAddr(RTC_ADDR_MON, mon & ~(1<<7));
    RTC_WriteAddr(RTC_SRAM_MILLENIUM_CENTURY, century & 0xFF);
}

void RTC_WriteAddr(UBYTE address, UBYTE value){
    UBYTE i2c_buf[2] = {address, value};
    
    I2C_MasterWriteBuf(RTC_ADDRESS, i2c_buf, 2, I2C_MODE_COMPLETE_XFER);
    while( !(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT)); // Block until complete TODO make something better, async?
}

UBYTE RTC_ReadAddr(UBYTE address){
    UBYTE i2c_buf = address;
    
    I2C_MasterWriteBuf(RTC_ADDRESS, &i2c_buf, 1, I2C_MODE_COMPLETE_XFER);
    while( !(I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));// Block until complete TODO make something better , async?
    I2C_MasterReadBuf(RTC_ADDRESS, &i2c_buf, 1, I2C_MODE_COMPLETE_XFER);
    while( !(I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT));// Block until complete TODO make something better, async?
    
    return i2c_buf;
}

    // ====================================
    // Alarms
    // ====================================
    FUNC_ERRCODE_T newAlarm(ALARM_T alarm, ALARM_T* list){
        ALARM_T* spot;
        ALARM_T* comp;
        for(int i = 0; i < MAX_ALARMS; i++){
            comp = (list+i);
            if(alarm.daysActive == comp->daysActive && alarm.outputs == comp->outputs && alarm.time_ms == comp->time_ms){
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

    // TODO
    // Sorts alarms in ascending order
    FUNC_ERRCODE_T sortAlarms(ALARM_T* alarms){
        ALARM_T* temp;
        for(int i = 0; i < MAX_ALARMS-1; i++){
            //if(((alarmList+i)
        }
    }
    
    FUNC_ERRCODE_T validateAlarm(ALARM_T alarm, ALARM_T* list){
        ALARM_T* comp;
        for(int i = 0; i < MAX_ALARMS; i++){
            comp = (list+i);
            if(alarm.daysActive == comp->daysActive && alarm.outputs == comp->outputs && alarm.time_ms == comp->time_ms){
                // Identical alarm already present
                return ERRCODE_FAIL;
            }
        }
        return ERRCODE_OK;    
    }
    
    // ====================================
    // Internal timekeeping
    // ====================================
    void ms2time(uint32_t ms, TIME_T * time) {
        time->ms = ms % 1000;
        time->seconds = (ms / 1000) % 60;
        time->minutes = (ms / 60000) % 60;
        time->hours = ms / 3600000;
    }
    void time2ms(TIME_T time, uint32_t * ms) {
        *ms = time.ms + time.seconds * 1000 + time.minutes * 60000 + time.hours * 3600000;
    }
    
// ====================================
// Helpers
// ====================================
DAY_T computeDayOfWeek(DATE_T date){
    int y = date.year, m = date.month, d = date.date;
    if (m < 3) {
        m += 12;
        y--;
    }
    int k = y % 100;
    int j = y / 100;
    int day = (d + (13 * (m + 1)) / 5 + k + (k / 4) + (j / 4) - (2 * j)) % 7;
    return (DAY_T)((day + 5) % 7); // Adjust to make 0 = MON
}

uint8_t validateDate(DATE_T date){
    return (date.date <= getDaysInMonth(date.month, date.year));
}

uint8_t getDaysInMonth(uint8_t m, uint16_t y){
    const uint8_t daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(m != 2){
        return daysInMonth[m-1];
    }
    else if((y % 400 == 0) || ((y % 100 != 0) && (y % 4 == 0))){
        return 29;
    }
    else{
        return 28;
    }
}

void TimeToString(TIME_T time, char* buf){
	sprintf(buf, "%02d:%02d:%02d:%03d\r\n", time.hours, time.minutes, time.seconds, time.ms);
}

void DateToString(DATE_T date, char* buf){
    char* dayRef[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    sprintf(buf, "%s %02d-%02d-%04d\r\n", dayRef[date.day-1], date.date, date.month, date.year);
}
/* [] END OF FILE */
