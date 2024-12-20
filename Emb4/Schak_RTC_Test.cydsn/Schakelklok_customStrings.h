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
#ifndef SCHAKELKLOK_QUEUE_H
    #define SCHAKELKLOK_QUEUE_H
    #include "project.h"
    #include "..\Schakelklok.cydsn\Schakelklok_types.h"
    #include "Schakelklok_queue.h"
    #include <stdlib.h>
    #include <string.h>
    
    typedef struct {
    	const char* contents;
    	uint8_t length;
    }C_STRING_T;

    C_STRING_T* newString(const char* str, uint8_t length);
    FUNC_ERRCODE_T dropString(C_STRING_T* );

#endif
/* [] END OF FILE */
