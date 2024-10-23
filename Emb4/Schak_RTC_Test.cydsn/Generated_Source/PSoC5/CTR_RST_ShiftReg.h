/*******************************************************************************
* File Name: CTR_RST_ShiftReg.h
* Version 2.30
*
* Description:
*  This header file contains definitions associated with the Shift Register
*  component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


#if !defined(CY_SHIFTREG_CTR_RST_ShiftReg_H)
#define CY_SHIFTREG_CTR_RST_ShiftReg_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define CTR_RST_ShiftReg_FIFO_SIZE          (4u)
#define CTR_RST_ShiftReg_USE_INPUT_FIFO     (0u)
#define CTR_RST_ShiftReg_USE_OUTPUT_FIFO    (0u)
#define CTR_RST_ShiftReg_SR_SIZE            (32u)


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;

    uint32 saveSrA0Reg;
    uint32 saveSrA1Reg;

    #if(CY_UDB_V0)
        uint32 saveSrIntMask;
    #endif /* (CY_UDB_V0) */

} CTR_RST_ShiftReg_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  CTR_RST_ShiftReg_Start(void)                              ;
void  CTR_RST_ShiftReg_Stop(void)                               ;
void  CTR_RST_ShiftReg_Init(void)                               ;
void  CTR_RST_ShiftReg_Enable(void)                             ;
void  CTR_RST_ShiftReg_RestoreConfig(void)                      ;
void  CTR_RST_ShiftReg_SaveConfig(void)                         ;
void  CTR_RST_ShiftReg_Sleep(void)                              ;
void  CTR_RST_ShiftReg_Wakeup(void)                             ;
void  CTR_RST_ShiftReg_EnableInt(void)                          ;
void  CTR_RST_ShiftReg_DisableInt(void)                         ;
void  CTR_RST_ShiftReg_SetIntMode(uint8 interruptSource)        ;
uint8 CTR_RST_ShiftReg_GetIntStatus(void)                       ;
void  CTR_RST_ShiftReg_WriteRegValue(uint32 shiftData) \
                                                                ;
uint32 CTR_RST_ShiftReg_ReadRegValue(void) ;
uint8    CTR_RST_ShiftReg_GetFIFOStatus(uint8 fifoId)           ;

#if(0u != CTR_RST_ShiftReg_USE_INPUT_FIFO)
    cystatus CTR_RST_ShiftReg_WriteData(uint32 shiftData) \
                                                                ;
#endif /* (0u != CTR_RST_ShiftReg_USE_INPUT_FIFO) */

#if(0u != CTR_RST_ShiftReg_USE_OUTPUT_FIFO)
    uint32 CTR_RST_ShiftReg_ReadData(void) ;
#endif /* (0u != CTR_RST_ShiftReg_USE_OUTPUT_FIFO) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 CTR_RST_ShiftReg_initVar;


/***************************************
*           API Constants
***************************************/

#define CTR_RST_ShiftReg_LOAD                   (0x01u)
#define CTR_RST_ShiftReg_STORE                  (0x02u)
#define CTR_RST_ShiftReg_RESET                  (0x04u)

#define CTR_RST_ShiftReg_IN_FIFO                (0x01u)
#define CTR_RST_ShiftReg_OUT_FIFO               (0x02u)

#define CTR_RST_ShiftReg_RET_FIFO_FULL          (0x00u)

/* This define is obsolete */
#define CTR_RST_ShiftReg_RET_FIFO_NOT_EMPTY     (0x01u)

#define CTR_RST_ShiftReg_RET_FIFO_PARTIAL       (0x01u)
#define CTR_RST_ShiftReg_RET_FIFO_EMPTY         (0x02u)
#define CTR_RST_ShiftReg_RET_FIFO_NOT_DEFINED   (0xFEu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define CTR_RST_ShiftReg__LEFT 0
#define CTR_RST_ShiftReg__RIGHT 1



/***************************************
*    Initial Parameter Constants
***************************************/

#define CTR_RST_ShiftReg_SR_MASK    (0xFFFFFFFFu) /* Unsigned is added to parameter */
#define CTR_RST_ShiftReg_INT_SRC    (0u)
#define CTR_RST_ShiftReg_DIRECTION  (1u)


/***************************************
*             Registers
***************************************/

/* Control register */
#define CTR_RST_ShiftReg_SR_CONTROL_REG (* (reg8 *) \
                                           CTR_RST_ShiftReg_bSR_SyncCtl_CtrlReg__CONTROL_REG)
#define CTR_RST_ShiftReg_SR_CONTROL_PTR (  (reg8 *) \
                                           CTR_RST_ShiftReg_bSR_SyncCtl_CtrlReg__CONTROL_REG)

/* Status register */
#define CTR_RST_ShiftReg_SR_STATUS_REG      (* (reg8 *) CTR_RST_ShiftReg_bSR_StsReg__STATUS_REG)
#define CTR_RST_ShiftReg_SR_STATUS_PTR      (  (reg8 *) CTR_RST_ShiftReg_bSR_StsReg__STATUS_REG)

/* Interrupt status register */
#define CTR_RST_ShiftReg_SR_STATUS_MASK_REG (* (reg8 *) CTR_RST_ShiftReg_bSR_StsReg__MASK_REG)
#define CTR_RST_ShiftReg_SR_STATUS_MASK_PTR (  (reg8 *) CTR_RST_ShiftReg_bSR_StsReg__MASK_REG)

/* Aux control register */
#define CTR_RST_ShiftReg_SR_AUX_CONTROL_REG (* (reg8 *) CTR_RST_ShiftReg_bSR_StsReg__STATUS_AUX_CTL_REG)
#define CTR_RST_ShiftReg_SR_AUX_CONTROL_PTR (  (reg8 *) CTR_RST_ShiftReg_bSR_StsReg__STATUS_AUX_CTL_REG)

/* A1 register: only used to implement capture function */
#define CTR_RST_ShiftReg_SHIFT_REG_CAPTURE_PTR    ( (reg8 *) \
                                        CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__A1_REG )

#if(CY_PSOC3 || CY_PSOC5)
    #define CTR_RST_ShiftReg_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                        CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__F0_REG )

    #define CTR_RST_ShiftReg_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                        CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__A0_REG )

    #define CTR_RST_ShiftReg_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                        CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__A1_REG )

    #define CTR_RST_ShiftReg_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                        CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__F1_REG )

#else
    #if(CTR_RST_ShiftReg_SR_SIZE <= 8u) /* 8bit - ShiftReg */
        #define CTR_RST_ShiftReg_IN_FIFO_VAL_LSB_PTR        ( (reg8 *) \
                                        CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__F0_REG )

        #define CTR_RST_ShiftReg_SHIFT_REG_LSB_PTR          ( (reg8 *) \
                                        CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__A0_REG )

        #define CTR_RST_ShiftReg_SHIFT_REG_VALUE_LSB_PTR    ( (reg8 *) \
                                        CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__A1_REG )

        #define CTR_RST_ShiftReg_OUT_FIFO_VAL_LSB_PTR       ( (reg8 *) \
                                        CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__F1_REG )

    #elif(CTR_RST_ShiftReg_SR_SIZE <= 16u) /* 16bit - ShiftReg */
        #define CTR_RST_ShiftReg_IN_FIFO_VAL_LSB_PTR        ( (reg16 *) \
                                  CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__16BIT_F0_REG )

        #define CTR_RST_ShiftReg_SHIFT_REG_LSB_PTR          ( (reg16 *) \
                                  CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__16BIT_A0_REG )

        #define CTR_RST_ShiftReg_SHIFT_REG_VALUE_LSB_PTR    ( (reg16 *) \
                                  CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__16BIT_A1_REG )

        #define CTR_RST_ShiftReg_OUT_FIFO_VAL_LSB_PTR       ( (reg16 *) \
                                  CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__16BIT_F1_REG )


    #elif(CTR_RST_ShiftReg_SR_SIZE <= 24u) /* 24bit - ShiftReg */
        #define CTR_RST_ShiftReg_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                        CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__F0_REG )

        #define CTR_RST_ShiftReg_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                        CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__A0_REG )

        #define CTR_RST_ShiftReg_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                        CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__A1_REG )

        #define CTR_RST_ShiftReg_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                        CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__F1_REG )

    #else /* 32bit - ShiftReg */
        #define CTR_RST_ShiftReg_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                  CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__32BIT_F0_REG )

        #define CTR_RST_ShiftReg_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                  CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__32BIT_A0_REG )

        #define CTR_RST_ShiftReg_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                  CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__32BIT_A1_REG )

        #define CTR_RST_ShiftReg_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                  CTR_RST_ShiftReg_bSR_sC32_BShiftRegDp_u0__32BIT_F1_REG )

    #endif  /* (CTR_RST_ShiftReg_SR_SIZE <= 8u) */
#endif      /* (CY_PSOC3 || CY_PSOC5) */


/***************************************
*       Register Constants
***************************************/

#define CTR_RST_ShiftReg_INTERRUPTS_ENABLE      (0x10u)
#define CTR_RST_ShiftReg_LOAD_INT_EN            (0x01u)
#define CTR_RST_ShiftReg_STORE_INT_EN           (0x02u)
#define CTR_RST_ShiftReg_RESET_INT_EN           (0x04u)
#define CTR_RST_ShiftReg_CLK_EN                 (0x01u)

#define CTR_RST_ShiftReg_RESET_INT_EN_MASK      (0xFBu)
#define CTR_RST_ShiftReg_LOAD_INT_EN_MASK       (0xFEu)
#define CTR_RST_ShiftReg_STORE_INT_EN_MASK      (0xFDu)
#define CTR_RST_ShiftReg_INTS_EN_MASK           (0x07u)

#define CTR_RST_ShiftReg_OUT_FIFO_CLR_BIT       (0x02u)

#if(0u != CTR_RST_ShiftReg_USE_INPUT_FIFO)

    #define CTR_RST_ShiftReg_IN_FIFO_MASK       (0x18u)

    #define CTR_RST_ShiftReg_IN_FIFO_FULL       (0x00u)
    #define CTR_RST_ShiftReg_IN_FIFO_EMPTY      (0x01u)
    #define CTR_RST_ShiftReg_IN_FIFO_PARTIAL    (0x02u)
    
    /* This define is obsolete */
    #define CTR_RST_ShiftReg_IN_FIFO_NOT_EMPTY  (0x02u)
    
#endif /* (0u != CTR_RST_ShiftReg_USE_INPUT_FIFO) */

#define CTR_RST_ShiftReg_OUT_FIFO_MASK          (0x60u)

#define CTR_RST_ShiftReg_OUT_FIFO_EMPTY         (0x00u)
#define CTR_RST_ShiftReg_OUT_FIFO_FULL          (0x01u)
#define CTR_RST_ShiftReg_OUT_FIFO_PARTIAL       (0x02u)

/* This define is obsolete */
#define CTR_RST_ShiftReg_OUT_FIFO_NOT_EMPTY     (0x02u)

#define CTR_RST_ShiftReg_IN_FIFO_SHIFT_MASK     (0x03u)
#define CTR_RST_ShiftReg_OUT_FIFO_SHIFT_MASK    (0x05u)

#define CTR_RST_ShiftReg_DISABLED               (0u)
#define CTR_RST_ShiftReg_DEFAULT_A0             (0u)
#define CTR_RST_ShiftReg_DEFAULT_A1             (0u)


/***************************************
*       Macros
***************************************/

#define CTR_RST_ShiftReg_IS_ENABLED         (0u != (CTR_RST_ShiftReg_SR_CONTROL & CTR_RST_ShiftReg_CLK_EN))

#define CTR_RST_ShiftReg_GET_OUT_FIFO_STS   ((CTR_RST_ShiftReg_SR_STATUS & CTR_RST_ShiftReg_OUT_FIFO_MASK) >> \
                                              CTR_RST_ShiftReg_OUT_FIFO_SHIFT_MASK)

#define CTR_RST_ShiftReg_GET_IN_FIFO_STS    ((CTR_RST_ShiftReg_SR_STATUS & CTR_RST_ShiftReg_IN_FIFO_MASK)  >> \
                                              CTR_RST_ShiftReg_IN_FIFO_SHIFT_MASK)


/***************************************
*       Obsolete
***************************************/

/* Following code are OBSOLETE and must not be used 
 * starting from ShiftReg 2.20 
 */

#define CTR_RST_ShiftReg_SR_CONTROL     (CTR_RST_ShiftReg_SR_CONTROL_REG)
#define CTR_RST_ShiftReg_SR_STATUS      (CTR_RST_ShiftReg_SR_STATUS_REG)
#define CTR_RST_ShiftReg_SR_STATUS_MASK (CTR_RST_ShiftReg_SR_STATUS_MASK_REG)
#define CTR_RST_ShiftReg_SR_AUX_CONTROL (CTR_RST_ShiftReg_SR_AUX_CONTROL_REG)

#define CTR_RST_ShiftReg_IN_FIFO_SHFT_MASK  (CTR_RST_ShiftReg_IN_FIFO_SHIFT_MASK)
#define CTR_RST_ShiftReg_OUT_FIFO_SHFT_MASK (CTR_RST_ShiftReg_OUT_FIFO_SHFIT_MASK)

#define CTR_RST_ShiftReg_RET_FIFO_BAD_PARAM (0xFFu)

#endif /* (CY_SHIFTREG_CTR_RST_ShiftReg_H) */


/* [] END OF FILE */
