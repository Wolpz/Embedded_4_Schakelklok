/* ========================================
    GFX for schakelklok: 

    TODO:
    - draw chars into buffer
    - lines
    - rectangle
    - circle
   
 
    
* ========================================
*/
#include "Schakelklok_gfx.h"

uint8_t fetchGlyph(FONT8_T* fontData, uint16_t code, GLYPH_T* glyphBuf){
    glyphBuf->width = fontData->glyph_width;
    glyphBuf->height = fontData->glyph_height;
    glyphBuf->size = fontData->glyph_size;
    // TODO THIS SAYS ERR
    uint32_t index = ((code + fontData->glyphcode_start_offset) * glyphBuf->height);
    if(index < (fontData->length - fontData->glyphcode_start_offset)){
        glyphBuf->buffer = &fontData->array[index];
        return ERRCODE_OK;
    }
    else{
        return ERRCODE_FAIL;
    }
}

uint8_t clearBuffer(DISPLAY_BUFFER_T* buffer, UWORD colour){
    for(int i = 0; i < buffer->buffer_length; i++){
        buffer->buffer[i] = colour;
    }
    return ERRCODE_OK;
}

uint8_t drawPixel(DISPLAY_BUFFER_T* buffer, UWORD X, UWORD Y, UWORD colour){
    if(X >= buffer->width || Y >= buffer->height || X < 0 || Y < 0){
        return ERRCODE_FAIL;
    }
    else{
      buffer->buffer[buffer->width * Y + X] = colour;
      return ERRCODE_OK;
    }
}

uint8_t drawGlyph(DISPLAY_BUFFER_T* buffer, UWORD Xstart, UWORD Ystart, uint16_t code, FONT8_T* font, UWORD colour){
    GLYPH_T glyph;
    if(fetchGlyph(font, code, &glyph) == ERRCODE_FAIL)
        return ERRCODE_FAIL;
    
    for(uint8_t layer = 0; layer < glyph.height; layer++){
		uint8_t buf = glyph.buffer[layer];
		for(uint8_t bit = 0; bit < glyph.width; bit++){
			if(buf & (128>>bit)){
                drawPixel(buffer, Xstart+bit, Ystart+layer, colour);
            }
		}
    }
    return ERRCODE_OK;
}

uint8_t drawString(DISPLAY_BUFFER_T* buffer, UWORD Xstart, UWORD Ystart, char* str, uint8_t strlen, FONT8_T* font, UWORD colour){
    uint8_t pitch = font->glyph_width + 1;
    
    for(int i = 0; i < strlen; i++){
        char curchar = str[i];
        drawGlyph(buffer, Xstart+pitch*i, Ystart, curchar, font, colour);
    }
}

uint8_t drawLine(DISPLAY_BUFFER_T* buffer, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, uint8_t thickness, UWORD colour){
    if(Xstart > Xend){
        UWORD temp = Xend;
        Xend = Xstart;
        Xstart = temp;
    }
    if(Ystart > Yend){
        UWORD temp = Yend;
        Yend = Ystart;
        Ystart = temp;
    }
    
    if(Xend >= buffer->width || Yend >= buffer->height)
        return ERRCODE_FAIL;
    
    if(Xstart == Xend){     // Vertical line
        int x  = Xstart;
        for(int y = Ystart; y <= Yend; y++){
            for(int i = 0; i < thickness; i++){
                if(i == 0){
                    drawPixel(buffer, x, y, colour);
                }
                else{
                    drawPixel(buffer, x-i, y, colour);
                    drawPixel(buffer, x+i, y, colour);
                }
            }
        }        
        return ERRCODE_OK;
    }
    else if(Ystart == Yend){// Horizontal line
        int y = Ystart;
        for(int x = Xstart; x < Xend; x++){
            for(int i = 0; i < thickness; i++){
                if(i == 0){
                    drawPixel(buffer, x, y, colour);
                }
                else{
                    drawPixel(buffer, x, y-i, colour);
                    drawPixel(buffer, x, y+i, colour);
                }
            }
        }        
        return ERRCODE_OK;
    }
    else{ // Diagonal lines, not bothering with these
        return ERRCODE_FAIL;
    }
    
}

uint8_t drawRectangle(DISPLAY_BUFFER_T* buffer, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, uint8_t thickness, UWORD colour, uint8_t doFill, UWORD fillColour){
    if(Xend >= buffer->width || Yend >= buffer->height)
        return ERRCODE_FAIL;
    
    for(int y = Ystart; y < Yend; y++){     
        for(int x = Xstart; x < Xend; x++){
            drawPixel(buffer, x, y, fillColour);
        }
    }
    if(doFill){
        // Top hor
        drawLine(buffer, Xstart, Ystart+(thickness-1), Xend, Ystart+(thickness-1), thickness, colour);
        // Bot hor
        drawLine(buffer, Xstart, Yend-(thickness), Xend, Yend-(thickness), thickness, colour);
        // Left vert
        drawLine(buffer, Xstart+(thickness-1), Ystart, Xstart+(thickness-1), Yend, thickness, colour);
        // Right vert
        drawLine(buffer, Xend-(thickness), Ystart, Xend-(thickness), Yend, thickness, colour);  
    }
    return ERRCODE_OK;
}

uint8_t drawCircle(DISPLAY_BUFFER_T* buffer, UWORD originX, UWORD originY, uint8_t radius, UWORD colour, uint8_t doFill){
    int x, y, d;

    x = 0;
    y = d = -radius;
    
    while( x < -y){
        if(d>0){
            if(doFill){
                if(y != -radius){
                    drawLine(buffer, originX-x, originY+y, originX+x, originY+y, 1, colour);
                    drawLine(buffer, originX-x, originY-y, originX+x, originY-y, 1, colour);
                }
            }
            y += 1;
            d += ((x+y)<<1) + 1;
        }
        else{
            d += (x<<1) + 1;     
        }
        
        if(doFill){
            drawLine(buffer, originX-y, originY+x, originX+y, originY+x, 1, colour);
            drawLine(buffer, originX-y, originY-x, originX+y, originY-x, 1, colour);
        }
        else{
            drawPixel(buffer, originX+x, originY+y, colour);
            drawPixel(buffer, originX-x, originY+y, colour);
            drawPixel(buffer, originX+x, originY-y, colour);
            drawPixel(buffer, originX-x, originY-y, colour);
            drawPixel(buffer, originX+y, originY+x, colour);
            drawPixel(buffer, originX-y, originY+x, colour);
            drawPixel(buffer, originX+y, originY-x, colour);
            drawPixel(buffer, originX-y, originY-x, colour);             
        }
        x += 1;
    }
    
    if(doFill){
        drawLine(buffer, originX-x, originY+y, originX+x, originY+y, 1, colour);
        drawLine(buffer, originX-x, originY-y, originX+x, originY-y, 1, colour);
        drawLine(buffer, originX-y, originY+x, originX+y, originY+x, 1, colour);
        drawLine(buffer, originX-y, originY-x, originX+y, originY-x, 1, colour);
    }

    return ERRCODE_OK;
}

/* [] END OF FILE */
