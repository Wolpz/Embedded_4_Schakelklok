/*******************************************************************************
* File Name: MISO_NC.h  
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

#if !defined(CY_PINS_MISO_NC_H) /* Pins MISO_NC_H */
#define CY_PINS_MISO_NC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MISO_NC_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MISO_NC__PORT == 15 && ((MISO_NC__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MISO_NC_Write(uint8 value);
void    MISO_NC_SetDriveMode(uint8 mode);
uint8   MISO_NC_ReadDataReg(void);
uint8   MISO_NC_Read(void);
void    MISO_NC_SetInterruptMode(uint16 position, uint16 mode);
uint8   MISO_NC_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MISO_NC_SetDriveMode() function.
     *  @{
     */
        #define MISO_NC_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MISO_NC_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MISO_NC_DM_RES_UP          PIN_DM_RES_UP
        #define MISO_NC_DM_RES_DWN         PIN_DM_RES_DWN
        #define MISO_NC_DM_OD_LO           PIN_DM_OD_LO
        #define MISO_NC_DM_OD_HI           PIN_DM_OD_HI
        #define MISO_NC_DM_STRONG          PIN_DM_STRONG
        #define MISO_NC_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MISO_NC_MASK               MISO_NC__MASK
#define MISO_NC_SHIFT              MISO_NC__SHIFT
#define MISO_NC_WIDTH              1u

/* Interrupt constants */
#if defined(MISO_NC__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MISO_NC_SetInterruptMode() function.
     *  @{
     */
        #define MISO_NC_INTR_NONE      (uint16)(0x0000u)
        #define MISO_NC_INTR_RISING    (uint16)(0x0001u)
        #define MISO_NC_INTR_FALLING   (uint16)(0x0002u)
        #define MISO_NC_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MISO_NC_INTR_MASK      (0x01u) 
#endif /* (MISO_NC__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MISO_NC_PS                     (* (reg8 *) MISO_NC__PS)
/* Data Register */
#define MISO_NC_DR                     (* (reg8 *) MISO_NC__DR)
/* Port Number */
#define MISO_NC_PRT_NUM                (* (reg8 *) MISO_NC__PRT) 
/* Connect to Analog Globals */                                                  
#define MISO_NC_AG                     (* (reg8 *) MISO_NC__AG)                       
/* Analog MUX bux enable */
#define MISO_NC_AMUX                   (* (reg8 *) MISO_NC__AMUX) 
/* Bidirectional Enable */                                                        
#define MISO_NC_BIE                    (* (reg8 *) MISO_NC__BIE)
/* Bit-mask for Aliased Register Access */
#define MISO_NC_BIT_MASK               (* (reg8 *) MISO_NC__BIT_MASK)
/* Bypass Enable */
#define MISO_NC_BYP                    (* (reg8 *) MISO_NC__BYP)
/* Port wide control signals */                                                   
#define MISO_NC_CTL                    (* (reg8 *) MISO_NC__CTL)
/* Drive Modes */
#define MISO_NC_DM0                    (* (reg8 *) MISO_NC__DM0) 
#define MISO_NC_DM1                    (* (reg8 *) MISO_NC__DM1)
#define MISO_NC_DM2                    (* (reg8 *) MISO_NC__DM2) 
/* Input Buffer Disable Override */
#define MISO_NC_INP_DIS                (* (reg8 *) MISO_NC__INP_DIS)
/* LCD Common or Segment Drive */
#define MISO_NC_LCD_COM_SEG            (* (reg8 *) MISO_NC__LCD_COM_SEG)
/* Enable Segment LCD */
#define MISO_NC_LCD_EN                 (* (reg8 *) MISO_NC__LCD_EN)
/* Slew Rate Control */
#define MISO_NC_SLW                    (* (reg8 *) MISO_NC__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MISO_NC_PRTDSI__CAPS_SEL       (* (reg8 *) MISO_NC__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MISO_NC_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MISO_NC__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MISO_NC_PRTDSI__OE_SEL0        (* (reg8 *) MISO_NC__PRTDSI__OE_SEL0) 
#define MISO_NC_PRTDSI__OE_SEL1        (* (reg8 *) MISO_NC__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MISO_NC_PRTDSI__OUT_SEL0       (* (reg8 *) MISO_NC__PRTDSI__OUT_SEL0) 
#define MISO_NC_PRTDSI__OUT_SEL1       (* (reg8 *) MISO_NC__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MISO_NC_PRTDSI__SYNC_OUT       (* (reg8 *) MISO_NC__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MISO_NC__SIO_CFG)
    #define MISO_NC_SIO_HYST_EN        (* (reg8 *) MISO_NC__SIO_HYST_EN)
    #define MISO_NC_SIO_REG_HIFREQ     (* (reg8 *) MISO_NC__SIO_REG_HIFREQ)
    #define MISO_NC_SIO_CFG            (* (reg8 *) MISO_NC__SIO_CFG)
    #define MISO_NC_SIO_DIFF           (* (reg8 *) MISO_NC__SIO_DIFF)
#endif /* (MISO_NC__SIO_CFG) */

/* Interrupt Registers */
#if defined(MISO_NC__INTSTAT)
    #define MISO_NC_INTSTAT            (* (reg8 *) MISO_NC__INTSTAT)
    #define MISO_NC_SNAP               (* (reg8 *) MISO_NC__SNAP)
    
	#define MISO_NC_0_INTTYPE_REG 		(* (reg8 *) MISO_NC__0__INTTYPE)
#endif /* (MISO_NC__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MISO_NC_H */


/* [] END OF FILE */
