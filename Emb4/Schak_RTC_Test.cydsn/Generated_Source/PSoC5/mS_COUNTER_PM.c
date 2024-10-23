/*******************************************************************************
* File Name: mS_COUNTER_PM.c  
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

#include "mS_COUNTER.h"

static mS_COUNTER_backupStruct mS_COUNTER_backup;


/*******************************************************************************
* Function Name: mS_COUNTER_SaveConfig
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
*  mS_COUNTER_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void mS_COUNTER_SaveConfig(void) 
{
    #if (!mS_COUNTER_UsingFixedFunction)

        mS_COUNTER_backup.CounterUdb = mS_COUNTER_ReadCounter();

        #if(!mS_COUNTER_ControlRegRemoved)
            mS_COUNTER_backup.CounterControlRegister = mS_COUNTER_ReadControlRegister();
        #endif /* (!mS_COUNTER_ControlRegRemoved) */

    #endif /* (!mS_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: mS_COUNTER_RestoreConfig
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
*  mS_COUNTER_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void mS_COUNTER_RestoreConfig(void) 
{      
    #if (!mS_COUNTER_UsingFixedFunction)

       mS_COUNTER_WriteCounter(mS_COUNTER_backup.CounterUdb);

        #if(!mS_COUNTER_ControlRegRemoved)
            mS_COUNTER_WriteControlRegister(mS_COUNTER_backup.CounterControlRegister);
        #endif /* (!mS_COUNTER_ControlRegRemoved) */

    #endif /* (!mS_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: mS_COUNTER_Sleep
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
*  mS_COUNTER_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void mS_COUNTER_Sleep(void) 
{
    #if(!mS_COUNTER_ControlRegRemoved)
        /* Save Counter's enable state */
        if(mS_COUNTER_CTRL_ENABLE == (mS_COUNTER_CONTROL & mS_COUNTER_CTRL_ENABLE))
        {
            /* Counter is enabled */
            mS_COUNTER_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            mS_COUNTER_backup.CounterEnableState = 0u;
        }
    #else
        mS_COUNTER_backup.CounterEnableState = 1u;
        if(mS_COUNTER_backup.CounterEnableState != 0u)
        {
            mS_COUNTER_backup.CounterEnableState = 0u;
        }
    #endif /* (!mS_COUNTER_ControlRegRemoved) */
    
    mS_COUNTER_Stop();
    mS_COUNTER_SaveConfig();
}


/*******************************************************************************
* Function Name: mS_COUNTER_Wakeup
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
*  mS_COUNTER_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void mS_COUNTER_Wakeup(void) 
{
    mS_COUNTER_RestoreConfig();
    #if(!mS_COUNTER_ControlRegRemoved)
        if(mS_COUNTER_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            mS_COUNTER_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!mS_COUNTER_ControlRegRemoved) */
    
}


/* [] END OF FILE */
