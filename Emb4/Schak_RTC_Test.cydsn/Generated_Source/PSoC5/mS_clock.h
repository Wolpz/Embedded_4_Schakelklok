/*******************************************************************************
* File Name: mS_clock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_mS_clock_H)
#define CY_CLOCK_mS_clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void mS_clock_Start(void) ;
void mS_clock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void mS_clock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void mS_clock_StandbyPower(uint8 state) ;
void mS_clock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 mS_clock_GetDividerRegister(void) ;
void mS_clock_SetModeRegister(uint8 modeBitMask) ;
void mS_clock_ClearModeRegister(uint8 modeBitMask) ;
uint8 mS_clock_GetModeRegister(void) ;
void mS_clock_SetSourceRegister(uint8 clkSource) ;
uint8 mS_clock_GetSourceRegister(void) ;
#if defined(mS_clock__CFG3)
void mS_clock_SetPhaseRegister(uint8 clkPhase) ;
uint8 mS_clock_GetPhaseRegister(void) ;
#endif /* defined(mS_clock__CFG3) */

#define mS_clock_Enable()                       mS_clock_Start()
#define mS_clock_Disable()                      mS_clock_Stop()
#define mS_clock_SetDivider(clkDivider)         mS_clock_SetDividerRegister(clkDivider, 1u)
#define mS_clock_SetDividerValue(clkDivider)    mS_clock_SetDividerRegister((clkDivider) - 1u, 1u)
#define mS_clock_SetMode(clkMode)               mS_clock_SetModeRegister(clkMode)
#define mS_clock_SetSource(clkSource)           mS_clock_SetSourceRegister(clkSource)
#if defined(mS_clock__CFG3)
#define mS_clock_SetPhase(clkPhase)             mS_clock_SetPhaseRegister(clkPhase)
#define mS_clock_SetPhaseValue(clkPhase)        mS_clock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(mS_clock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define mS_clock_CLKEN              (* (reg8 *) mS_clock__PM_ACT_CFG)
#define mS_clock_CLKEN_PTR          ((reg8 *) mS_clock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define mS_clock_CLKSTBY            (* (reg8 *) mS_clock__PM_STBY_CFG)
#define mS_clock_CLKSTBY_PTR        ((reg8 *) mS_clock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define mS_clock_DIV_LSB            (* (reg8 *) mS_clock__CFG0)
#define mS_clock_DIV_LSB_PTR        ((reg8 *) mS_clock__CFG0)
#define mS_clock_DIV_PTR            ((reg16 *) mS_clock__CFG0)

/* Clock MSB divider configuration register. */
#define mS_clock_DIV_MSB            (* (reg8 *) mS_clock__CFG1)
#define mS_clock_DIV_MSB_PTR        ((reg8 *) mS_clock__CFG1)

/* Mode and source configuration register */
#define mS_clock_MOD_SRC            (* (reg8 *) mS_clock__CFG2)
#define mS_clock_MOD_SRC_PTR        ((reg8 *) mS_clock__CFG2)

#if defined(mS_clock__CFG3)
/* Analog clock phase configuration register */
#define mS_clock_PHASE              (* (reg8 *) mS_clock__CFG3)
#define mS_clock_PHASE_PTR          ((reg8 *) mS_clock__CFG3)
#endif /* defined(mS_clock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define mS_clock_CLKEN_MASK         mS_clock__PM_ACT_MSK
#define mS_clock_CLKSTBY_MASK       mS_clock__PM_STBY_MSK

/* CFG2 field masks */
#define mS_clock_SRC_SEL_MSK        mS_clock__CFG2_SRC_SEL_MASK
#define mS_clock_MODE_MASK          (~(mS_clock_SRC_SEL_MSK))

#if defined(mS_clock__CFG3)
/* CFG3 phase mask */
#define mS_clock_PHASE_MASK         mS_clock__CFG3_PHASE_DLY_MASK
#endif /* defined(mS_clock__CFG3) */

#endif /* CY_CLOCK_mS_clock_H */


/* [] END OF FILE */
