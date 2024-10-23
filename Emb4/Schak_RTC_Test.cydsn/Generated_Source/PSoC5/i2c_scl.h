/*******************************************************************************
* File Name: i2c_scl.h  
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

#if !defined(CY_PINS_i2c_scl_H) /* Pins i2c_scl_H */
#define CY_PINS_i2c_scl_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "i2c_scl_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 i2c_scl__PORT == 15 && ((i2c_scl__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    i2c_scl_Write(uint8 value);
void    i2c_scl_SetDriveMode(uint8 mode);
uint8   i2c_scl_ReadDataReg(void);
uint8   i2c_scl_Read(void);
void    i2c_scl_SetInterruptMode(uint16 position, uint16 mode);
uint8   i2c_scl_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the i2c_scl_SetDriveMode() function.
     *  @{
     */
        #define i2c_scl_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define i2c_scl_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define i2c_scl_DM_RES_UP          PIN_DM_RES_UP
        #define i2c_scl_DM_RES_DWN         PIN_DM_RES_DWN
        #define i2c_scl_DM_OD_LO           PIN_DM_OD_LO
        #define i2c_scl_DM_OD_HI           PIN_DM_OD_HI
        #define i2c_scl_DM_STRONG          PIN_DM_STRONG
        #define i2c_scl_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define i2c_scl_MASK               i2c_scl__MASK
#define i2c_scl_SHIFT              i2c_scl__SHIFT
#define i2c_scl_WIDTH              1u

/* Interrupt constants */
#if defined(i2c_scl__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in i2c_scl_SetInterruptMode() function.
     *  @{
     */
        #define i2c_scl_INTR_NONE      (uint16)(0x0000u)
        #define i2c_scl_INTR_RISING    (uint16)(0x0001u)
        #define i2c_scl_INTR_FALLING   (uint16)(0x0002u)
        #define i2c_scl_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define i2c_scl_INTR_MASK      (0x01u) 
#endif /* (i2c_scl__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define i2c_scl_PS                     (* (reg8 *) i2c_scl__PS)
/* Data Register */
#define i2c_scl_DR                     (* (reg8 *) i2c_scl__DR)
/* Port Number */
#define i2c_scl_PRT_NUM                (* (reg8 *) i2c_scl__PRT) 
/* Connect to Analog Globals */                                                  
#define i2c_scl_AG                     (* (reg8 *) i2c_scl__AG)                       
/* Analog MUX bux enable */
#define i2c_scl_AMUX                   (* (reg8 *) i2c_scl__AMUX) 
/* Bidirectional Enable */                                                        
#define i2c_scl_BIE                    (* (reg8 *) i2c_scl__BIE)
/* Bit-mask for Aliased Register Access */
#define i2c_scl_BIT_MASK               (* (reg8 *) i2c_scl__BIT_MASK)
/* Bypass Enable */
#define i2c_scl_BYP                    (* (reg8 *) i2c_scl__BYP)
/* Port wide control signals */                                                   
#define i2c_scl_CTL                    (* (reg8 *) i2c_scl__CTL)
/* Drive Modes */
#define i2c_scl_DM0                    (* (reg8 *) i2c_scl__DM0) 
#define i2c_scl_DM1                    (* (reg8 *) i2c_scl__DM1)
#define i2c_scl_DM2                    (* (reg8 *) i2c_scl__DM2) 
/* Input Buffer Disable Override */
#define i2c_scl_INP_DIS                (* (reg8 *) i2c_scl__INP_DIS)
/* LCD Common or Segment Drive */
#define i2c_scl_LCD_COM_SEG            (* (reg8 *) i2c_scl__LCD_COM_SEG)
/* Enable Segment LCD */
#define i2c_scl_LCD_EN                 (* (reg8 *) i2c_scl__LCD_EN)
/* Slew Rate Control */
#define i2c_scl_SLW                    (* (reg8 *) i2c_scl__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define i2c_scl_PRTDSI__CAPS_SEL       (* (reg8 *) i2c_scl__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define i2c_scl_PRTDSI__DBL_SYNC_IN    (* (reg8 *) i2c_scl__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define i2c_scl_PRTDSI__OE_SEL0        (* (reg8 *) i2c_scl__PRTDSI__OE_SEL0) 
#define i2c_scl_PRTDSI__OE_SEL1        (* (reg8 *) i2c_scl__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define i2c_scl_PRTDSI__OUT_SEL0       (* (reg8 *) i2c_scl__PRTDSI__OUT_SEL0) 
#define i2c_scl_PRTDSI__OUT_SEL1       (* (reg8 *) i2c_scl__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define i2c_scl_PRTDSI__SYNC_OUT       (* (reg8 *) i2c_scl__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(i2c_scl__SIO_CFG)
    #define i2c_scl_SIO_HYST_EN        (* (reg8 *) i2c_scl__SIO_HYST_EN)
    #define i2c_scl_SIO_REG_HIFREQ     (* (reg8 *) i2c_scl__SIO_REG_HIFREQ)
    #define i2c_scl_SIO_CFG            (* (reg8 *) i2c_scl__SIO_CFG)
    #define i2c_scl_SIO_DIFF           (* (reg8 *) i2c_scl__SIO_DIFF)
#endif /* (i2c_scl__SIO_CFG) */

/* Interrupt Registers */
#if defined(i2c_scl__INTSTAT)
    #define i2c_scl_INTSTAT            (* (reg8 *) i2c_scl__INTSTAT)
    #define i2c_scl_SNAP               (* (reg8 *) i2c_scl__SNAP)
    
	#define i2c_scl_0_INTTYPE_REG 		(* (reg8 *) i2c_scl__0__INTTYPE)
#endif /* (i2c_scl__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_i2c_scl_H */


/* [] END OF FILE */
