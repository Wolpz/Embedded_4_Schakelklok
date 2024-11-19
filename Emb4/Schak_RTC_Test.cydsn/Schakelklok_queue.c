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
#include "Schakelklok_queue.h"

//static FUNC_ERRCODE_T queue_insertRear(Q_NODE_T* queueHead, Q_HANDLER_T* handler);

FUNC_ERRCODE_T queue_popFront(Q_NODE_T* queueHead){
    Q_NODE_T* newHead = queueHead->next;
    newHead->last = queueHead->last;
    newHead->data->length = queueHead->data->length - 1;
    queueHead = newHead;
    
    return ERRCODE_OK;
}
    
FUNC_ERRCODE_T queue_add(Q_NODE_T* queueHead, Q_NODE_T* newNode){
    if(queueHead->data->length == QUEUE_MAXLENGTH){
        return ERRCODE_ERR;
    }
    else{
        Q_NODE_T* q_rear = queueHead->last;
        q_rear->next = newNode;
        queueHead->last = newNode;
        queueHead->data->length++;
        return ERRCODE_OK;
    }
}
FUNC_ERRCODE_T queue_handle(Q_NODE_T* queueHead){
    Q_HANDLER_T *handler = queueHead->handler;
    uint8_t argNum = *(int*)handler->args[0];
    
    (queueHead->handler->handlerFunc)();
    queue_popFront(queueHead);
    return ERRCODE_OK;
}

/* [] END OF FILE */
