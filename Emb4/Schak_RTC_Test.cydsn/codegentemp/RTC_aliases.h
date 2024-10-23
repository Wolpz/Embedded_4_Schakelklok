/*******************************************************************************
* File Name: RTC.h  
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

#if !defined(CY_PINS_RTC_ALIASES_H) /* Pins RTC_ALIASES_H */
#define CY_PINS_RTC_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define RTC_0			(RTC__0__PC)
#define RTC_0_INTR	((uint16)((uint16)0x0001u << RTC__0__SHIFT))

#define RTC_1			(RTC__1__PC)
#define RTC_1_INTR	((uint16)((uint16)0x0001u << RTC__1__SHIFT))

#define RTC_2			(RTC__2__PC)
#define RTC_2_INTR	((uint16)((uint16)0x0001u << RTC__2__SHIFT))

#define RTC_INTR_ALL	 ((uint16)(RTC_0_INTR| RTC_1_INTR| RTC_2_INTR))
#define RTC_f32kHz			(RTC__f32kHz__PC)
#define RTC_f32kHz_INTR	((uint16)((uint16)0x0001u << RTC__0__SHIFT))

#define RTC_RST			(RTC__RST__PC)
#define RTC_RST_INTR	((uint16)((uint16)0x0001u << RTC__1__SHIFT))

#define RTC_INT			(RTC__INT__PC)
#define RTC_INT_INTR	((uint16)((uint16)0x0001u << RTC__2__SHIFT))

#endif /* End Pins RTC_ALIASES_H */


/* [] END OF FILE */
