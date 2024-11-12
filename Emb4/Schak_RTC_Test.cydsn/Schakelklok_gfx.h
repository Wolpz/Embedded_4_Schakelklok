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
//#include "project.h"

#ifndef SCHAKELKLOK_GFX_H
    #define SCHAKELKLOK_GFX_H

    #define FONT_NAME_OFFSET 6
    #define FONT_WIDTH_OFFSET 14
    #define FONT_HEIGHT_OFFSET 15
    #define FONT_TYPE_OFFSET 16
    
    #define ERRCODE_OK      0
    #define ERRCODE_ERR     1
    #include "..\Schakelklok.cydsn\Schakelklok_types.h"
    #include "string.h"
    
    typedef struct {
        uint8_t* array;
        uint32_t length;
        uint16_t glyphs_total;
        int16_t glyphcode_start_offset;
        uint8_t glyph_width;
        uint8_t glyph_height;
        uint16_t glyph_size;
        char* name;
    } FONT8_T;

    typedef struct {
        const uint8_t* buffer;
        uint8_t width;
        uint8_t height;
        uint8_t size;
    } GLYPH_T;

    typedef struct {
        UWORD* buffer;
        uint16_t buffer_length;
        uint16_t width;
        uint16_t height;
        uint16_t index;
    } DISPLAY_BUFFER_T;

    uint8_t fetchGlyph(FONT8_T* fontData, uint16_t code, GLYPH_T* glyphBuf );
    
    uint8_t clearBuffer(DISPLAY_BUFFER_T* buffer, UWORD colour);
    
    uint8_t drawPixel(DISPLAY_BUFFER_T* buffer, UWORD X, UWORD Y, UWORD colour);
    uint8_t drawGlyph(DISPLAY_BUFFER_T* buffer, UWORD Xstart, UWORD Ystart, uint16_t code, FONT8_T* font, UWORD colour);  
    uint8_t drawString(DISPLAY_BUFFER_T* buffer, UWORD Xstart, UWORD Ystart, char* str, uint8_t strlen, FONT8_T* font, UWORD colour);
    uint8_t drawLine(DISPLAY_BUFFER_T* buffer, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, uint8_t thickness, UWORD colour);
    uint8_t drawRectangle(DISPLAY_BUFFER_T* buffer, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, uint8_t thickness, UWORD colour, uint8_t doFill, UWORD fillColour);
    uint8_t drawCircle(DISPLAY_BUFFER_T* buffer, UWORD Xstart, UWORD Ystart, uint8_t radius, UWORD colour, uint8_t doFill);
    
#endif

/* [] END OF FILE */
