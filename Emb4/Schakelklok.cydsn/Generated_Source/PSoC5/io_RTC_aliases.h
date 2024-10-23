/*******************************************************************************
* File Name: io_RTC.h  
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

#if !defined(CY_PINS_io_RTC_ALIASES_H) /* Pins io_RTC_ALIASES_H */
#define CY_PINS_io_RTC_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define io_RTC_0			(io_RTC__0__PC)
#define io_RTC_0_INTR	((uint16)((uint16)0x0001u << io_RTC__0__SHIFT))

#define io_RTC_1			(io_RTC__1__PC)
#define io_RTC_1_INTR	((uint16)((uint16)0x0001u << io_RTC__1__SHIFT))

#define io_RTC_2			(io_RTC__2__PC)
#define io_RTC_2_INTR	((uint16)((uint16)0x0001u << io_RTC__2__SHIFT))

#define io_RTC_3			(io_RTC__3__PC)
#define io_RTC_3_INTR	((uint16)((uint16)0x0001u << io_RTC__3__SHIFT))

#define io_RTC_INTR_ALL	 ((uint16)(io_RTC_0_INTR| io_RTC_1_INTR| io_RTC_2_INTR| io_RTC_3_INTR))
#define io_RTC_RST			(io_RTC__RST__PC)
#define io_RTC_RST_INTR	((uint16)((uint16)0x0001u << io_RTC__0__SHIFT))

#define io_RTC_INT			(io_RTC__INT__PC)
#define io_RTC_INT_INTR	((uint16)((uint16)0x0001u << io_RTC__1__SHIFT))

#define io_RTC_SDA			(io_RTC__SDA__PC)
#define io_RTC_SDA_INTR	((uint16)((uint16)0x0001u << io_RTC__2__SHIFT))

#define io_RTC_SCL			(io_RTC__SCL__PC)
#define io_RTC_SCL_INTR	((uint16)((uint16)0x0001u << io_RTC__3__SHIFT))

#endif /* End Pins io_RTC_ALIASES_H */


/* [] END OF FILE */
