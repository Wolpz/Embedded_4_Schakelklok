/*******************************************************************************
* File Name: o_Display.h  
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

#if !defined(CY_PINS_o_Display_ALIASES_H) /* Pins o_Display_ALIASES_H */
#define CY_PINS_o_Display_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define o_Display_0			(o_Display__0__PC)
#define o_Display_0_INTR	((uint16)((uint16)0x0001u << o_Display__0__SHIFT))

#define o_Display_1			(o_Display__1__PC)
#define o_Display_1_INTR	((uint16)((uint16)0x0001u << o_Display__1__SHIFT))

#define o_Display_2			(o_Display__2__PC)
#define o_Display_2_INTR	((uint16)((uint16)0x0001u << o_Display__2__SHIFT))

#define o_Display_3			(o_Display__3__PC)
#define o_Display_3_INTR	((uint16)((uint16)0x0001u << o_Display__3__SHIFT))

#define o_Display_4			(o_Display__4__PC)
#define o_Display_4_INTR	((uint16)((uint16)0x0001u << o_Display__4__SHIFT))

#define o_Display_INTR_ALL	 ((uint16)(o_Display_0_INTR| o_Display_1_INTR| o_Display_2_INTR| o_Display_3_INTR| o_Display_4_INTR))
#define o_Display_RST			(o_Display__RST__PC)
#define o_Display_RST_INTR	((uint16)((uint16)0x0001u << o_Display__0__SHIFT))

#define o_Display_DC			(o_Display__DC__PC)
#define o_Display_DC_INTR	((uint16)((uint16)0x0001u << o_Display__1__SHIFT))

#define o_Display_CS			(o_Display__CS__PC)
#define o_Display_CS_INTR	((uint16)((uint16)0x0001u << o_Display__2__SHIFT))

#define o_Display_SCLK			(o_Display__SCLK__PC)
#define o_Display_SCLK_INTR	((uint16)((uint16)0x0001u << o_Display__3__SHIFT))

#define o_Display_MOSI			(o_Display__MOSI__PC)
#define o_Display_MOSI_INTR	((uint16)((uint16)0x0001u << o_Display__4__SHIFT))

#endif /* End Pins o_Display_ALIASES_H */


/* [] END OF FILE */
