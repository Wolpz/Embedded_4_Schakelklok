/*******************************************************************************
* File Name: mS_COUNTER.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "mS_COUNTER.h"

uint8 mS_COUNTER_initVar = 0u;


/*******************************************************************************
* Function Name: mS_COUNTER_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void mS_COUNTER_Init(void) 
{
        #if (!mS_COUNTER_UsingFixedFunction && !mS_COUNTER_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!mS_COUNTER_UsingFixedFunction && !mS_COUNTER_ControlRegRemoved) */
        
        #if(!mS_COUNTER_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 mS_COUNTER_interruptState;
        #endif /* (!mS_COUNTER_UsingFixedFunction) */
        
        #if (mS_COUNTER_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            mS_COUNTER_CONTROL &= mS_COUNTER_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                mS_COUNTER_CONTROL2 &= ((uint8)(~mS_COUNTER_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                mS_COUNTER_CONTROL3 &= ((uint8)(~mS_COUNTER_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (mS_COUNTER_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                mS_COUNTER_CONTROL |= mS_COUNTER_ONESHOT;
            #endif /* (mS_COUNTER_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            mS_COUNTER_CONTROL2 |= mS_COUNTER_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            mS_COUNTER_RT1 &= ((uint8)(~mS_COUNTER_RT1_MASK));
            mS_COUNTER_RT1 |= mS_COUNTER_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            mS_COUNTER_RT1 &= ((uint8)(~mS_COUNTER_SYNCDSI_MASK));
            mS_COUNTER_RT1 |= mS_COUNTER_SYNCDSI_EN;

        #else
            #if(!mS_COUNTER_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = mS_COUNTER_CONTROL & ((uint8)(~mS_COUNTER_CTRL_CMPMODE_MASK));
            mS_COUNTER_CONTROL = ctrl | mS_COUNTER_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = mS_COUNTER_CONTROL & ((uint8)(~mS_COUNTER_CTRL_CAPMODE_MASK));
            
            #if( 0 != mS_COUNTER_CAPTURE_MODE_CONF)
                mS_COUNTER_CONTROL = ctrl | mS_COUNTER_DEFAULT_CAPTURE_MODE;
            #else
                mS_COUNTER_CONTROL = ctrl;
            #endif /* 0 != mS_COUNTER_CAPTURE_MODE */ 
            
            #endif /* (!mS_COUNTER_ControlRegRemoved) */
        #endif /* (mS_COUNTER_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!mS_COUNTER_UsingFixedFunction)
            mS_COUNTER_ClearFIFO();
        #endif /* (!mS_COUNTER_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        mS_COUNTER_WritePeriod(mS_COUNTER_INIT_PERIOD_VALUE);
        #if (!(mS_COUNTER_UsingFixedFunction && (CY_PSOC5A)))
            mS_COUNTER_WriteCounter(mS_COUNTER_INIT_COUNTER_VALUE);
        #endif /* (!(mS_COUNTER_UsingFixedFunction && (CY_PSOC5A))) */
        mS_COUNTER_SetInterruptMode(mS_COUNTER_INIT_INTERRUPTS_MASK);
        
        #if (!mS_COUNTER_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)mS_COUNTER_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            mS_COUNTER_WriteCompare(mS_COUNTER_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            mS_COUNTER_interruptState = CyEnterCriticalSection();
            
            mS_COUNTER_STATUS_AUX_CTRL |= mS_COUNTER_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(mS_COUNTER_interruptState);
            
        #endif /* (!mS_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: mS_COUNTER_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void mS_COUNTER_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (mS_COUNTER_UsingFixedFunction)
        mS_COUNTER_GLOBAL_ENABLE |= mS_COUNTER_BLOCK_EN_MASK;
        mS_COUNTER_GLOBAL_STBY_ENABLE |= mS_COUNTER_BLOCK_STBY_EN_MASK;
    #endif /* (mS_COUNTER_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!mS_COUNTER_ControlRegRemoved || mS_COUNTER_UsingFixedFunction)
        mS_COUNTER_CONTROL |= mS_COUNTER_CTRL_ENABLE;                
    #endif /* (!mS_COUNTER_ControlRegRemoved || mS_COUNTER_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: mS_COUNTER_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  mS_COUNTER_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void mS_COUNTER_Start(void) 
{
    if(mS_COUNTER_initVar == 0u)
    {
        mS_COUNTER_Init();
        
        mS_COUNTER_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    mS_COUNTER_Enable();        
}


/*******************************************************************************
* Function Name: mS_COUNTER_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void mS_COUNTER_Stop(void) 
{
    /* Disable Counter */
    #if(!mS_COUNTER_ControlRegRemoved || mS_COUNTER_UsingFixedFunction)
        mS_COUNTER_CONTROL &= ((uint8)(~mS_COUNTER_CTRL_ENABLE));        
    #endif /* (!mS_COUNTER_ControlRegRemoved || mS_COUNTER_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (mS_COUNTER_UsingFixedFunction)
        mS_COUNTER_GLOBAL_ENABLE &= ((uint8)(~mS_COUNTER_BLOCK_EN_MASK));
        mS_COUNTER_GLOBAL_STBY_ENABLE &= ((uint8)(~mS_COUNTER_BLOCK_STBY_EN_MASK));
    #endif /* (mS_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: mS_COUNTER_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void mS_COUNTER_SetInterruptMode(uint8 interruptsMask) 
{
    mS_COUNTER_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: mS_COUNTER_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   mS_COUNTER_ReadStatusRegister(void) 
{
    return mS_COUNTER_STATUS;
}


#if(!mS_COUNTER_ControlRegRemoved)
/*******************************************************************************
* Function Name: mS_COUNTER_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   mS_COUNTER_ReadControlRegister(void) 
{
    return mS_COUNTER_CONTROL;
}


/*******************************************************************************
* Function Name: mS_COUNTER_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    mS_COUNTER_WriteControlRegister(uint8 control) 
{
    mS_COUNTER_CONTROL = control;
}

#endif  /* (!mS_COUNTER_ControlRegRemoved) */


#if (!(mS_COUNTER_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: mS_COUNTER_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void mS_COUNTER_WriteCounter(uint32 counter) \
                                   
{
    #if(mS_COUNTER_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (mS_COUNTER_GLOBAL_ENABLE & mS_COUNTER_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        mS_COUNTER_GLOBAL_ENABLE |= mS_COUNTER_BLOCK_EN_MASK;
        CY_SET_REG16(mS_COUNTER_COUNTER_LSB_PTR, (uint16)counter);
        mS_COUNTER_GLOBAL_ENABLE &= ((uint8)(~mS_COUNTER_BLOCK_EN_MASK));
    #else
        CY_SET_REG24(mS_COUNTER_COUNTER_LSB_PTR, counter);
    #endif /* (mS_COUNTER_UsingFixedFunction) */
}
#endif /* (!(mS_COUNTER_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: mS_COUNTER_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) The present value of the counter.
*
*******************************************************************************/
uint32 mS_COUNTER_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(mS_COUNTER_UsingFixedFunction)
		(void)CY_GET_REG16(mS_COUNTER_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(mS_COUNTER_COUNTER_LSB_PTR_8BIT);
	#endif/* (mS_COUNTER_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(mS_COUNTER_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(mS_COUNTER_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG24(mS_COUNTER_STATICCOUNT_LSB_PTR));
    #endif /* (mS_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: mS_COUNTER_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint32) Present Capture value.
*
*******************************************************************************/
uint32 mS_COUNTER_ReadCapture(void) 
{
    #if(mS_COUNTER_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(mS_COUNTER_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG24(mS_COUNTER_STATICCOUNT_LSB_PTR));
    #endif /* (mS_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: mS_COUNTER_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint32) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void mS_COUNTER_WritePeriod(uint32 period) 
{
    #if(mS_COUNTER_UsingFixedFunction)
        CY_SET_REG16(mS_COUNTER_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG24(mS_COUNTER_PERIOD_LSB_PTR, period);
    #endif /* (mS_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: mS_COUNTER_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) Present period value.
*
*******************************************************************************/
uint32 mS_COUNTER_ReadPeriod(void) 
{
    #if(mS_COUNTER_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(mS_COUNTER_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG24(mS_COUNTER_PERIOD_LSB_PTR));
    #endif /* (mS_COUNTER_UsingFixedFunction) */
}


#if (!mS_COUNTER_UsingFixedFunction)
/*******************************************************************************
* Function Name: mS_COUNTER_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void mS_COUNTER_WriteCompare(uint32 compare) \
                                   
{
    #if(mS_COUNTER_UsingFixedFunction)
        CY_SET_REG16(mS_COUNTER_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG24(mS_COUNTER_COMPARE_LSB_PTR, compare);
    #endif /* (mS_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: mS_COUNTER_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint32) Present compare value.
*
*******************************************************************************/
uint32 mS_COUNTER_ReadCompare(void) 
{
    return (CY_GET_REG24(mS_COUNTER_COMPARE_LSB_PTR));
}


#if (mS_COUNTER_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: mS_COUNTER_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void mS_COUNTER_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    mS_COUNTER_CONTROL &= ((uint8)(~mS_COUNTER_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    mS_COUNTER_CONTROL |= compareMode;
}
#endif  /* (mS_COUNTER_COMPARE_MODE_SOFTWARE) */


#if (mS_COUNTER_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: mS_COUNTER_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void mS_COUNTER_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    mS_COUNTER_CONTROL &= ((uint8)(~mS_COUNTER_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    mS_COUNTER_CONTROL |= ((uint8)((uint8)captureMode << mS_COUNTER_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (mS_COUNTER_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: mS_COUNTER_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void mS_COUNTER_ClearFIFO(void) 
{

    while(0u != (mS_COUNTER_ReadStatusRegister() & mS_COUNTER_STATUS_FIFONEMP))
    {
        (void)mS_COUNTER_ReadCapture();
    }

}
#endif  /* (!mS_COUNTER_UsingFixedFunction) */


/* [] END OF FILE */

