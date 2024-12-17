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

/* 	popHead
	'removes' entry from queue by incrementing head index
*/
FUNCTION_ERRCODE_T queue_popHead(FUNC_QUEUE_T* q) {
	if (q->headIndex != q->tailIndex){        
        if(q->headIndex < (QUEUE_MAXLENGTH-1)){
            q->headIndex++;
        }
        else{
            q->headIndex = 0;
        } 
    }
	if(q->currLength > 0){
        q->currLength--;
    }
		
	return ERRCODE_OK;
}

/*	addTask
	adds new task data and pointers to next element in queue and updates tail index to match
*/
FUNCTION_ERRCODE_T queue_addTask(FUNC_QUEUE_T* q_ptr, Q_TASK_T task) {
	if (q_ptr->currLength == q_ptr->arrayLength) {// Queue full
		return ERRCODE_FAIL;
	}

	if (q_ptr->tailIndex == q_ptr->arrayLength - 1) {
		q_ptr->tailIndex = 0;
	}
	else if (q_ptr->currLength != 0) {
		q_ptr->tailIndex++;
	}
	q_ptr->array[q_ptr->tailIndex] = task;
	q_ptr->currLength++;

	return ERRCODE_OK;
}

/* 	HandleTask
	handles task by calling function pointer with arguments provided in task struct and removing task from queue.
	if task fails, adds it again to the end of the queue.
*/
FUNCTION_ERRCODE_T queue_handleTask(FUNC_QUEUE_T* q, QUEUE_FUNCS_DATA_T* funcData, FUNC_PTR_T loggingFunc) {
    if(q->currLength == 0){
        return ERRCODE_QUEUE_EMPTY;
    }
    
	Q_TASK_T task = q->array[q->headIndex];

	FUNCTION_ERRCODE_T result = (task.handlerPtr)(task.argStruct_ptr);
    
	if (result == ERRCODE_RETRY && task.retries < QUEUE_MAXRETRIES) {
        task.retries++;
	    queue_addTask(q, task);
        return ERRCODE_RETRY;
	}
    
    if(result == ERRCODE_FAIL){
        QUEUE_LOG_DATA_T log;
        log.funcData = funcData;
        log.funcId = getHandlerFuncName(task.handlerPtr, funcData);
        loggingFunc(&log);
    }
    
	if (task.destructorPtr != NULL) {
		task.destructorPtr(task.argStruct_ptr);
	}
    
    queue_popHead(q);
	return result;
}

FUNCTION_ERRCODE_T createTask(Q_TASK_T* taskBuf, FUNC_PTR_T handlerPtr, FUNC_PTR_T destructorPtr, void* argStruct_ptr)
{
	taskBuf->handlerPtr = handlerPtr;
	taskBuf->destructorPtr = destructorPtr;
	taskBuf->argStruct_ptr = argStruct_ptr;
	taskBuf->retries = 0;
	return ERRCODE_OK;
}

uint8_t getHandlerFuncName(FUNC_PTR_T handlerAddr, QUEUE_FUNCS_DATA_T* funcsData){
    for(uint8_t i = 0; i < funcsData->amount; i++){
        FUNC_PTR_T currPtr = funcsData->ptrs[i];
        if(handlerAddr == currPtr){
            return i+1;
        }
    }
    return 0;
}
    
    
/* [] END OF FILE */
