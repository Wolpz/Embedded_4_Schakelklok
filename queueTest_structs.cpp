#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO:
// Create RTOS schema
// Put this into practice! It's time to write some wrappersss

#define QUEUE_MAXLENGTH (10)
#define ERRCODE_OK (0)
#define ERRCODE_FAIL (1)
#define ERRCODE_RETRY (2)

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

typedef uint8_t FUNC_ERRCODE_T;

typedef FUNC_ERRCODE_T(*FUNC_PTR_T)(void* argStruct_ptr);

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

FUNC_ERRCODE_T queue_popHead(FUNC_QUEUE_T* q);
FUNC_ERRCODE_T queue_addTask(FUNC_QUEUE_T* q, Q_TASK_T task);
FUNC_ERRCODE_T queue_handleTask(FUNC_QUEUE_T* q);
FUNC_ERRCODE_T createTask(Q_TASK_T* taskBuf, FUNC_PTR_T handlerPtr, FUNC_PTR_T destructorPtr, void* argStruct_ptr);
C_STRING_T* newString(const char* str, uint8_t length);
FUNC_ERRCODE_T dropString(C_STRING_T* );

typedef struct {
	int i;
}PRINTINT_ARGS_T;
FUNC_ERRCODE_T printInt(PRINTINT_ARGS_T* args);
FUNC_ERRCODE_T printInt_destructor(PRINTINT_ARGS_T* args_ptr) {
	//printf("address to be freed: %u\r\n", args_ptr);
	free(args_ptr);
	//printf("boom\r\n");
	return ERRCODE_OK;
}

typedef struct {
	float f;
}PRINTFLOAT_ARGS_T;
FUNC_ERRCODE_T printFloat(PRINTFLOAT_ARGS_T* args);

typedef struct {
	int i;
	float f;
}PRINTFLOATANDINT_ARGS_T;
FUNC_ERRCODE_T printFloatAndInt(PRINTFLOATANDINT_ARGS_T* args);

typedef struct {
	C_STRING_T* str;
}PRINTSTRING_ARGS_T;
FUNC_ERRCODE_T printString(PRINTSTRING_ARGS_T* args);
FUNC_ERRCODE_T printString_destructor(PRINTSTRING_ARGS_T* args_ptr) {
	dropString(args_ptr->str);
	free(args_ptr);
	return ERRCODE_OK;
}

typedef struct {
	char* c_ptr;
}PRINTCHARPTR_ARGS_T;
FUNC_ERRCODE_T printCharPtr(PRINTCHARPTR_ARGS_T* args);

FUNC_QUEUE_T taskQueue;

void main(void) {
	Q_TASK_T queueArray[QUEUE_MAXLENGTH];
	taskQueue.array = queueArray;
	taskQueue.arrayLength = QUEUE_MAXLENGTH;
	taskQueue.headIndex = taskQueue.tailIndex = taskQueue.currLength = 0;
	Q_TASK_T task;
	int a = 5;
	int b = 90;
	float f = 0.123456f;
	char c = '?';
	const char* temp = "Hello";
	C_STRING_T str = { temp, strlen(temp)};

	PRINTINT_ARGS_T* addr = (PRINTINT_ARGS_T*)malloc(sizeof(PRINTINT_ARGS_T));
	//printf("address allocated: %u\r\n", addr);
	printInt_destructor(addr);

	task.handlerPtr = (FUNC_PTR_T)printInt;
	task.destructorPtr = NULL;
	task.retries = 0;
	PRINTINT_ARGS_T p;
	p.i = a;
	task.argStruct_ptr = (void*)&p;
	queue_addTask(&taskQueue, task);

	task.handlerPtr = (FUNC_PTR_T)printInt;
	task.destructorPtr = NULL;
	p.i = b;
	task.argStruct_ptr = (void*)&p;
	queue_addTask(&taskQueue, task);

	task.handlerPtr = (FUNC_PTR_T)printFloat;
	task.destructorPtr = NULL;
	task.retries = 0;
	PRINTFLOAT_ARGS_T q;
	q.f = f;
	task.argStruct_ptr = (void*)&q;
	queue_addTask(&taskQueue, task);

	task.handlerPtr = (FUNC_PTR_T)printCharPtr;
	task.retries = 0;
	PRINTCHARPTR_ARGS_T s;
	s.c_ptr = &c;
	task.argStruct_ptr = (void*)&s;
	queue_addTask(&taskQueue, task);

	task.handlerPtr = (FUNC_PTR_T)printFloatAndInt;
	task.retries = 0;
	PRINTFLOATANDINT_ARGS_T r;
	r.i = a;
	r.f = f;
	task.argStruct_ptr = (void*)&r;
	queue_addTask(&taskQueue, task);

	task.handlerPtr = (FUNC_PTR_T)printString;
	task.destructorPtr = NULL;
	task.retries = 0;
	PRINTSTRING_ARGS_T t;
	t.str = &str;
	task.argStruct_ptr = (void*)&t;
	queue_addTask(&taskQueue, task);
	//printf("Goal addr:\r\nArg1: %u\r\nArg1 arr: %u \r\nArg1 val: %u\r\nArg2: %u\r\nArg1 arr: %u \r\nArg2 val: %u\r\n\n", &len, arr2[0], *(int*)arr2[0], &str, arr2[1], *(char*)arr2[1]);
	
	while (taskQueue.currLength != 0) {
		queue_handleTask(&taskQueue);
	}
}

/* 	popHead
	'removes' entry from queue by incrementing head index
*/
FUNC_ERRCODE_T queue_popHead(FUNC_QUEUE_T* q) {
	if (q->headIndex != q->tailIndex)
		q->headIndex++;
	if (q->currLength > 0)
		q->currLength--;

	return ERRCODE_OK;
}

/*	addTask
	adds new task data and pointers to next element in queue and updates tail index to match
*/
FUNC_ERRCODE_T queue_addTask(FUNC_QUEUE_T* q_ptr, Q_TASK_T task) {
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
FUNC_ERRCODE_T queue_handleTask(FUNC_QUEUE_T* q) {
	Q_TASK_T task = q->array[q->headIndex];

	FUNC_ERRCODE_T result = (task.handlerPtr)(task.argStruct_ptr);
	queue_popHead(q);
	if (result != ERRCODE_OK) {
		task.retries++;
		queue_addTask(q, task);
	}
	else {
		if (task.destructorPtr != NULL) {
			task.destructorPtr(task.argStruct_ptr);
		}
		return ERRCODE_OK;
	}
}

FUNC_ERRCODE_T createTask(Q_TASK_T* taskBuf, FUNC_PTR_T handlerPtr, FUNC_PTR_T destructorPtr, void* argStruct_ptr)
{
	taskBuf->handlerPtr = handlerPtr;
	taskBuf->destructorPtr = destructorPtr;
	//printf("Task arg addr: %u\r\n", argStruct_ptr);
	taskBuf->argStruct_ptr = argStruct_ptr;
	taskBuf->retries = 0;
	return ERRCODE_OK;
}

C_STRING_T* newString(const char* str, uint8_t length)
{
	//printf("NEWSTRING: \r\n");
	C_STRING_T* struct_ptr = (C_STRING_T*)malloc(sizeof(C_STRING_T));
	//printf("struct ptr: %u\r\n", struct_ptr);
	const char* str_ptr = (const char*)malloc(sizeof(char) * (length+1));
	//printf("string ptr: %u\r\n", str_ptr);
	memcpy((void*)str_ptr, str, length+1);
	struct_ptr->length = length;
	struct_ptr->contents = str_ptr;
	//printf("Str contents: ");
	//printf(str);
	//printf("\r\nStruct contents: ");
	//printf(struct_ptr->contents);
	//printf("\r\n");
	return struct_ptr;
}

FUNC_ERRCODE_T dropString(C_STRING_T* str_struct_ptr)
{
	if (str_struct_ptr->contents == NULL)
		return ERRCODE_FAIL;
	//printf("DROPSTRING: \r\n");
	//printf("contents addr: %u\r\n", str_struct_ptr->contents);
	free((void*)str_struct_ptr->contents);
	if (str_struct_ptr == NULL)
		return ERRCODE_FAIL;
	//printf("struct addr: %u", str_struct_ptr);
	free(str_struct_ptr);
	return ERRCODE_OK;
}

FUNC_ERRCODE_T printInt(PRINTINT_ARGS_T* args)
{
	int a = args->i;
	printf("INT: %i\r\n", a);

	return ERRCODE_OK;
}

FUNC_ERRCODE_T printFloat(PRINTFLOAT_ARGS_T* args)
{
	float a = args->f;
	printf("FLOAT: %f\r\n", a);

	// TODO try this with longer thing like string and printfloatandint
	Q_TASK_T task;
	PRINTINT_ARGS_T* arg = (PRINTINT_ARGS_T*)malloc(sizeof(PRINTINT_ARGS_T));
	arg->i = 42;
	createTask(&task, (FUNC_PTR_T)printInt, (FUNC_PTR_T)printInt_destructor, arg);
	queue_addTask(&taskQueue, task);

	return ERRCODE_OK;
}

FUNC_ERRCODE_T printFloatAndInt(PRINTFLOATANDINT_ARGS_T* args)
{
	float f = args->f;
	int a = args->i;
	printf("FLOAT AND INT: %f and %i\r\n", f, a);

	return ERRCODE_OK;
}

FUNC_ERRCODE_T printString(PRINTSTRING_ARGS_T* args)
{
	int length = args->str->length;

	printf("STRING L=%i: ", length);
	int i;
	for(i = 0; i < length; i++){
		char c = *(args->str->contents + i);
		if (c > 32 and c < 127)
			printf("%c", c);
		else
			return ERRCODE_FAIL;
	}
	printf("\r\n");

	return ERRCODE_OK;
}

FUNC_ERRCODE_T printCharPtr(PRINTCHARPTR_ARGS_T* args)
{
	char c = *args->c_ptr;
	printf("CHAR: %c\r\n", c);

	Q_TASK_T task;
	PRINTSTRING_ARGS_T* arg = (PRINTSTRING_ARGS_T*)malloc(sizeof(PRINTSTRING_ARGS_T));
	const char* s = "Goodbye";
	arg->str = newString(s, strlen(s));
	createTask(&task, (FUNC_PTR_T)printString, (FUNC_PTR_T)printString_destructor, arg);
	queue_addTask(&taskQueue, task);

	return ERRCODE_OK;
}