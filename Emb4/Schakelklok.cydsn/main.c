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
#include "Schakelklok_Buttons.h"


volatile int flag_checkButtons = 0;


CY_ISR_PROTO(ISRH_CheckButtons);

CY_ISR(ISRH_CheckButtons){
    flag_checkButtons = 1;
    ISR_1kHz_ClearInterrupt();
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    uint8_t buttonStatus = 0;
    
    ISR_1kHz_StartEx(ISRH_CheckButtons);
    
    for(;;)
    {
        if(flag_checkButtons == 1){
            buttonStatus = checkButtons(i_Buttons_Read());
            flag_checkButtons = 0;
        }
        //if()
        
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
