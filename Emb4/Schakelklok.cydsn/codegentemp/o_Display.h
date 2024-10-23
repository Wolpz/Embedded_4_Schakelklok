/*******************************************************************************
* File Name: o_Display.h  
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

#if !defined(CY_PINS_o_Display_H) /* Pins o_Display_H */
#define CY_PINS_o_Display_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "o_Display_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 o_Display__PORT == 15 && ((o_Display__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    o_Display_Write(uint8 value);
void    o_Display_SetDriveMode(uint8 mode);
uint8   o_Display_ReadDataReg(void);
uint8   o_Display_Read(void);
void    o_Display_SetInterruptMode(uint16 position, uint16 mode);
uint8   o_Display_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the o_Display_SetDriveMode() function.
     *  @{
     */
        #define o_Display_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define o_Display_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define o_Display_DM_RES_UP          PIN_DM_RES_UP
        #define o_Display_DM_RES_DWN         PIN_DM_RES_DWN
        #define o_Display_DM_OD_LO           PIN_DM_OD_LO
        #define o_Display_DM_OD_HI           PIN_DM_OD_HI
        #define o_Display_DM_STRONG          PIN_DM_STRONG
        #define o_Display_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define o_Display_MASK               o_Display__MASK
#define o_Display_SHIFT              o_Display__SHIFT
#define o_Display_WIDTH              5u

/* Interrupt constants */
#if defined(o_Display__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in o_Display_SetInterruptMode() function.
     *  @{
     */
        #define o_Display_INTR_NONE      (uint16)(0x0000u)
        #define o_Display_INTR_RISING    (uint16)(0x0001u)
        #define o_Display_INTR_FALLING   (uint16)(0x0002u)
        #define o_Display_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define o_Display_INTR_MASK      (0x01u) 
#endif /* (o_Display__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define o_Display_PS                     (* (reg8 *) o_Display__PS)
/* Data Register */
#define o_Display_DR                     (* (reg8 *) o_Display__DR)
/* Port Number */
#define o_Display_PRT_NUM                (* (reg8 *) o_Display__PRT) 
/* Connect to Analog Globals */                                                  
#define o_Display_AG                     (* (reg8 *) o_Display__AG)                       
/* Analog MUX bux enable */
#define o_Display_AMUX                   (* (reg8 *) o_Display__AMUX) 
/* Bidirectional Enable */                                                        
#define o_Display_BIE                    (* (reg8 *) o_Display__BIE)
/* Bit-mask for Aliased Register Access */
#define o_Display_BIT_MASK               (* (reg8 *) o_Display__BIT_MASK)
/* Bypass Enable */
#define o_Display_BYP                    (* (reg8 *) o_Display__BYP)
/* Port wide control signals */                                                   
#define o_Display_CTL                    (* (reg8 *) o_Display__CTL)
/* Drive Modes */
#define o_Display_DM0                    (* (reg8 *) o_Display__DM0) 
#define o_Display_DM1                    (* (reg8 *) o_Display__DM1)
#define o_Display_DM2                    (* (reg8 *) o_Display__DM2) 
/* Input Buffer Disable Override */
#define o_Display_INP_DIS                (* (reg8 *) o_Display__INP_DIS)
/* LCD Common or Segment Drive */
#define o_Display_LCD_COM_SEG            (* (reg8 *) o_Display__LCD_COM_SEG)
/* Enable Segment LCD */
#define o_Display_LCD_EN                 (* (reg8 *) o_Display__LCD_EN)
/* Slew Rate Control */
#define o_Display_SLW                    (* (reg8 *) o_Display__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define o_Display_PRTDSI__CAPS_SEL       (* (reg8 *) o_Display__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define o_Display_PRTDSI__DBL_SYNC_IN    (* (reg8 *) o_Display__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define o_Display_PRTDSI__OE_SEL0        (* (reg8 *) o_Display__PRTDSI__OE_SEL0) 
#define o_Display_PRTDSI__OE_SEL1        (* (reg8 *) o_Display__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define o_Display_PRTDSI__OUT_SEL0       (* (reg8 *) o_Display__PRTDSI__OUT_SEL0) 
#define o_Display_PRTDSI__OUT_SEL1       (* (reg8 *) o_Display__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define o_Display_PRTDSI__SYNC_OUT       (* (reg8 *) o_Display__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(o_Display__SIO_CFG)
    #define o_Display_SIO_HYST_EN        (* (reg8 *) o_Display__SIO_HYST_EN)
    #define o_Display_SIO_REG_HIFREQ     (* (reg8 *) o_Display__SIO_REG_HIFREQ)
    #define o_Display_SIO_CFG            (* (reg8 *) o_Display__SIO_CFG)
    #define o_Display_SIO_DIFF           (* (reg8 *) o_Display__SIO_DIFF)
#endif /* (o_Display__SIO_CFG) */

/* Interrupt Registers */
#if defined(o_Display__INTSTAT)
    #define o_Display_INTSTAT            (* (reg8 *) o_Display__INTSTAT)
    #define o_Display_SNAP               (* (reg8 *) o_Display__SNAP)
    
	#define o_Display_0_INTTYPE_REG 		(* (reg8 *) o_Display__0__INTTYPE)
	#define o_Display_1_INTTYPE_REG 		(* (reg8 *) o_Display__1__INTTYPE)
	#define o_Display_2_INTTYPE_REG 		(* (reg8 *) o_Display__2__INTTYPE)
	#define o_Display_3_INTTYPE_REG 		(* (reg8 *) o_Display__3__INTTYPE)
	#define o_Display_4_INTTYPE_REG 		(* (reg8 *) o_Display__4__INTTYPE)
#endif /* (o_Display__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_o_Display_H */


/* [] END OF FILE */
