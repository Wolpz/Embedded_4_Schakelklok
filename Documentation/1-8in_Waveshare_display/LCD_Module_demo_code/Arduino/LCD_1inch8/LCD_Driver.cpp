/*****************************************************************************
  | File        :   LCD_Driver.c
  | Author      :   Waveshare team
  | Function    :   Electronic paper driver
  | Info        :
  ----------------
  | This version:   V1.0
  | Date        :   2018-11-18
  | Info        :
  #
  # Permission is hereby granted, free of UBYTEge, to any person obtaining a copy
  # of this software and associated documnetation files (the "Software"), to deal
  # in the Software without restriction, including without limitation the rights
  # to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  # copies of the Software, and to permit persons to  whom the Software is
  # furished to do so, subject to the following conditions:
  #
  # The above copyright notice and this permission notice shall be included in
  # all copies or substantial portions of the Software.
  #
  # THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  # IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  # FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  # AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  # LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  # OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  # THE SOFTWARE.
  #
******************************************************************************/
#include "LCD_Driver.h"

/*******************************************************************************
  function:
  Hardware reset
*******************************************************************************/
static void LCD_Reset(void)
{
  DEV_Digital_Write(DEV_RST_PIN, 0);
  DEV_Delay_ms(20);
  DEV_Digital_Write(DEV_RST_PIN, 0);
  DEV_Delay_ms(20);
  DEV_Digital_Write(DEV_RST_PIN, 1);
  DEV_Delay_ms(20);
}

/*******************************************************************************
  function:
  Setting backlight
  parameter :
    value : Range 0~255   Duty cycle is value/255
*******************************************************************************/
void LCD_SetBacklight(UWORD Value)
{
  DEV_Set_BL(DEV_BL_PIN, Value);
}

/*******************************************************************************
  function:
    Write register address and data
*******************************************************************************/
void LCD_WriteData_Byte(UBYTE da)
{
  DEV_Digital_Write(DEV_CS_PIN, 0);
  DEV_Digital_Write(DEV_DC_PIN, 1);
  DEV_SPI_WRITE(da);
  DEV_Digital_Write(DEV_CS_PIN, 1);
}

void LCD_WriteData_Word(UWORD da)
{
  UBYTE i = (da >> 8) & 0xff;
  DEV_Digital_Write(DEV_CS_PIN, 0);
  DEV_Digital_Write(DEV_DC_PIN, 1);
  DEV_SPI_WRITE(i);
  DEV_SPI_WRITE(da);
  DEV_Digital_Write(DEV_CS_PIN, 1);
}

void LCD_WriteReg(UBYTE da)
{
  DEV_Digital_Write(DEV_CS_PIN, 0);
  DEV_Digital_Write(DEV_DC_PIN, 0);
  DEV_SPI_WRITE(da);
  //DEV_Digital_Write(DEV_CS_PIN,1);
}

/******************************************************************************
  function:
    Common register initialization
******************************************************************************/
void LCD_Init(void)
{
  LCD_Reset();

  //************* Start Initial Sequence **********//
  LCD_WriteReg(0xB1);       // FRMCTR1: Normal mode, full colours p155
  LCD_WriteData_Byte(0x01); // RTNA set 1-line period: 0001
  LCD_WriteData_Byte(0x2C); // FPA: Front porch
  LCD_WriteData_Byte(0x2D); // BPA: Back porch

  LCD_WriteReg(0xB2);       // FRMCTR2: In Idle Mode (8-colors) p155
  LCD_WriteData_Byte(0x01); // RTNB: set 1 line period 0001
  LCD_WriteData_Byte(0x2C); // FPB: Front porch
  LCD_WriteData_Byte(0x2D); // BPB: Back porch

  LCD_WriteReg(0xB3);       // FRMCTR3: In partial mode + full colours p155 (Partial update??)
  LCD_WriteData_Byte(0x01); // RTNC
  LCD_WriteData_Byte(0x2C); // FPC
  LCD_WriteData_Byte(0x2D); // BPC
  LCD_WriteData_Byte(0x01); // RTND
  LCD_WriteData_Byte(0x2C); // FPD
  LCD_WriteData_Byte(0x2D); // BPD

  LCD_WriteReg(0xB4);       // INVCTR: Display inverion control: Column inversion p155 p162
  LCD_WriteData_Byte(0x07); // Set inversion: currently 111

  //ST7735R Power Sequence
  LCD_WriteReg(0xC0);       // PWCTR1 Power control setting p156
  LCD_WriteData_Byte(0xA2); // AVDD 2:0, VRHP 4:0
  LCD_WriteData_Byte(0x02); // 000 + VRHN 4:0 set GVDD voltage
  LCD_WriteData_Byte(0x84); // MODE 1:0 + 000100
  LCD_WriteReg(0xC1);       // PWCTR2 Power control setting p156
  LCD_WriteData_Byte(0xC5); // VGH2 1:0 + -- + VGLS EL 1:0 + VGHB T 1:0

  LCD_WriteReg(0xC2);       // PWCTR3: Power control in normal mode(full colours) p156
  LCD_WriteData_Byte(0x0A); // DCA (dc booster) 9:8 + SAPA 2:0 + APA (opamp adj) 2:0 
  LCD_WriteData_Byte(0x00); // DCA (dc booster) 7:0

  LCD_WriteReg(0xC3);       // PWCTR4: Power control idle mode(8colours) p156
  LCD_WriteData_Byte(0x8A); // DCB (dc booster) 9:8 + SAPB 2:0 + APB (opamp adjust) 2:0 
  LCD_WriteData_Byte(0x2A); // DCB (dc booster) 7:0
  
  LCD_WriteReg(0xC4);       // PWCTR5: Power control partial mode + fullcolours
  LCD_WriteData_Byte(0x8A); // DCC (dc booster) 9:8 + SAPC 2:0 + APC (opamp adjust) 2:0 
  LCD_WriteData_Byte(0xEE); // DCC (dc booster) 7:0

  LCD_WriteReg(0xC5);       // VMCTR1: VCOM control 1
  LCD_WriteData_Byte(0x0E); // -- + VCOMS (voltage control) 5:0 

  //ST7735R Gamma Sequence
  LCD_WriteReg(0xe0);       // GAMCTRP1 Gamma adjustment + polarity
  LCD_WriteData_Byte(0x0f);
  LCD_WriteData_Byte(0x1a);
  LCD_WriteData_Byte(0x0f);
  LCD_WriteData_Byte(0x18);
  LCD_WriteData_Byte(0x2f);
  LCD_WriteData_Byte(0x28);
  LCD_WriteData_Byte(0x20);
  LCD_WriteData_Byte(0x22);
  LCD_WriteData_Byte(0x1f);
  LCD_WriteData_Byte(0x1b);
  LCD_WriteData_Byte(0x23);
  LCD_WriteData_Byte(0x37);
  LCD_WriteData_Byte(0x00);
  LCD_WriteData_Byte(0x07);
  LCD_WriteData_Byte(0x02);
  LCD_WriteData_Byte(0x10);

  LCD_WriteReg(0xe1);       // GAMCTRN1 Gamma adjustment - polarity
  LCD_WriteData_Byte(0x0f);
  LCD_WriteData_Byte(0x1b);
  LCD_WriteData_Byte(0x0f);
  LCD_WriteData_Byte(0x17);
  LCD_WriteData_Byte(0x33);
  LCD_WriteData_Byte(0x2c);
  LCD_WriteData_Byte(0x29);
  LCD_WriteData_Byte(0x2e);
  LCD_WriteData_Byte(0x30);
  LCD_WriteData_Byte(0x30);
  LCD_WriteData_Byte(0x39);
  LCD_WriteData_Byte(0x3f);
  LCD_WriteData_Byte(0x00);
  LCD_WriteData_Byte(0x07);
  LCD_WriteData_Byte(0x03);
  LCD_WriteData_Byte(0x10);

  LCD_WriteReg(0xF0); //Enable test command
  LCD_WriteData_Byte(0x01);

  LCD_WriteReg(0xF6); //Disable ram power save mode
  LCD_WriteData_Byte(0x00);

  LCD_WriteReg(0x3A); //65k mode
  LCD_WriteData_Byte(0x05);

  LCD_WriteReg(0x36);
  LCD_WriteData_Byte(0x60);
  DEV_Delay_ms(200);

  LCD_WriteReg(0X11);
  DEV_Delay_ms(200);
  
  LCD_WriteReg(0X29);
  DEV_Delay_ms(200);
}

/******************************************************************************
  function: Set the cursor position
  parameter :
    Xstart:   Start UWORD x coordinate
    Ystart:   Start UWORD y coordinate
    Xend  :   End UWORD coordinates
    Yend  :   End UWORD coordinatesen
******************************************************************************/
void LCD_SetCursor(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD  Yend)
{
  LCD_WriteReg(0x2a);
  LCD_WriteData_Byte(0X00);
  LCD_WriteData_Byte((Xstart & 0xff) + 1);
  LCD_WriteData_Byte(0X00);
  LCD_WriteData_Byte((( Xend - 1 ) & 0xff) + 1 );

  LCD_WriteReg(0x2b);
  LCD_WriteData_Byte(0X00);
  LCD_WriteData_Byte((Ystart & 0xff) + 2);
  LCD_WriteData_Byte(0X00);
  LCD_WriteData_Byte(( (Yend - 1) & 0xff ) + 2);

  LCD_WriteReg(0x2C);
}

/******************************************************************************
  function: Clear screen function, refresh the screen to a certain color
  parameter :
    Color :   The color you want to clear all the screen
******************************************************************************/
void LCD_Clear(UWORD Color)
{
  UWORD i, j;
  LCD_SetCursor(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);
  for (i = 0; i < LCD_WIDTH; i++) {
    for (j = 0; j < LCD_HEIGHT; j++) {
      LCD_WriteData_Word(Color);
    }
  }
}

/******************************************************************************
  function: Refresh a certain area to the same color
  parameter :
    Xstart:   Start UWORD x coordinate
    Ystart:   Start UWORD y coordinate
    Xend  :   End UWORD coordinates
    Yend  :   End UWORD coordinates
    color :   Set the color
******************************************************************************/
void LCD_ClearWindow(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD color)
{
  UWORD i, j;
  LCD_SetCursor(Xstart, Ystart, Xend - 1, Yend - 1);
  for (i = Ystart; i <= Yend - 1; i++) {
    for (j = Xstart; j <= Xend - 1; j++) {
      LCD_WriteData_Word(color);
    }
  }
}

/******************************************************************************
  function: Set the color of an area
  parameter :
    Xstart:   Start UWORD x coordinate
    Ystart:   Start UWORD y coordinate
    Xend  :   End UWORD coordinates
    Yend  :   End UWORD coordinates
    Color :   Set the color
******************************************************************************/
void LCD_SetWindowColor(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD  Color)
{
  LCD_SetCursor( Xstart, Ystart, Xend, Yend);
  LCD_WriteData_Word(Color);
}

/******************************************************************************
  function: Draw a UWORD
  parameter :
    X     :   Set the X coordinate
    Y     :   Set the Y coordinate
    Color :   Set the color
******************************************************************************/
void LCD_SetUWORD(UWORD x, UWORD y, UWORD Color)
{
  LCD_SetCursor(x, y, x, y);
  LCD_WriteData_Word(Color);
}
