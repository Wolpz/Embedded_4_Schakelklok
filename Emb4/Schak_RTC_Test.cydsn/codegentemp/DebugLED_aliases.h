/*******************************************************************************
* File Name: DebugLED.h  
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

#if !defined(CY_PINS_DebugLED_ALIASES_H) /* Pins DebugLED_ALIASES_H */
#define CY_PINS_DebugLED_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define DebugLED_0			(DebugLED__0__PC)
#define DebugLED_0_INTR	((uint16)((uint16)0x0001u << DebugLED__0__SHIFT))

#define DebugLED_1			(DebugLED__1__PC)
#define DebugLED_1_INTR	((uint16)((uint16)0x0001u << DebugLED__1__SHIFT))

#define DebugLED_2			(DebugLED__2__PC)
#define DebugLED_2_INTR	((uint16)((uint16)0x0001u << DebugLED__2__SHIFT))

#define DebugLED_INTR_ALL	 ((uint16)(DebugLED_0_INTR| DebugLED_1_INTR| DebugLED_2_INTR))
#define DebugLED_Grn			(DebugLED__Grn__PC)
#define DebugLED_Grn_INTR	((uint16)((uint16)0x0001u << DebugLED__0__SHIFT))

#define DebugLED_Blu			(DebugLED__Blu__PC)
#define DebugLED_Blu_INTR	((uint16)((uint16)0x0001u << DebugLED__1__SHIFT))

#define DebugLED_Red			(DebugLED__Red__PC)
#define DebugLED_Red_INTR	((uint16)((uint16)0x0001u << DebugLED__2__SHIFT))

#endif /* End Pins DebugLED_ALIASES_H */


/* [] END OF FILE */
