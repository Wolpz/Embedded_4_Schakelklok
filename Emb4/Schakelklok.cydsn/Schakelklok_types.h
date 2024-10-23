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

typedef enum {
        OFF, PRESS, LONGPRESS
    } BUTTONSTATUS_T;

typedef struct{
    uint8_t mask;
    uint16_t counter;
    BUTTONSTATUS_T status;
} BUTTON_T;

/*
typedef struct {
    uint8_t* address;
    uint8_t bitPosition;
    void (*resolver)();
} FLAG_T;
*/
/*
typedef union {
  uint16_t uWord;
  uint8_t uByte[2];
} UWORD;
*/
typedef uint16_t UWORD;
typedef uint8_t UBYTE;
typedef uint32_t UDOUBLE;

typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint16_t ms;
} TIME_T;
typedef struct {
    uint8_t day;
    uint8_t date; 
    uint8_t month;
    uint16_t year;
} DATE_T;



/* [] END OF FILE */
