/*******************************************************************************
* File Name: BUTTONPRESS_REG.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "BUTTONPRESS_REG.h"

#if !defined(BUTTONPRESS_REG_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: BUTTONPRESS_REG_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The current value in the Status Register.
*
*******************************************************************************/
uint8 BUTTONPRESS_REG_Read(void) 
{ 
    return BUTTONPRESS_REG_Status;
}


/*******************************************************************************
* Function Name: BUTTONPRESS_REG_InterruptEnable
********************************************************************************
*
* Summary:
*  Enables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void BUTTONPRESS_REG_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    BUTTONPRESS_REG_Status_Aux_Ctrl |= BUTTONPRESS_REG_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: BUTTONPRESS_REG_InterruptDisable
********************************************************************************
*
* Summary:
*  Disables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void BUTTONPRESS_REG_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    BUTTONPRESS_REG_Status_Aux_Ctrl &= (uint8)(~BUTTONPRESS_REG_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: BUTTONPRESS_REG_WriteMask
********************************************************************************
*
* Summary:
*  Writes the current mask value assigned to the Status Register.
*
* Parameters:
*  mask:  Value to write into the mask register.
*
* Return:
*  None.
*
*******************************************************************************/
void BUTTONPRESS_REG_WriteMask(uint8 mask) 
{
    #if(BUTTONPRESS_REG_INPUTS < 8u)
    	mask &= ((uint8)(1u << BUTTONPRESS_REG_INPUTS) - 1u);
	#endif /* End BUTTONPRESS_REG_INPUTS < 8u */
    BUTTONPRESS_REG_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: BUTTONPRESS_REG_ReadMask
********************************************************************************
*
* Summary:
*  Reads the current interrupt mask assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the interrupt mask of the Status Register.
*
*******************************************************************************/
uint8 BUTTONPRESS_REG_ReadMask(void) 
{
    return BUTTONPRESS_REG_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
