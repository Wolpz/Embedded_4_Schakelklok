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
#include "project.h"
#include "..\Schakelklok.cydsn\Schakelklok_types.h"
#include "Schakelklok_gfx.h"
#include "gfx_fonts.h"
#include "Schakelklok_display.h"

#define LCD_WIDTH   160 //LCD width
#define LCD_HEIGHT  128 //LCD height


//const UWORD dispBuf_diff_array[LCD_WIDTH * LCD_HEIGHT];

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    const UWORD dispBuf_array[LCD_WIDTH * LCD_HEIGHT];
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    SPI_Module_Start();
    //SPI_Module_TxEnable();
    
    int led = 0;
    for(int i = 0; i < 4; i++){
        led = ~led;
        o_DebugLed_Write(led);  
        CyDelay(100);
    }
    CyDelay(500);
    
    FONT8_T currFont;
    
    FONT8_T font_8x13_struct;
    font_8x13_struct.array = font_8x13;
    font_8x13_struct.name = font_8x13_name;
    font_8x13_struct.length = font_8x13_arraylength;
    font_8x13_struct.glyphs_total = font_8x13_glyphnum;
    font_8x13_struct.glyphcode_start_offset = -font_8x13_startGlyph;
    font_8x13_struct.glyph_width = font_8x13_width;
    font_8x13_struct.glyph_height = font_8x13_height;
    font_8x13_struct.glyph_size = font_8x13_height * font_8x13_width;   
    FONT8_T font_6x9_struct;
    font_6x9_struct.array = font_6x9;
    font_6x9_struct.name = font_6x9_name;
    font_6x9_struct.length = font_6x9_arraylength;
    font_6x9_struct.glyphs_total = font_6x9_glyphnum;
    font_6x9_struct.glyphcode_start_offset = -font_6x9_startGlyph;
    font_6x9_struct.glyph_width = font_6x9_width;
    font_6x9_struct.glyph_height = font_6x9_height;
    font_6x9_struct.glyph_size = font_6x9_height * font_6x9_width;   
    
    currFont = font_8x13_struct;
    
    DISPLAY_BUFFER_T displayBuffer;
    displayBuffer.buffer = dispBuf_array;
    displayBuffer.buffer_length = LCD_WIDTH * LCD_HEIGHT;
    displayBuffer.height = LCD_HEIGHT;
    displayBuffer.width = LCD_WIDTH;
    displayBuffer.index = 0;
   
    LCD_Init();
    
    for(int i = 0; i < 4; i++){
        led = ~led;
        o_DebugLed_Write(led);  
        CyDelay(100);
    }
    
    char* text = "Hello there!";
    uint8_t text_len = strlen(text);
    
    for(;;)
    {/*
        o_DebugLed_Write(led);
        clearBuffer(&displayBuffer, 0x00FF);
        LCD_Clear(0x00FF);
        //LCD_TransferBuffer(0, 0, displayBuffer.width, displayBuffer.height, displayBuffer.buffer);
        CyDelay(1000);*/
       
        o_DebugLed_Write(~led); 
        clearBuffer(&displayBuffer, 0);
        //drawLine(&displayBuffer, 50, 20, 50, 120, 10, 0xF000);
        //drawLine(&displayBuffer, 20, 80, 70, 80, 5, 0x005F);
        //drawRectangle(&displayBuffer, 70, 30, 140, 80, 5, 0x0FF0, 1, 0xFFFF);
        drawCircle(&displayBuffer, LCD_WIDTH/2, LCD_HEIGHT/2, 60, 0x005F, 1);
        drawString(&displayBuffer, LCD_WIDTH/2-(text_len * currFont.glyph_width)/2, LCD_HEIGHT/2-4, text, text_len, &currFont, 0xFFFF);
        LCD_TransferBuffer(0, 0, displayBuffer.width, displayBuffer.height, displayBuffer.buffer);
        CyDelay(1000);
        
    }
}


/* [] END OF FILE */
