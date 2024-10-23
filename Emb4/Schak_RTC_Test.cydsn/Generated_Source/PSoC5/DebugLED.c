/*******************************************************************************
* File Name: DebugLED.c  
* Version 2.20
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "DebugLED.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 DebugLED__PORT == 15 && ((DebugLED__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: DebugLED_Write
****************************************************************************//**
*
* \brief Writes the value to the physical port (data output register), masking
*  and shifting the bits appropriately. 
*
* The data output register controls the signal applied to the physical pin in 
* conjunction with the drive mode parameter. This function avoids changing 
* other bits in the port by using the appropriate method (read-modify-write or
* bit banding).
*
* <b>Note</b> This function should not be used on a hardware digital output pin 
* as it is driven by the hardware signal attached to it.
*
* \param value
*  Value to write to the component instance.
*
* \return 
*  None 
*
* \sideeffect
*  If you use read-modify-write operations that are not atomic; the Interrupt 
*  Service Routines (ISR) can cause corruption of this function. An ISR that 
*  interrupts this function and performs writes to the Pins component data 
*  register can cause corrupted port data. To avoid this issue, you should 
*  either use the Per-Pin APIs (primary method) or disable interrupts around 
*  this function.
*
* \funcusage
*  \snippet DebugLED_SUT.c usage_DebugLED_Write
*******************************************************************************/
void DebugLED_Write(uint8 value)
{
    uint8 staticBits = (DebugLED_DR & (uint8)(~DebugLED_MASK));
    DebugLED_DR = staticBits | ((uint8)(value << DebugLED_SHIFT) & DebugLED_MASK);
}


/*******************************************************************************
* Function Name: DebugLED_SetDriveMode
****************************************************************************//**
*
* \brief Sets the drive mode for each of the Pins component's pins.
* 
* <b>Note</b> This affects all pins in the Pins component instance. Use the
* Per-Pin APIs if you wish to control individual pin's drive modes.
*
* \param mode
*  Mode for the selected signals. Valid options are documented in 
*  \ref driveMode.
*
* \return
*  None
*
* \sideeffect
*  If you use read-modify-write operations that are not atomic, the ISR can
*  cause corruption of this function. An ISR that interrupts this function 
*  and performs writes to the Pins component Drive Mode registers can cause 
*  corrupted port data. To avoid this issue, you should either use the Per-Pin
*  APIs (primary method) or disable interrupts around this function.
*
* \funcusage
*  \snippet DebugLED_SUT.c usage_DebugLED_SetDriveMode
*******************************************************************************/
void DebugLED_SetDriveMode(uint8 mode)
{
	CyPins_SetPinDriveMode(DebugLED_0, mode);
	CyPins_SetPinDriveMode(DebugLED_1, mode);
	CyPins_SetPinDriveMode(DebugLED_2, mode);
}


/*******************************************************************************
* Function Name: DebugLED_Read
****************************************************************************//**
*
* \brief Reads the associated physical port (pin status register) and masks 
*  the required bits according to the width and bit position of the component
*  instance. 
*
* The pin's status register returns the current logic level present on the 
* physical pin.
*
* \return 
*  The current value for the pins in the component as a right justified number.
*
* \funcusage
*  \snippet DebugLED_SUT.c usage_DebugLED_Read  
*******************************************************************************/
uint8 DebugLED_Read(void)
{
    return (DebugLED_PS & DebugLED_MASK) >> DebugLED_SHIFT;
}


/*******************************************************************************
* Function Name: DebugLED_ReadDataReg
****************************************************************************//**
*
* \brief Reads the associated physical port's data output register and masks 
*  the correct bits according to the width and bit position of the component 
*  instance. 
*
* The data output register controls the signal applied to the physical pin in 
* conjunction with the drive mode parameter. This is not the same as the 
* preferred DebugLED_Read() API because the 
* DebugLED_ReadDataReg() reads the data register instead of the status 
* register. For output pins this is a useful function to determine the value 
* just written to the pin.
*
* \return 
*  The current value of the data register masked and shifted into a right 
*  justified number for the component instance.
*
* \funcusage
*  \snippet DebugLED_SUT.c usage_DebugLED_ReadDataReg 
*******************************************************************************/
uint8 DebugLED_ReadDataReg(void)
{
    return (DebugLED_DR & DebugLED_MASK) >> DebugLED_SHIFT;
}


/* If interrupt is connected for this Pins component */ 
#if defined(DebugLED_INTSTAT) 

    /*******************************************************************************
    * Function Name: DebugLED_SetInterruptMode
    ****************************************************************************//**
    *
    * \brief Configures the interrupt mode for each of the Pins component's
    *  pins. Alternatively you may set the interrupt mode for all the pins
    *  specified in the Pins component.
    *
    *  <b>Note</b> The interrupt is port-wide and therefore any enabled pin
    *  interrupt may trigger it.
    *
    * \param position
    *  The pin position as listed in the Pins component. You may OR these to be 
    *  able to configure the interrupt mode of multiple pins within a Pins 
    *  component. Or you may use DebugLED_INTR_ALL to configure the
    *  interrupt mode of all the pins in the Pins component.       
    *  - DebugLED_0_INTR       (First pin in the list)
    *  - DebugLED_1_INTR       (Second pin in the list)
    *  - ...
    *  - DebugLED_INTR_ALL     (All pins in Pins component)
    *
    * \param mode
    *  Interrupt mode for the selected pins. Valid options are documented in
    *  \ref intrMode.
    *
    * \return 
    *  None
    *  
    * \sideeffect
    *  It is recommended that the interrupt be disabled before calling this 
    *  function to avoid unintended interrupt requests. Note that the interrupt
    *  type is port wide, and therefore will trigger for any enabled pin on the 
    *  port.
    *
    * \funcusage
    *  \snippet DebugLED_SUT.c usage_DebugLED_SetInterruptMode
    *******************************************************************************/
    void DebugLED_SetInterruptMode(uint16 position, uint16 mode)
    {
		if((position & DebugLED_0_INTR) != 0u) 
		{ 
			 DebugLED_0_INTTYPE_REG = (uint8)mode; 
		} 
		if((position & DebugLED_1_INTR) != 0u) 
		{ 
			 DebugLED_1_INTTYPE_REG = (uint8)mode; 
		} 
		if((position & DebugLED_2_INTR) != 0u) 
		{ 
			 DebugLED_2_INTTYPE_REG = (uint8)mode; 
		}
    }
    
    
    /*******************************************************************************
    * Function Name: DebugLED_ClearInterrupt
    ****************************************************************************//**
    *
    * \brief Clears any active interrupts attached with the component and returns 
    *  the value of the interrupt status register allowing determination of which
    *  pins generated an interrupt event.
    *
    * \return 
    *  The right-shifted current value of the interrupt status register. Each pin 
    *  has one bit set if it generated an interrupt event. For example, bit 0 is 
    *  for pin 0 and bit 1 is for pin 1 of the Pins component.
    *  
    * \sideeffect
    *  Clears all bits of the physical port's interrupt status register, not just
    *  those associated with the Pins component.
    *
    * \funcusage
    *  \snippet DebugLED_SUT.c usage_DebugLED_ClearInterrupt
    *******************************************************************************/
    uint8 DebugLED_ClearInterrupt(void)
    {
        return (DebugLED_INTSTAT & DebugLED_MASK) >> DebugLED_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
