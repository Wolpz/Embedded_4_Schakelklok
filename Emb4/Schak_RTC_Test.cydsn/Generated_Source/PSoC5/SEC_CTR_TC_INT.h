/*******************************************************************************
* File Name: SEC_CTR_TC_INT.h
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
#if !defined(CY_ISR_SEC_CTR_TC_INT_H)
#define CY_ISR_SEC_CTR_TC_INT_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void SEC_CTR_TC_INT_Start(void);
void SEC_CTR_TC_INT_StartEx(cyisraddress address);
void SEC_CTR_TC_INT_Stop(void);

CY_ISR_PROTO(SEC_CTR_TC_INT_Interrupt);

void SEC_CTR_TC_INT_SetVector(cyisraddress address);
cyisraddress SEC_CTR_TC_INT_GetVector(void);

void SEC_CTR_TC_INT_SetPriority(uint8 priority);
uint8 SEC_CTR_TC_INT_GetPriority(void);

void SEC_CTR_TC_INT_Enable(void);
uint8 SEC_CTR_TC_INT_GetState(void);
void SEC_CTR_TC_INT_Disable(void);

void SEC_CTR_TC_INT_SetPending(void);
void SEC_CTR_TC_INT_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the SEC_CTR_TC_INT ISR. */
#define SEC_CTR_TC_INT_INTC_VECTOR            ((reg32 *) SEC_CTR_TC_INT__INTC_VECT)

/* Address of the SEC_CTR_TC_INT ISR priority. */
#define SEC_CTR_TC_INT_INTC_PRIOR             ((reg8 *) SEC_CTR_TC_INT__INTC_PRIOR_REG)

/* Priority of the SEC_CTR_TC_INT interrupt. */
#define SEC_CTR_TC_INT_INTC_PRIOR_NUMBER      SEC_CTR_TC_INT__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable SEC_CTR_TC_INT interrupt. */
#define SEC_CTR_TC_INT_INTC_SET_EN            ((reg32 *) SEC_CTR_TC_INT__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the SEC_CTR_TC_INT interrupt. */
#define SEC_CTR_TC_INT_INTC_CLR_EN            ((reg32 *) SEC_CTR_TC_INT__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the SEC_CTR_TC_INT interrupt state to pending. */
#define SEC_CTR_TC_INT_INTC_SET_PD            ((reg32 *) SEC_CTR_TC_INT__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the SEC_CTR_TC_INT interrupt. */
#define SEC_CTR_TC_INT_INTC_CLR_PD            ((reg32 *) SEC_CTR_TC_INT__INTC_CLR_PD_REG)


#endif /* CY_ISR_SEC_CTR_TC_INT_H */


/* [] END OF FILE */
