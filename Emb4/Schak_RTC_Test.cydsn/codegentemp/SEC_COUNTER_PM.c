/*******************************************************************************
* File Name: SEC_COUNTER_PM.c  
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

#include "SEC_COUNTER.h"

static SEC_COUNTER_backupStruct SEC_COUNTER_backup;


/*******************************************************************************
* Function Name: SEC_COUNTER_SaveConfig
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
*  SEC_COUNTER_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void SEC_COUNTER_SaveConfig(void) 
{
    #if (!SEC_COUNTER_UsingFixedFunction)

        SEC_COUNTER_backup.CounterUdb = SEC_COUNTER_ReadCounter();

        #if(!SEC_COUNTER_ControlRegRemoved)
            SEC_COUNTER_backup.CounterControlRegister = SEC_COUNTER_ReadControlRegister();
        #endif /* (!SEC_COUNTER_ControlRegRemoved) */

    #endif /* (!SEC_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: SEC_COUNTER_RestoreConfig
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
*  SEC_COUNTER_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void SEC_COUNTER_RestoreConfig(void) 
{      
    #if (!SEC_COUNTER_UsingFixedFunction)

       SEC_COUNTER_WriteCounter(SEC_COUNTER_backup.CounterUdb);

        #if(!SEC_COUNTER_ControlRegRemoved)
            SEC_COUNTER_WriteControlRegister(SEC_COUNTER_backup.CounterControlRegister);
        #endif /* (!SEC_COUNTER_ControlRegRemoved) */

    #endif /* (!SEC_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: SEC_COUNTER_Sleep
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
*  SEC_COUNTER_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void SEC_COUNTER_Sleep(void) 
{
    #if(!SEC_COUNTER_ControlRegRemoved)
        /* Save Counter's enable state */
        if(SEC_COUNTER_CTRL_ENABLE == (SEC_COUNTER_CONTROL & SEC_COUNTER_CTRL_ENABLE))
        {
            /* Counter is enabled */
            SEC_COUNTER_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            SEC_COUNTER_backup.CounterEnableState = 0u;
        }
    #else
        SEC_COUNTER_backup.CounterEnableState = 1u;
        if(SEC_COUNTER_backup.CounterEnableState != 0u)
        {
            SEC_COUNTER_backup.CounterEnableState = 0u;
        }
    #endif /* (!SEC_COUNTER_ControlRegRemoved) */
    
    SEC_COUNTER_Stop();
    SEC_COUNTER_SaveConfig();
}


/*******************************************************************************
* Function Name: SEC_COUNTER_Wakeup
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
*  SEC_COUNTER_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void SEC_COUNTER_Wakeup(void) 
{
    SEC_COUNTER_RestoreConfig();
    #if(!SEC_COUNTER_ControlRegRemoved)
        if(SEC_COUNTER_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            SEC_COUNTER_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!SEC_COUNTER_ControlRegRemoved) */
    
}


/* [] END OF FILE */
