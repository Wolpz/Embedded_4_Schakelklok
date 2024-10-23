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

typedef struct {
    uint8_t* array;
    uint32_t length;
    uint16_t glyph_num;
    uint8_t glyphs_start_offset;
    uint8_t glyph_width;
    uint8_t glyph_height;
    uint16_t glyph_size;
} FONT8_T;

typedef struct {
    const uint8_t* buffer;
    uint8_t width;
    uint8_t height;
    uint8_t size;
} GLYPH_T;

/* [] END OF FILE */
