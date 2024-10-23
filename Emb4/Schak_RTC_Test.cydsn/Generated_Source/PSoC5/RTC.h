/*******************************************************************************
* File Name: RTC.h  
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

#if !defined(CY_PINS_RTC_H) /* Pins RTC_H */
#define CY_PINS_RTC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RTC_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RTC__PORT == 15 && ((RTC__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RTC_Write(uint8 value);
void    RTC_SetDriveMode(uint8 mode);
uint8   RTC_ReadDataReg(void);
uint8   RTC_Read(void);
void    RTC_SetInterruptMode(uint16 position, uint16 mode);
uint8   RTC_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RTC_SetDriveMode() function.
     *  @{
     */
        #define RTC_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RTC_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RTC_DM_RES_UP          PIN_DM_RES_UP
        #define RTC_DM_RES_DWN         PIN_DM_RES_DWN
        #define RTC_DM_OD_LO           PIN_DM_OD_LO
        #define RTC_DM_OD_HI           PIN_DM_OD_HI
        #define RTC_DM_STRONG          PIN_DM_STRONG
        #define RTC_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RTC_MASK               RTC__MASK
#define RTC_SHIFT              RTC__SHIFT
#define RTC_WIDTH              3u

/* Interrupt constants */
#if defined(RTC__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RTC_SetInterruptMode() function.
     *  @{
     */
        #define RTC_INTR_NONE      (uint16)(0x0000u)
        #define RTC_INTR_RISING    (uint16)(0x0001u)
        #define RTC_INTR_FALLING   (uint16)(0x0002u)
        #define RTC_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RTC_INTR_MASK      (0x01u) 
#endif /* (RTC__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RTC_PS                     (* (reg8 *) RTC__PS)
/* Data Register */
#define RTC_DR                     (* (reg8 *) RTC__DR)
/* Port Number */
#define RTC_PRT_NUM                (* (reg8 *) RTC__PRT) 
/* Connect to Analog Globals */                                                  
#define RTC_AG                     (* (reg8 *) RTC__AG)                       
/* Analog MUX bux enable */
#define RTC_AMUX                   (* (reg8 *) RTC__AMUX) 
/* Bidirectional Enable */                                                        
#define RTC_BIE                    (* (reg8 *) RTC__BIE)
/* Bit-mask for Aliased Register Access */
#define RTC_BIT_MASK               (* (reg8 *) RTC__BIT_MASK)
/* Bypass Enable */
#define RTC_BYP                    (* (reg8 *) RTC__BYP)
/* Port wide control signals */                                                   
#define RTC_CTL                    (* (reg8 *) RTC__CTL)
/* Drive Modes */
#define RTC_DM0                    (* (reg8 *) RTC__DM0) 
#define RTC_DM1                    (* (reg8 *) RTC__DM1)
#define RTC_DM2                    (* (reg8 *) RTC__DM2) 
/* Input Buffer Disable Override */
#define RTC_INP_DIS                (* (reg8 *) RTC__INP_DIS)
/* LCD Common or Segment Drive */
#define RTC_LCD_COM_SEG            (* (reg8 *) RTC__LCD_COM_SEG)
/* Enable Segment LCD */
#define RTC_LCD_EN                 (* (reg8 *) RTC__LCD_EN)
/* Slew Rate Control */
#define RTC_SLW                    (* (reg8 *) RTC__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RTC_PRTDSI__CAPS_SEL       (* (reg8 *) RTC__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RTC_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RTC__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RTC_PRTDSI__OE_SEL0        (* (reg8 *) RTC__PRTDSI__OE_SEL0) 
#define RTC_PRTDSI__OE_SEL1        (* (reg8 *) RTC__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RTC_PRTDSI__OUT_SEL0       (* (reg8 *) RTC__PRTDSI__OUT_SEL0) 
#define RTC_PRTDSI__OUT_SEL1       (* (reg8 *) RTC__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RTC_PRTDSI__SYNC_OUT       (* (reg8 *) RTC__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RTC__SIO_CFG)
    #define RTC_SIO_HYST_EN        (* (reg8 *) RTC__SIO_HYST_EN)
    #define RTC_SIO_REG_HIFREQ     (* (reg8 *) RTC__SIO_REG_HIFREQ)
    #define RTC_SIO_CFG            (* (reg8 *) RTC__SIO_CFG)
    #define RTC_SIO_DIFF           (* (reg8 *) RTC__SIO_DIFF)
#endif /* (RTC__SIO_CFG) */

/* Interrupt Registers */
#if defined(RTC__INTSTAT)
    #define RTC_INTSTAT            (* (reg8 *) RTC__INTSTAT)
    #define RTC_SNAP               (* (reg8 *) RTC__SNAP)
    
	#define RTC_0_INTTYPE_REG 		(* (reg8 *) RTC__0__INTTYPE)
	#define RTC_1_INTTYPE_REG 		(* (reg8 *) RTC__1__INTTYPE)
	#define RTC_2_INTTYPE_REG 		(* (reg8 *) RTC__2__INTTYPE)
#endif /* (RTC__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RTC_H */


/* [] END OF FILE */
