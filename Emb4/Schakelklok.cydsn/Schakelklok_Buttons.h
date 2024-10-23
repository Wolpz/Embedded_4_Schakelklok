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
#include "Schakelklok_types.h"

#define BUTTON_CLOCKFREQ_HZ 
#define BUTTON_PRESS_MS 100
#define BUTTON_LONGPRESS_MS 1000

BUTTONSTATUS_T button_debounce(int buttonRead_i, BUTTON_T* button);
    // if button high, increment ctr
    // then check with press/longpress and set status accordingly


/* [] END OF FILE */
