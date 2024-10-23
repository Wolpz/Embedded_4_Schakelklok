/*******************************************************************************
* File Name: uS_COUNTER_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "uS_COUNTER.h"

static uS_COUNTER_backupStruct uS_COUNTER_backup;


/*******************************************************************************
* Function Name: uS_COUNTER_SaveConfig
********************************************************************************
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
*  uS_COUNTER_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void uS_COUNTER_SaveConfig(void) 
{
    #if (!uS_COUNTER_UsingFixedFunction)

        uS_COUNTER_backup.CounterUdb = uS_COUNTER_ReadCounter();

        #if(!uS_COUNTER_ControlRegRemoved)
            uS_COUNTER_backup.CounterControlRegister = uS_COUNTER_ReadControlRegister();
        #endif /* (!uS_COUNTER_ControlRegRemoved) */

    #endif /* (!uS_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: uS_COUNTER_RestoreConfig
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
*  uS_COUNTER_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void uS_COUNTER_RestoreConfig(void) 
{      
    #if (!uS_COUNTER_UsingFixedFunction)

       uS_COUNTER_WriteCounter(uS_COUNTER_backup.CounterUdb);

        #if(!uS_COUNTER_ControlRegRemoved)
            uS_COUNTER_WriteControlRegister(uS_COUNTER_backup.CounterControlRegister);
        #endif /* (!uS_COUNTER_ControlRegRemoved) */

    #endif /* (!uS_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: uS_COUNTER_Sleep
********************************************************************************
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
*  uS_COUNTER_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void uS_COUNTER_Sleep(void) 
{
    #if(!uS_COUNTER_ControlRegRemoved)
        /* Save Counter's enable state */
        if(uS_COUNTER_CTRL_ENABLE == (uS_COUNTER_CONTROL & uS_COUNTER_CTRL_ENABLE))
        {
            /* Counter is enabled */
            uS_COUNTER_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            uS_COUNTER_backup.CounterEnableState = 0u;
        }
    #else
        uS_COUNTER_backup.CounterEnableState = 1u;
        if(uS_COUNTER_backup.CounterEnableState != 0u)
        {
            uS_COUNTER_backup.CounterEnableState = 0u;
        }
    #endif /* (!uS_COUNTER_ControlRegRemoved) */
    
    uS_COUNTER_Stop();
    uS_COUNTER_SaveConfig();
}


/*******************************************************************************
* Function Name: uS_COUNTER_Wakeup
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
*  uS_COUNTER_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void uS_COUNTER_Wakeup(void) 
{
    uS_COUNTER_RestoreConfig();
    #if(!uS_COUNTER_ControlRegRemoved)
        if(uS_COUNTER_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            uS_COUNTER_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!uS_COUNTER_ControlRegRemoved) */
    
}


/* [] END OF FILE */
