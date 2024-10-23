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
#include "Schakelklok_Buttons.h"

// K I S S
// Split everything up into funcs that are as simple and short as possible\

// TODO how to add buttons to kept array of buttons to check?

void checkButtons(BUTTON_T* button_ptr, FLAG_T* flag, int flag_offset){
    // TODO
    //debounce all buttons (using array??)
    //check if return val for any button is diff from old value, set button flag using offset
    
}

BUTTONSTATUS_T button_debounce(int buttonRead_i, BUTTON_T* button_ptr){
    BUTTONSTATUS_T  btnStatus = OFF;
    
    if(buttonRead_i == 1){
        if(button_ptr->counter > BUTTON_LONGPRESS_MS){
            button_ptr->counter = button_ptr->counter;
            btnStatus = LONGPRESS;
        }
        else{
            if(button_ptr->counter > BUTTON_PRESS_MS){
                btnStatus = PRESS;
            }
            button_ptr->counter++;
        }
    }
    else{
        button_ptr->counter = 0;
        btnStatus = OFF;
    }
    return btnStatus;
}

/* [] END OF FILE */
