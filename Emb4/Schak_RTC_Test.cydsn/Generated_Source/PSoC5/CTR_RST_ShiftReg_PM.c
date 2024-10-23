/*******************************************************************************
* File Name: CTR_RST_ShiftReg_PM.c
* Version 2.30
*
* Description:
*  This file provides the API source code for sleep mode support for Shift
*  Register component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CTR_RST_ShiftReg.h"

static CTR_RST_ShiftReg_BACKUP_STRUCT CTR_RST_ShiftReg_backup =
{
    CTR_RST_ShiftReg_DISABLED,

    ((uint32) CTR_RST_ShiftReg_DEFAULT_A0),
    ((uint32) CTR_RST_ShiftReg_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint32) CTR_RST_ShiftReg_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: CTR_RST_ShiftReg_SaveConfig
********************************************************************************
*
* Summary:
*  Saves Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void CTR_RST_ShiftReg_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    CTR_RST_ShiftReg_backup.saveSrA0Reg   = CY_GET_REG32(CTR_RST_ShiftReg_SHIFT_REG_LSB_PTR);
    CTR_RST_ShiftReg_backup.saveSrA1Reg   = CY_GET_REG32(CTR_RST_ShiftReg_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        CTR_RST_ShiftReg_backup.saveSrIntMask = CTR_RST_ShiftReg_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: CTR_RST_ShiftReg_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void CTR_RST_ShiftReg_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG32(CTR_RST_ShiftReg_SHIFT_REG_LSB_PTR, CTR_RST_ShiftReg_backup.saveSrA0Reg);
    CY_SET_REG32(CTR_RST_ShiftReg_SHIFT_REG_VALUE_LSB_PTR, CTR_RST_ShiftReg_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        CTR_RST_ShiftReg_SR_STATUS_MASK = ((uint8) CTR_RST_ShiftReg_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: CTR_RST_ShiftReg_Sleep
********************************************************************************
*
* Summary:
*  Prepare the component to enter a Sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void CTR_RST_ShiftReg_Sleep(void) 
{
    CTR_RST_ShiftReg_backup.enableState = ((uint8) CTR_RST_ShiftReg_IS_ENABLED);

    CTR_RST_ShiftReg_Stop();
    CTR_RST_ShiftReg_SaveConfig();
}


/*******************************************************************************
* Function Name: CTR_RST_ShiftReg_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void CTR_RST_ShiftReg_Wakeup(void) 
{
    CTR_RST_ShiftReg_RestoreConfig();

    if(0u != CTR_RST_ShiftReg_backup.enableState)
    {
        CTR_RST_ShiftReg_Enable();
    }
}


/* [] END OF FILE */
