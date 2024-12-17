/* ========================================
    Guide to using these queues:

    queue_handleTask handes your tasks. This should be the only thing in your main loop, except perhaps some basic code
    to execute whenever you complete a task.
    
    queue_addTask adds a task to the queue, up to QUEUE_MAXLENGTH, but the variables for this task must first be 
    allocated. If they are
    Allocation can be done in two ways:
    -   pre-allocation: this is done lower on the stack, at the same level as queue_handleTask, ensureing the variables
        are not thrown out when the current function ends. However, this tends to mean you only have one instance of
        the variable-carrying struct. Thus, it must not be modified while the task in in the queue, meaning the task 
        cannot be added to the queue more than once with different values.
    -   dynamically allocated: this is done within the function, using malloc. More on the format for this later.
        This will allow you to create multiple different variable structs for multiple instances of the same task.
        When this is done, a destructor function NEEDS to be called to free() the allocated memory after the task is completed.
        
    Declaring/defining a task function:
    The task queue does not know what parameters your task requires. It only passes a void pointer to a struct that
    carries these arguments. Because of this, tasks must accept a void pointer, which is then cast to an argument
    struct defined along with the function. In tasks that require dynamic memory allocation, a destructor to free()
    the memory allocated for this struct also has to be declared. If this were c++, we'd have objects to fix all this, but we don't.
    Task functions should also return FUNCTION_ERRCODE_T to allow retries.
    Declaration of a task function:
    
    FUNC_ERRCODE_T myFunction(void* argument_struct_pointer);
    FUNC_ERRCODE_T myFunction_destructor(void* argument_struct_pointer); // If argument will be dynamically allocated
    typedef struct {
        ... arguments ...
        } MY_ARGUMENT_STRUCT_T;
        
    
    Scheduling a follow-up task:
    Since queue argument blindness works both ways and leaving the task will mean that stack layer is destroyed,
    we must dynamically allocate arguments we wish to pass to the queue. The function must also know which queue
    to add the new task to, so a pointer to the queue has to be in the task's argument struct.
    
 * ========================================
*/




#ifndef SCHAKELKLOK_QUEUE_H
    #define SCHAKELKLOK_QUEUE_H
    #include "project.h"
    #include "..\Schakelklok.cydsn\Schakelklok_types.h"
    
    #define QUEUE_MAXLENGTH (20)
    #define QUEUE_MAXRETRIES (10)
    #define ERRCODE_OK (0)
    #define ERRCODE_FAIL (1)
    #define ERRCODE_RETRY (2)
    #define ERRCODE_QUEUE_EMPTY (3)

    typedef unsigned char uint8_t;
    typedef unsigned short uint16_t;

    typedef uint8_t FUNCTION_ERRCODE_T;

    typedef FUNCTION_ERRCODE_T(*FUNC_PTR_T)(void* argStruct_ptr);

    typedef struct {
    	const char* contents;
    	uint8_t length;
    }C_STRING_T;

    typedef struct {
    	FUNC_PTR_T handlerPtr;
    	FUNC_PTR_T destructorPtr;
    	uint8_t retries;
    	void* argStruct_ptr;
    } Q_TASK_T;

    typedef struct {
    	Q_TASK_T* array;
    	uint16_t arrayLength;
    	uint16_t currLength;
    	uint16_t headIndex;
    	uint16_t tailIndex;
    } FUNC_QUEUE_T;
    
    typedef struct {
        char** names;
        FUNC_PTR_T* ptrs;
        uint8_t amount;
    } QUEUE_FUNCS_DATA_T;
    
    typedef struct {
        QUEUE_FUNCS_DATA_T* funcData;
        uint8_t funcId;
    } QUEUE_LOG_DATA_T;

    FUNCTION_ERRCODE_T queue_popHead(FUNC_QUEUE_T* q);
    FUNCTION_ERRCODE_T queue_addTask(FUNC_QUEUE_T* q, Q_TASK_T task);
    FUNCTION_ERRCODE_T queue_handleTask(FUNC_QUEUE_T* q, QUEUE_FUNCS_DATA_T* funcData, FUNC_PTR_T loggingFunc);
    FUNCTION_ERRCODE_T createTask(Q_TASK_T* taskBuf, FUNC_PTR_T handlerPtr, FUNC_PTR_T destructorPtr, void* argStruct_ptr);
    C_STRING_T* newString(const char* str, uint8_t length);
    FUNCTION_ERRCODE_T dropString(C_STRING_T* );
    
    uint8_t getHandlerFuncName(FUNC_PTR_T handlerAddr, QUEUE_FUNCS_DATA_T* funcData);


#endif

/* [] END OF FILE */
