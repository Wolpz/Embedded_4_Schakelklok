/*******************************************************************************
* File Name: MILLIS_CTR_CAPTSEL_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "MILLIS_CTR_CAPTSEL.h"

/* Check for removal by optimization */
#if !defined(MILLIS_CTR_CAPTSEL_Sync_ctrl_reg__REMOVED)

static MILLIS_CTR_CAPTSEL_BACKUP_STRUCT  MILLIS_CTR_CAPTSEL_backup = {0u};

    
/*******************************************************************************
* Function Name: MILLIS_CTR_CAPTSEL_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MILLIS_CTR_CAPTSEL_SaveConfig(void) 
{
    MILLIS_CTR_CAPTSEL_backup.controlState = MILLIS_CTR_CAPTSEL_Control;
}


/*******************************************************************************
* Function Name: MILLIS_CTR_CAPTSEL_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void MILLIS_CTR_CAPTSEL_RestoreConfig(void) 
{
     MILLIS_CTR_CAPTSEL_Control = MILLIS_CTR_CAPTSEL_backup.controlState;
}


/*******************************************************************************
* Function Name: MILLIS_CTR_CAPTSEL_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MILLIS_CTR_CAPTSEL_Sleep(void) 
{
    MILLIS_CTR_CAPTSEL_SaveConfig();
}


/*******************************************************************************
* Function Name: MILLIS_CTR_CAPTSEL_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MILLIS_CTR_CAPTSEL_Wakeup(void)  
{
    MILLIS_CTR_CAPTSEL_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
