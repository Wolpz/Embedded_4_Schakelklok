/*******************************************************************************
* File Name: MIN_HR_DAY_MATCH_STATUSREG_PM.c
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

#include "MIN_HR_DAY_MATCH_STATUSREG.h"

/* Check for removal by optimization */
#if !defined(MIN_HR_DAY_MATCH_STATUSREG_Sync_ctrl_reg__REMOVED)

static MIN_HR_DAY_MATCH_STATUSREG_BACKUP_STRUCT  MIN_HR_DAY_MATCH_STATUSREG_backup = {0u};

    
/*******************************************************************************
* Function Name: MIN_HR_DAY_MATCH_STATUSREG_SaveConfig
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
void MIN_HR_DAY_MATCH_STATUSREG_SaveConfig(void) 
{
    MIN_HR_DAY_MATCH_STATUSREG_backup.controlState = MIN_HR_DAY_MATCH_STATUSREG_Control;
}


/*******************************************************************************
* Function Name: MIN_HR_DAY_MATCH_STATUSREG_RestoreConfig
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
void MIN_HR_DAY_MATCH_STATUSREG_RestoreConfig(void) 
{
     MIN_HR_DAY_MATCH_STATUSREG_Control = MIN_HR_DAY_MATCH_STATUSREG_backup.controlState;
}


/*******************************************************************************
* Function Name: MIN_HR_DAY_MATCH_STATUSREG_Sleep
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
void MIN_HR_DAY_MATCH_STATUSREG_Sleep(void) 
{
    MIN_HR_DAY_MATCH_STATUSREG_SaveConfig();
}


/*******************************************************************************
* Function Name: MIN_HR_DAY_MATCH_STATUSREG_Wakeup
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
void MIN_HR_DAY_MATCH_STATUSREG_Wakeup(void)  
{
    MIN_HR_DAY_MATCH_STATUSREG_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
