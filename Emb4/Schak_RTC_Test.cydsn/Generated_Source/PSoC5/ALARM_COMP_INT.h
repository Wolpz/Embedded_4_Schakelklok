/*******************************************************************************
* File Name: ALARM_COMP_INT.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_ALARM_COMP_INT_H)
#define CY_ISR_ALARM_COMP_INT_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ALARM_COMP_INT_Start(void);
void ALARM_COMP_INT_StartEx(cyisraddress address);
void ALARM_COMP_INT_Stop(void);

CY_ISR_PROTO(ALARM_COMP_INT_Interrupt);

void ALARM_COMP_INT_SetVector(cyisraddress address);
cyisraddress ALARM_COMP_INT_GetVector(void);

void ALARM_COMP_INT_SetPriority(uint8 priority);
uint8 ALARM_COMP_INT_GetPriority(void);

void ALARM_COMP_INT_Enable(void);
uint8 ALARM_COMP_INT_GetState(void);
void ALARM_COMP_INT_Disable(void);

void ALARM_COMP_INT_SetPending(void);
void ALARM_COMP_INT_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ALARM_COMP_INT ISR. */
#define ALARM_COMP_INT_INTC_VECTOR            ((reg32 *) ALARM_COMP_INT__INTC_VECT)

/* Address of the ALARM_COMP_INT ISR priority. */
#define ALARM_COMP_INT_INTC_PRIOR             ((reg8 *) ALARM_COMP_INT__INTC_PRIOR_REG)

/* Priority of the ALARM_COMP_INT interrupt. */
#define ALARM_COMP_INT_INTC_PRIOR_NUMBER      ALARM_COMP_INT__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ALARM_COMP_INT interrupt. */
#define ALARM_COMP_INT_INTC_SET_EN            ((reg32 *) ALARM_COMP_INT__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ALARM_COMP_INT interrupt. */
#define ALARM_COMP_INT_INTC_CLR_EN            ((reg32 *) ALARM_COMP_INT__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ALARM_COMP_INT interrupt state to pending. */
#define ALARM_COMP_INT_INTC_SET_PD            ((reg32 *) ALARM_COMP_INT__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ALARM_COMP_INT interrupt. */
#define ALARM_COMP_INT_INTC_CLR_PD            ((reg32 *) ALARM_COMP_INT__INTC_CLR_PD_REG)


#endif /* CY_ISR_ALARM_COMP_INT_H */


/* [] END OF FILE */
