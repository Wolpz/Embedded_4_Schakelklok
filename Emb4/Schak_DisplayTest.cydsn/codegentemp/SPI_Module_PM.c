/*******************************************************************************
* File Name: SPI_Module_PM.c
* Version 2.50
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPI_Module_PVT.h"

static SPI_Module_BACKUP_STRUCT SPI_Module_backup =
{
    SPI_Module_DISABLED,
    SPI_Module_BITCTR_INIT,
};


/*******************************************************************************
* Function Name: SPI_Module_SaveConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SPI_Module_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPI_Module_RestoreConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SPI_Module_RestoreConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPI_Module_Sleep
********************************************************************************
*
* Summary:
*  Prepare SPIM Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPI_Module_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPI_Module_Sleep(void) 
{
    /* Save components enable state */
    SPI_Module_backup.enableState = ((uint8) SPI_Module_IS_ENABLED);

    SPI_Module_Stop();
}


/*******************************************************************************
* Function Name: SPI_Module_Wakeup
********************************************************************************
*
* Summary:
*  Prepare SPIM Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPI_Module_backup - used when non-retention registers are restored.
*  SPI_Module_txBufferWrite - modified every function call - resets to
*  zero.
*  SPI_Module_txBufferRead - modified every function call - resets to
*  zero.
*  SPI_Module_rxBufferWrite - modified every function call - resets to
*  zero.
*  SPI_Module_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPI_Module_Wakeup(void) 
{
    #if(SPI_Module_RX_SOFTWARE_BUF_ENABLED)
        SPI_Module_rxBufferFull  = 0u;
        SPI_Module_rxBufferRead  = 0u;
        SPI_Module_rxBufferWrite = 0u;
    #endif /* (SPI_Module_RX_SOFTWARE_BUF_ENABLED) */

    #if(SPI_Module_TX_SOFTWARE_BUF_ENABLED)
        SPI_Module_txBufferFull  = 0u;
        SPI_Module_txBufferRead  = 0u;
        SPI_Module_txBufferWrite = 0u;
    #endif /* (SPI_Module_TX_SOFTWARE_BUF_ENABLED) */

    /* Clear any data from the RX and TX FIFO */
    SPI_Module_ClearFIFO();

    /* Restore components block enable state */
    if(0u != SPI_Module_backup.enableState)
    {
        SPI_Module_Enable();
    }
}


/* [] END OF FILE */
