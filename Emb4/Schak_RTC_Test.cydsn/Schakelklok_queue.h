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
    #define QUEUE_MAXLENGTH (10)
    #define ERRCODE_OK (0)
    #define ERRCODE_ERR (1)

    typedef uint8_t FUNC_ERRCODE_T;
    
    typedef struct {
        FUNC_ERRCODE_T (*handlerFunc)();
        uint8_t retries;
        void* args[];
        /*  [0] is number of arguments, rest is arguments. Cast to make them usable. */
    } Q_HANDLER_T;
    
    typedef struct {
        uint8_t length;
    } Q_DATA_T;

    typedef struct Q_NODE_TD {
        Q_HANDLER_T* handler;
        Q_DATA_T* data;
        struct Q_NODE_TD* next;
        struct Q_NODE_TD* last;
    } Q_NODE_T;
    
    //static FUNC_ERRCODE_T queue_insertRear(Q_NODE_T* queueHead, Q_HANDLER_T* handler);
    FUNC_ERRCODE_T queue_popFront(Q_NODE_T* queueHead);
    
    FUNC_ERRCODE_T queue_add(Q_NODE_T* queueHead, Q_NODE_T* newNode);
    FUNC_ERRCODE_T queue_handle(Q_NODE_T* queueHead);

#endif

/* [] END OF FILE */
