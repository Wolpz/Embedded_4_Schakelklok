/*******************************************************************************
* File Name: SPI_RESET_PM.c
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

#include "SPI_RESET.h"

/* Check for removal by optimization */
#if !defined(SPI_RESET_Sync_ctrl_reg__REMOVED)

static SPI_RESET_BACKUP_STRUCT  SPI_RESET_backup = {0u};

    
/*******************************************************************************
* Function Name: SPI_RESET_SaveConfig
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
void SPI_RESET_SaveConfig(void) 
{
    SPI_RESET_backup.controlState = SPI_RESET_Control;
}


/*******************************************************************************
* Function Name: SPI_RESET_RestoreConfig
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
void SPI_RESET_RestoreConfig(void) 
{
     SPI_RESET_Control = SPI_RESET_backup.controlState;
}


/*******************************************************************************
* Function Name: SPI_RESET_Sleep
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
void SPI_RESET_Sleep(void) 
{
    SPI_RESET_SaveConfig();
}


/*******************************************************************************
* Function Name: SPI_RESET_Wakeup
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
void SPI_RESET_Wakeup(void)  
{
    SPI_RESET_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
