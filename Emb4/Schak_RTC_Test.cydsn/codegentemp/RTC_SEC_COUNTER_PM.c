/*******************************************************************************
* File Name: RTC_SEC_COUNTER_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "RTC_SEC_COUNTER.h"

static RTC_SEC_COUNTER_backupStruct RTC_SEC_COUNTER_backup;


/*******************************************************************************
* Function Name: RTC_SEC_COUNTER_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  RTC_SEC_COUNTER_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void RTC_SEC_COUNTER_SaveConfig(void) 
{
    #if (!RTC_SEC_COUNTER_UsingFixedFunction)
        RTC_SEC_COUNTER_backup.TimerUdb = RTC_SEC_COUNTER_ReadCounter();
        RTC_SEC_COUNTER_backup.InterruptMaskValue = RTC_SEC_COUNTER_STATUS_MASK;
        #if (RTC_SEC_COUNTER_UsingHWCaptureCounter)
            RTC_SEC_COUNTER_backup.TimerCaptureCounter = RTC_SEC_COUNTER_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!RTC_SEC_COUNTER_UDB_CONTROL_REG_REMOVED)
            RTC_SEC_COUNTER_backup.TimerControlRegister = RTC_SEC_COUNTER_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: RTC_SEC_COUNTER_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  RTC_SEC_COUNTER_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void RTC_SEC_COUNTER_RestoreConfig(void) 
{   
    #if (!RTC_SEC_COUNTER_UsingFixedFunction)

        RTC_SEC_COUNTER_WriteCounter(RTC_SEC_COUNTER_backup.TimerUdb);
        RTC_SEC_COUNTER_STATUS_MASK =RTC_SEC_COUNTER_backup.InterruptMaskValue;
        #if (RTC_SEC_COUNTER_UsingHWCaptureCounter)
            RTC_SEC_COUNTER_SetCaptureCount(RTC_SEC_COUNTER_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!RTC_SEC_COUNTER_UDB_CONTROL_REG_REMOVED)
            RTC_SEC_COUNTER_WriteControlRegister(RTC_SEC_COUNTER_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: RTC_SEC_COUNTER_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  RTC_SEC_COUNTER_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void RTC_SEC_COUNTER_Sleep(void) 
{
    #if(!RTC_SEC_COUNTER_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(RTC_SEC_COUNTER_CTRL_ENABLE == (RTC_SEC_COUNTER_CONTROL & RTC_SEC_COUNTER_CTRL_ENABLE))
        {
            /* Timer is enabled */
            RTC_SEC_COUNTER_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            RTC_SEC_COUNTER_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    RTC_SEC_COUNTER_Stop();
    RTC_SEC_COUNTER_SaveConfig();
}


/*******************************************************************************
* Function Name: RTC_SEC_COUNTER_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  RTC_SEC_COUNTER_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void RTC_SEC_COUNTER_Wakeup(void) 
{
    RTC_SEC_COUNTER_RestoreConfig();
    #if(!RTC_SEC_COUNTER_UDB_CONTROL_REG_REMOVED)
        if(RTC_SEC_COUNTER_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                RTC_SEC_COUNTER_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
