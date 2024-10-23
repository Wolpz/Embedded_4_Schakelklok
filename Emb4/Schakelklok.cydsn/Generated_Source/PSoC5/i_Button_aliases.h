/*******************************************************************************
* File Name: i_Button.h  
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

#if !defined(CY_PINS_i_Button_ALIASES_H) /* Pins i_Button_ALIASES_H */
#define CY_PINS_i_Button_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define i_Button_0			(i_Button__0__PC)
#define i_Button_0_INTR	((uint16)((uint16)0x0001u << i_Button__0__SHIFT))

#define i_Button_1			(i_Button__1__PC)
#define i_Button_1_INTR	((uint16)((uint16)0x0001u << i_Button__1__SHIFT))

#define i_Button_2			(i_Button__2__PC)
#define i_Button_2_INTR	((uint16)((uint16)0x0001u << i_Button__2__SHIFT))

#define i_Button_3			(i_Button__3__PC)
#define i_Button_3_INTR	((uint16)((uint16)0x0001u << i_Button__3__SHIFT))

#define i_Button_INTR_ALL	 ((uint16)(i_Button_0_INTR| i_Button_1_INTR| i_Button_2_INTR| i_Button_3_INTR))
#define i_Button_Up			(i_Button__Up__PC)
#define i_Button_Up_INTR	((uint16)((uint16)0x0001u << i_Button__0__SHIFT))

#define i_Button_Down			(i_Button__Down__PC)
#define i_Button_Down_INTR	((uint16)((uint16)0x0001u << i_Button__1__SHIFT))

#define i_Button_Back			(i_Button__Back__PC)
#define i_Button_Back_INTR	((uint16)((uint16)0x0001u << i_Button__2__SHIFT))

#define i_Button_OK			(i_Button__OK__PC)
#define i_Button_OK_INTR	((uint16)((uint16)0x0001u << i_Button__3__SHIFT))

#endif /* End Pins i_Button_ALIASES_H */


/* [] END OF FILE */
