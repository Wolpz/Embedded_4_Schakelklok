/*******************************************************************************
* File Name: ms_Counter_CAPT_INT.h
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
#if !defined(CY_ISR_ms_Counter_CAPT_INT_H)
#define CY_ISR_ms_Counter_CAPT_INT_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ms_Counter_CAPT_INT_Start(void);
void ms_Counter_CAPT_INT_StartEx(cyisraddress address);
void ms_Counter_CAPT_INT_Stop(void);

CY_ISR_PROTO(ms_Counter_CAPT_INT_Interrupt);

void ms_Counter_CAPT_INT_SetVector(cyisraddress address);
cyisraddress ms_Counter_CAPT_INT_GetVector(void);

void ms_Counter_CAPT_INT_SetPriority(uint8 priority);
uint8 ms_Counter_CAPT_INT_GetPriority(void);

void ms_Counter_CAPT_INT_Enable(void);
uint8 ms_Counter_CAPT_INT_GetState(void);
void ms_Counter_CAPT_INT_Disable(void);

void ms_Counter_CAPT_INT_SetPending(void);
void ms_Counter_CAPT_INT_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ms_Counter_CAPT_INT ISR. */
#define ms_Counter_CAPT_INT_INTC_VECTOR            ((reg32 *) ms_Counter_CAPT_INT__INTC_VECT)

/* Address of the ms_Counter_CAPT_INT ISR priority. */
#define ms_Counter_CAPT_INT_INTC_PRIOR             ((reg8 *) ms_Counter_CAPT_INT__INTC_PRIOR_REG)

/* Priority of the ms_Counter_CAPT_INT interrupt. */
#define ms_Counter_CAPT_INT_INTC_PRIOR_NUMBER      ms_Counter_CAPT_INT__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ms_Counter_CAPT_INT interrupt. */
#define ms_Counter_CAPT_INT_INTC_SET_EN            ((reg32 *) ms_Counter_CAPT_INT__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ms_Counter_CAPT_INT interrupt. */
#define ms_Counter_CAPT_INT_INTC_CLR_EN            ((reg32 *) ms_Counter_CAPT_INT__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ms_Counter_CAPT_INT interrupt state to pending. */
#define ms_Counter_CAPT_INT_INTC_SET_PD            ((reg32 *) ms_Counter_CAPT_INT__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ms_Counter_CAPT_INT interrupt. */
#define ms_Counter_CAPT_INT_INTC_CLR_PD            ((reg32 *) ms_Counter_CAPT_INT__INTC_CLR_PD_REG)


#endif /* CY_ISR_ms_Counter_CAPT_INT_H */


/* [] END OF FILE */
