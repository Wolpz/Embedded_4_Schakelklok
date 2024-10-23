/*******************************************************************************
* File Name: o_DebugLed.h  
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

#if !defined(CY_PINS_o_DebugLed_H) /* Pins o_DebugLed_H */
#define CY_PINS_o_DebugLed_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "o_DebugLed_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 o_DebugLed__PORT == 15 && ((o_DebugLed__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    o_DebugLed_Write(uint8 value);
void    o_DebugLed_SetDriveMode(uint8 mode);
uint8   o_DebugLed_ReadDataReg(void);
uint8   o_DebugLed_Read(void);
void    o_DebugLed_SetInterruptMode(uint16 position, uint16 mode);
uint8   o_DebugLed_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the o_DebugLed_SetDriveMode() function.
     *  @{
     */
        #define o_DebugLed_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define o_DebugLed_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define o_DebugLed_DM_RES_UP          PIN_DM_RES_UP
        #define o_DebugLed_DM_RES_DWN         PIN_DM_RES_DWN
        #define o_DebugLed_DM_OD_LO           PIN_DM_OD_LO
        #define o_DebugLed_DM_OD_HI           PIN_DM_OD_HI
        #define o_DebugLed_DM_STRONG          PIN_DM_STRONG
        #define o_DebugLed_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define o_DebugLed_MASK               o_DebugLed__MASK
#define o_DebugLed_SHIFT              o_DebugLed__SHIFT
#define o_DebugLed_WIDTH              3u

/* Interrupt constants */
#if defined(o_DebugLed__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in o_DebugLed_SetInterruptMode() function.
     *  @{
     */
        #define o_DebugLed_INTR_NONE      (uint16)(0x0000u)
        #define o_DebugLed_INTR_RISING    (uint16)(0x0001u)
        #define o_DebugLed_INTR_FALLING   (uint16)(0x0002u)
        #define o_DebugLed_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define o_DebugLed_INTR_MASK      (0x01u) 
#endif /* (o_DebugLed__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define o_DebugLed_PS                     (* (reg8 *) o_DebugLed__PS)
/* Data Register */
#define o_DebugLed_DR                     (* (reg8 *) o_DebugLed__DR)
/* Port Number */
#define o_DebugLed_PRT_NUM                (* (reg8 *) o_DebugLed__PRT) 
/* Connect to Analog Globals */                                                  
#define o_DebugLed_AG                     (* (reg8 *) o_DebugLed__AG)                       
/* Analog MUX bux enable */
#define o_DebugLed_AMUX                   (* (reg8 *) o_DebugLed__AMUX) 
/* Bidirectional Enable */                                                        
#define o_DebugLed_BIE                    (* (reg8 *) o_DebugLed__BIE)
/* Bit-mask for Aliased Register Access */
#define o_DebugLed_BIT_MASK               (* (reg8 *) o_DebugLed__BIT_MASK)
/* Bypass Enable */
#define o_DebugLed_BYP                    (* (reg8 *) o_DebugLed__BYP)
/* Port wide control signals */                                                   
#define o_DebugLed_CTL                    (* (reg8 *) o_DebugLed__CTL)
/* Drive Modes */
#define o_DebugLed_DM0                    (* (reg8 *) o_DebugLed__DM0) 
#define o_DebugLed_DM1                    (* (reg8 *) o_DebugLed__DM1)
#define o_DebugLed_DM2                    (* (reg8 *) o_DebugLed__DM2) 
/* Input Buffer Disable Override */
#define o_DebugLed_INP_DIS                (* (reg8 *) o_DebugLed__INP_DIS)
/* LCD Common or Segment Drive */
#define o_DebugLed_LCD_COM_SEG            (* (reg8 *) o_DebugLed__LCD_COM_SEG)
/* Enable Segment LCD */
#define o_DebugLed_LCD_EN                 (* (reg8 *) o_DebugLed__LCD_EN)
/* Slew Rate Control */
#define o_DebugLed_SLW                    (* (reg8 *) o_DebugLed__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define o_DebugLed_PRTDSI__CAPS_SEL       (* (reg8 *) o_DebugLed__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define o_DebugLed_PRTDSI__DBL_SYNC_IN    (* (reg8 *) o_DebugLed__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define o_DebugLed_PRTDSI__OE_SEL0        (* (reg8 *) o_DebugLed__PRTDSI__OE_SEL0) 
#define o_DebugLed_PRTDSI__OE_SEL1        (* (reg8 *) o_DebugLed__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define o_DebugLed_PRTDSI__OUT_SEL0       (* (reg8 *) o_DebugLed__PRTDSI__OUT_SEL0) 
#define o_DebugLed_PRTDSI__OUT_SEL1       (* (reg8 *) o_DebugLed__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define o_DebugLed_PRTDSI__SYNC_OUT       (* (reg8 *) o_DebugLed__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(o_DebugLed__SIO_CFG)
    #define o_DebugLed_SIO_HYST_EN        (* (reg8 *) o_DebugLed__SIO_HYST_EN)
    #define o_DebugLed_SIO_REG_HIFREQ     (* (reg8 *) o_DebugLed__SIO_REG_HIFREQ)
    #define o_DebugLed_SIO_CFG            (* (reg8 *) o_DebugLed__SIO_CFG)
    #define o_DebugLed_SIO_DIFF           (* (reg8 *) o_DebugLed__SIO_DIFF)
#endif /* (o_DebugLed__SIO_CFG) */

/* Interrupt Registers */
#if defined(o_DebugLed__INTSTAT)
    #define o_DebugLed_INTSTAT            (* (reg8 *) o_DebugLed__INTSTAT)
    #define o_DebugLed_SNAP               (* (reg8 *) o_DebugLed__SNAP)
    
	#define o_DebugLed_0_INTTYPE_REG 		(* (reg8 *) o_DebugLed__0__INTTYPE)
	#define o_DebugLed_1_INTTYPE_REG 		(* (reg8 *) o_DebugLed__1__INTTYPE)
	#define o_DebugLed_2_INTTYPE_REG 		(* (reg8 *) o_DebugLed__2__INTTYPE)
#endif /* (o_DebugLed__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_o_DebugLed_H */


/* [] END OF FILE */
