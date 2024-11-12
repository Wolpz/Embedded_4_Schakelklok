/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "..\Schakelklok.cydsn\Schakelklok_types.h"

#ifndef SCHAKELKLOK_DISPLAY_H 
    #define SCHAKELKLOK_DISPLAY_H 
    
    #define LCD_WIDTH   160 //LCD width
    #define LCD_HEIGHT  128 //LCD height
    // x2 bytes per pixel is around 40Mb of data
    #define DC_DATA 1
    #define DC_COMMAND 0

    #define SPI_READY 1

    void LCD_WriteData_Byte(UBYTE da); 
    void LCD_WriteData_Word(UWORD da);
    void LCD_WriteReg(UBYTE da);
    void LCD_DC_Setmode(uint8_t mode);

    void LCD_SetCursor(UWORD x1, UWORD y1, UWORD x2,UWORD y2);
    void LCD_SetUWORD(UWORD x, UWORD y, UWORD Color);

    int SPI_Ready();

    void LCD_Reset(void);
    void LCD_Init(void);
    void LCD_Clear(UWORD Color);
    void LCD_SetWindow(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD UWORD);
    void LCD_TransferBuffer(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD bufferArray[]);    
    
#endif
/* [] END OF FILE */
