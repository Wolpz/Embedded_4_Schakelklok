/*******************************************************************************
* File Name: DebugLED.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DebugLED_H) /* Pins DebugLED_H */
#define CY_PINS_DebugLED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DebugLED_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DebugLED__PORT == 15 && ((DebugLED__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DebugLED_Write(uint8 value);
void    DebugLED_SetDriveMode(uint8 mode);
uint8   DebugLED_ReadDataReg(void);
uint8   DebugLED_Read(void);
void    DebugLED_SetInterruptMode(uint16 position, uint16 mode);
uint8   DebugLED_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DebugLED_SetDriveMode() function.
     *  @{
     */
        #define DebugLED_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DebugLED_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DebugLED_DM_RES_UP          PIN_DM_RES_UP
        #define DebugLED_DM_RES_DWN         PIN_DM_RES_DWN
        #define DebugLED_DM_OD_LO           PIN_DM_OD_LO
        #define DebugLED_DM_OD_HI           PIN_DM_OD_HI
        #define DebugLED_DM_STRONG          PIN_DM_STRONG
        #define DebugLED_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DebugLED_MASK               DebugLED__MASK
#define DebugLED_SHIFT              DebugLED__SHIFT
#define DebugLED_WIDTH              3u

/* Interrupt constants */
#if defined(DebugLED__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DebugLED_SetInterruptMode() function.
     *  @{
     */
        #define DebugLED_INTR_NONE      (uint16)(0x0000u)
        #define DebugLED_INTR_RISING    (uint16)(0x0001u)
        #define DebugLED_INTR_FALLING   (uint16)(0x0002u)
        #define DebugLED_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DebugLED_INTR_MASK      (0x01u) 
#endif /* (DebugLED__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DebugLED_PS                     (* (reg8 *) DebugLED__PS)
/* Data Register */
#define DebugLED_DR                     (* (reg8 *) DebugLED__DR)
/* Port Number */
#define DebugLED_PRT_NUM                (* (reg8 *) DebugLED__PRT) 
/* Connect to Analog Globals */                                                  
#define DebugLED_AG                     (* (reg8 *) DebugLED__AG)                       
/* Analog MUX bux enable */
#define DebugLED_AMUX                   (* (reg8 *) DebugLED__AMUX) 
/* Bidirectional Enable */                                                        
#define DebugLED_BIE                    (* (reg8 *) DebugLED__BIE)
/* Bit-mask for Aliased Register Access */
#define DebugLED_BIT_MASK               (* (reg8 *) DebugLED__BIT_MASK)
/* Bypass Enable */
#define DebugLED_BYP                    (* (reg8 *) DebugLED__BYP)
/* Port wide control signals */                                                   
#define DebugLED_CTL                    (* (reg8 *) DebugLED__CTL)
/* Drive Modes */
#define DebugLED_DM0                    (* (reg8 *) DebugLED__DM0) 
#define DebugLED_DM1                    (* (reg8 *) DebugLED__DM1)
#define DebugLED_DM2                    (* (reg8 *) DebugLED__DM2) 
/* Input Buffer Disable Override */
#define DebugLED_INP_DIS                (* (reg8 *) DebugLED__INP_DIS)
/* LCD Common or Segment Drive */
#define DebugLED_LCD_COM_SEG            (* (reg8 *) DebugLED__LCD_COM_SEG)
/* Enable Segment LCD */
#define DebugLED_LCD_EN                 (* (reg8 *) DebugLED__LCD_EN)
/* Slew Rate Control */
#define DebugLED_SLW                    (* (reg8 *) DebugLED__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DebugLED_PRTDSI__CAPS_SEL       (* (reg8 *) DebugLED__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DebugLED_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DebugLED__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DebugLED_PRTDSI__OE_SEL0        (* (reg8 *) DebugLED__PRTDSI__OE_SEL0) 
#define DebugLED_PRTDSI__OE_SEL1        (* (reg8 *) DebugLED__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DebugLED_PRTDSI__OUT_SEL0       (* (reg8 *) DebugLED__PRTDSI__OUT_SEL0) 
#define DebugLED_PRTDSI__OUT_SEL1       (* (reg8 *) DebugLED__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DebugLED_PRTDSI__SYNC_OUT       (* (reg8 *) DebugLED__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DebugLED__SIO_CFG)
    #define DebugLED_SIO_HYST_EN        (* (reg8 *) DebugLED__SIO_HYST_EN)
    #define DebugLED_SIO_REG_HIFREQ     (* (reg8 *) DebugLED__SIO_REG_HIFREQ)
    #define DebugLED_SIO_CFG            (* (reg8 *) DebugLED__SIO_CFG)
    #define DebugLED_SIO_DIFF           (* (reg8 *) DebugLED__SIO_DIFF)
#endif /* (DebugLED__SIO_CFG) */

/* Interrupt Registers */
#if defined(DebugLED__INTSTAT)
    #define DebugLED_INTSTAT            (* (reg8 *) DebugLED__INTSTAT)
    #define DebugLED_SNAP               (* (reg8 *) DebugLED__SNAP)
    
	#define DebugLED_0_INTTYPE_REG 		(* (reg8 *) DebugLED__0__INTTYPE)
	#define DebugLED_1_INTTYPE_REG 		(* (reg8 *) DebugLED__1__INTTYPE)
	#define DebugLED_2_INTTYPE_REG 		(* (reg8 *) DebugLED__2__INTTYPE)
#endif /* (DebugLED__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DebugLED_H */


/* [] END OF FILE */
