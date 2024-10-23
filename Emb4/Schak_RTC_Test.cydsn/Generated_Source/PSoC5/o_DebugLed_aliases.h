/*******************************************************************************
* File Name: o_DebugLed.h  
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

#if !defined(CY_PINS_o_DebugLed_ALIASES_H) /* Pins o_DebugLed_ALIASES_H */
#define CY_PINS_o_DebugLed_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define o_DebugLed_0			(o_DebugLed__0__PC)
#define o_DebugLed_0_INTR	((uint16)((uint16)0x0001u << o_DebugLed__0__SHIFT))

#define o_DebugLed_1			(o_DebugLed__1__PC)
#define o_DebugLed_1_INTR	((uint16)((uint16)0x0001u << o_DebugLed__1__SHIFT))

#define o_DebugLed_2			(o_DebugLed__2__PC)
#define o_DebugLed_2_INTR	((uint16)((uint16)0x0001u << o_DebugLed__2__SHIFT))

#define o_DebugLed_INTR_ALL	 ((uint16)(o_DebugLed_0_INTR| o_DebugLed_1_INTR| o_DebugLed_2_INTR))
#define o_DebugLed_Red			(o_DebugLed__Red__PC)
#define o_DebugLed_Red_INTR	((uint16)((uint16)0x0001u << o_DebugLed__0__SHIFT))

#define o_DebugLed_Blu			(o_DebugLed__Blu__PC)
#define o_DebugLed_Blu_INTR	((uint16)((uint16)0x0001u << o_DebugLed__1__SHIFT))

#define o_DebugLed_Grn			(o_DebugLed__Grn__PC)
#define o_DebugLed_Grn_INTR	((uint16)((uint16)0x0001u << o_DebugLed__2__SHIFT))

#endif /* End Pins o_DebugLed_ALIASES_H */


/* [] END OF FILE */
