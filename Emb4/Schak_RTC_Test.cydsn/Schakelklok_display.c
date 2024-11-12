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
#include "Schakelklok_display.h"

void LCD_Reset(void){
    Display_RST_Write(0);
    //CyPins_ClearPin(o_Display_RST);
    CyDelay(120);
    Display_RST_Write(1);
    //CyPins_SetPin(o_Display_RST);
    CyDelay(20);
}

void LCD_Init(void){
    // TODO
    LCD_Reset();
    
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


// TODO WTF are these commands??

  LCD_WriteReg(0xF0); //Enable test command ???
  LCD_WriteData_Byte(0x01);

  LCD_WriteReg(0xF6); //Disable onboard ram power save mode
  LCD_WriteData_Byte(0x00);

  LCD_WriteReg(0x3A); // Pixel colour mode 
  LCD_WriteData_Byte(0x05); //65k mode (RGB 565)

  LCD_WriteReg(0x36); // Memory data access control
  LCD_WriteData_Byte(0x60); //MY + MX + MV + ML + RGB + MH + 0b10
  CyDelay(200);

  LCD_WriteReg(0X11); // SLPOUT: Sleep out (off?) and booster on
  CyDelay(200);
  
  LCD_WriteReg(0X29); // Command: display on (display off is 28h)
  CyDelay(200);

}
void LCD_Clear(UWORD colour){
    LCD_SetWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, colour);
}
void LCD_SetWindow(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD colour){
    int bufLen = (Xend - Xstart + 1) * (Yend - Ystart + 1);
    UWORD bufArray[bufLen];
    for(int i = 0; i < bufLen; i++){
        bufArray[i] = colour;
    }   
    
    LCD_SetCursor(Xstart, Ystart, Xend, Yend);
    LCD_TransferBuffer(Xstart, Ystart, Xend, Yend, bufArray);
    /*
    for(int i = 0; i < bufLen; i++){
        LCD_WriteData_Word(colour);
    }
    */
}

void LCD_TransferBuffer(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD bufferArray[]){
    int bufLen = (Xend - Xstart + 1) * (Yend - Ystart + 1);
    LCD_SetCursor(Xstart, Ystart, Xend, Yend);
    
    //SPI_Module_STS_BYTE_COMPLETE
    //SPI_Module_STS_TX_FIFO_NOT_FULL
    for(int i = 0; i < bufLen; i++){
        if(SPI_Module_ReadTxStatus() & SPI_Module_STS_TX_FIFO_NOT_FULL){
            LCD_WriteData_Word(bufferArray[i]);
        }
        else{
            uint8_t bytesComplete = 0;
            while(bytesComplete < 2){
                if(SPI_Module_ReadTxStatus() & SPI_Module_STS_BYTE_COMPLETE)
                    bytesComplete++;
            }
        }  
    }
}

void LCD_WriteData_Byte(UBYTE byte){
    while(SPI_Ready() == 0);
    //CyPins_ClearPin(o_Display_CS);
    LCD_DC_Setmode(DC_DATA);
    SPI_Module_WriteTxData(byte);
    //while(SPI_Module_ReadTxStatus() & (SPI_Module_STS_SPI_IDLE));  // Block until transmission starts
    //CyPins_SetPin(o_Display_CS);
}
void LCD_WriteData_Word(UWORD word){
    //while(SPI_Ready() == 0);
    //CyPins_ClearPin(o_Display_CS);
    LCD_DC_Setmode(DC_DATA);
    SPI_Module_WriteTxData((UBYTE) (word>>8 )& 0xff); // Send HB first
    SPI_Module_WriteTxData((UBYTE) (word & 0xff));
    //while(SPI_Module_ReadTxStatus() & (SPI_Module_STS_SPI_IDLE));  // Block until transmission starts
    //CyPins_SetPin(o_Display_CS);
}
void LCD_WriteReg(UBYTE regAddress){
    while(SPI_Ready() == 0);
    //CyPins_ClearPin(o_Display_CS);
    LCD_DC_Setmode(DC_COMMAND);
    SPI_Module_WriteTxData(regAddress);
    //while(SPI_Ready());  // Block until transmission starts. Kinda sucks
    //CyPins_ClearPin(o_Display_CS);
}

// Checks if SPI module is done or idle and Tx register is emptt
int SPI_Ready(){
    int status = SPI_Module_ReadTxStatus();
    int rdy = (status & (SPI_Module_STS_SPI_IDLE | SPI_Module_STS_BYTE_COMPLETE | SPI_Module_STS_SPI_DONE));
    return rdy;
}

// Sets LCD display Data/Command pin to correct mode
void LCD_DC_Setmode(uint8_t mode){
    Display_DC_Write(mode);
}

void LCD_SetCursor(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD  Yend){
    // TODO this windowing seems slightly off??
  LCD_WriteReg(0x2A); // Set RAM X Window
  LCD_WriteData_Byte(0X00);
  LCD_WriteData_Byte((Xstart & 0xff)+1);// + 1);
  LCD_WriteData_Byte(0X00);
  LCD_WriteData_Byte((( Xend - 1 ) & 0xff)+1);// + 1);

  LCD_WriteReg(0x2B); // Set RAM Y window
  LCD_WriteData_Byte(0X00);
  LCD_WriteData_Byte((Ystart & 0xff)+2);// + 2);
  LCD_WriteData_Byte(0X00);
  LCD_WriteData_Byte(( (Yend - 1) & 0xff )+4);// + 2);

  LCD_WriteReg(0x2C); // Begin RAM write
}
void LCD_SetPixel(UWORD x, UWORD y, UWORD Color){
  LCD_SetCursor(x, y, x, y);
  LCD_WriteData_Word(Color);    
}

/* [] END OF FILE */
