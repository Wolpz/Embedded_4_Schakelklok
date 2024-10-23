/*******************************************************************************
* File Name: Button.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Button_ALIASES_H) /* Pins Button_ALIASES_H */
#define CY_PINS_Button_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Button_0			(Button__0__PC)
#define Button_0_INTR	((uint16)((uint16)0x0001u << Button__0__SHIFT))

#define Button_1			(Button__1__PC)
#define Button_1_INTR	((uint16)((uint16)0x0001u << Button__1__SHIFT))

#define Button_2			(Button__2__PC)
#define Button_2_INTR	((uint16)((uint16)0x0001u << Button__2__SHIFT))

#define Button_3			(Button__3__PC)
#define Button_3_INTR	((uint16)((uint16)0x0001u << Button__3__SHIFT))

#define Button_INTR_ALL	 ((uint16)(Button_0_INTR| Button_1_INTR| Button_2_INTR| Button_3_INTR))
#define Button_UP			(Button__UP__PC)
#define Button_UP_INTR	((uint16)((uint16)0x0001u << Button__0__SHIFT))

#define Button_DOWN			(Button__DOWN__PC)
#define Button_DOWN_INTR	((uint16)((uint16)0x0001u << Button__1__SHIFT))

#define Button_BACK			(Button__BACK__PC)
#define Button_BACK_INTR	((uint16)((uint16)0x0001u << Button__2__SHIFT))

#define Button_OK			(Button__OK__PC)
#define Button_OK_INTR	((uint16)((uint16)0x0001u << Button__3__SHIFT))

#endif /* End Pins Button_ALIASES_H */


/* [] END OF FILE */
