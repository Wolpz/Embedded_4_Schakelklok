/* ========================================
    GFX for schakelklok: 

    TODO:
    - font struct
    - buffer
    - draw chars into buffer
    - lines
    - rectangle
    - cicle
   
 
    
* ========================================
*/
#include "project.h"
#include "..\Schakelklok.cydsn\Schakelklok_types.h"
#include "Schakelklok_gfx.h"
#include "gfx_fonts.h"

#define FONT_NAME_OFFSET 6
#define FONT_WIDTH_OFFSET 14
#define FONT_HEIGHT_OFFSET 15
#define FONT_TYPE_OFFSET 16

/*
Drawing glyph into buffer:
GLYPH_T glyph;
	FONT_T fontData;
	// TODO put all this data in font struct
	fontData.array = font_5x7;
    fontData.glyph_height = 7;
    fontData.glyph_width = 5;
    fontData.glyph_size = fontData.glyph_width * fontData.glyph_height;
    fontData.glyphs_offset = -32;
    printf("FONT\r\nW: %d H: %d \r\nO: %d\r\n\n", fontData.glyph_width, fontData.glyph_height, fontData.glyphs_offset);
    
    char* str = "Hello there!";
	printf("String: %s\r\n", str);
	
	int i, j, k;
	for(i = 0; str[i] != '\0'; i++){
		// Get glyph start
		fetchGlyph(&fontData, str[i], &glyph);
		for(j = 0; j < glyph.height; j++){
			// Get current layer of glyph
			uint8_t buf = glyph.index[j];
			for(k = 0; k < glyph.width; k++){
				char c = ((buf & (128>>k)) ? '#' : ' ');
				printf("%c", c);
			}
			printf("\r\n");
		}
	}
*/

void fetchGlyph(FONT_T* fontData, uint16_t code, GLYPH_T* glyphBuf){
    glyphBuf->width = fontData->glyph_width;
    glyphBuf->height = fontData->glyph_height;
    glyphBuf->size = fontData->glyph_size;
    
    int index = ((code + fontData->glyphs_offset) * glyphBuf->height);
   	glyphBuf->index = &fontData->array[index];
}

/* [] END OF FILE */
