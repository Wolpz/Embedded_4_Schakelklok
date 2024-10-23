/*******************************************************************************
* File Name: MILLIS_COUNTER_PM.c  
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

#include "MILLIS_COUNTER.h"

static MILLIS_COUNTER_backupStruct MILLIS_COUNTER_backup;


/*******************************************************************************
* Function Name: MILLIS_COUNTER_SaveConfig
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
*  MILLIS_COUNTER_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void MILLIS_COUNTER_SaveConfig(void) 
{
    #if (!MILLIS_COUNTER_UsingFixedFunction)

        MILLIS_COUNTER_backup.CounterUdb = MILLIS_COUNTER_ReadCounter();

        #if(!MILLIS_COUNTER_ControlRegRemoved)
            MILLIS_COUNTER_backup.CounterControlRegister = MILLIS_COUNTER_ReadControlRegister();
        #endif /* (!MILLIS_COUNTER_ControlRegRemoved) */

    #endif /* (!MILLIS_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MILLIS_COUNTER_RestoreConfig
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
*  MILLIS_COUNTER_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void MILLIS_COUNTER_RestoreConfig(void) 
{      
    #if (!MILLIS_COUNTER_UsingFixedFunction)

       MILLIS_COUNTER_WriteCounter(MILLIS_COUNTER_backup.CounterUdb);

        #if(!MILLIS_COUNTER_ControlRegRemoved)
            MILLIS_COUNTER_WriteControlRegister(MILLIS_COUNTER_backup.CounterControlRegister);
        #endif /* (!MILLIS_COUNTER_ControlRegRemoved) */

    #endif /* (!MILLIS_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MILLIS_COUNTER_Sleep
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
*  MILLIS_COUNTER_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void MILLIS_COUNTER_Sleep(void) 
{
    #if(!MILLIS_COUNTER_ControlRegRemoved)
        /* Save Counter's enable state */
        if(MILLIS_COUNTER_CTRL_ENABLE == (MILLIS_COUNTER_CONTROL & MILLIS_COUNTER_CTRL_ENABLE))
        {
            /* Counter is enabled */
            MILLIS_COUNTER_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            MILLIS_COUNTER_backup.CounterEnableState = 0u;
        }
    #else
        MILLIS_COUNTER_backup.CounterEnableState = 1u;
        if(MILLIS_COUNTER_backup.CounterEnableState != 0u)
        {
            MILLIS_COUNTER_backup.CounterEnableState = 0u;
        }
    #endif /* (!MILLIS_COUNTER_ControlRegRemoved) */
    
    MILLIS_COUNTER_Stop();
    MILLIS_COUNTER_SaveConfig();
}


/*******************************************************************************
* Function Name: MILLIS_COUNTER_Wakeup
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
*  MILLIS_COUNTER_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MILLIS_COUNTER_Wakeup(void) 
{
    MILLIS_COUNTER_RestoreConfig();
    #if(!MILLIS_COUNTER_ControlRegRemoved)
        if(MILLIS_COUNTER_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            MILLIS_COUNTER_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!MILLIS_COUNTER_ControlRegRemoved) */
    
}


/* [] END OF FILE */
