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
#include "Schakelklok_customStrings.h"

    #define ERRCODE_OK (0)
    #define ERRCODE_FAIL (1)
    #define ERRCODE_RETRY (2)

C_STRING_T* newString(const char* str, uint8_t length)
{
	C_STRING_T* struct_ptr = (C_STRING_T*)malloc(sizeof(C_STRING_T));
	const char* str_ptr = (const char*)malloc(sizeof(char) * (length+1));
	memcpy((void*)str_ptr, str, length+1);
	struct_ptr->length = length;
	struct_ptr->contents = str_ptr;
	return struct_ptr;
}

FUNC_ERRCODE_T dropString(C_STRING_T* str_struct_ptr)
{
	if (str_struct_ptr->contents == NULL)
		return ERRCODE_FAIL;
	free((void*)str_struct_ptr->contents);
	if (str_struct_ptr == NULL)
		return ERRCODE_FAIL;
	free(str_struct_ptr);
	return ERRCODE_OK;
}

/* [] END OF FILE */
