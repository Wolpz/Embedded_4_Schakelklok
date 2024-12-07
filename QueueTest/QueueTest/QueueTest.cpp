#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define QUEUE_MAXLENGTH (10)
#define ERRCODE_OK (0)
#define ERRCODE_ERR (1)

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

typedef uint8_t FUNC_ERRCODE_T;

typedef FUNC_ERRCODE_T(*FUNC_PTR_T)(uint8_t argc, void** argv);

typedef struct {
	FUNC_PTR_T handlerFuncPtr;
	FUNC_PTR_T closerFuncPtr;
	uint8_t retries;
	uint8_t argc;
	void** argv;
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

// TODO Define argument structs with function definitions they're for

typedef struct {
	int* i;
}PRINTINT_ARGS_T;
FUNC_ERRCODE_T printInt(PRINTINT_ARGS_T args);
typedef struct {
	float* f;
}PRINTFLOAT_ARGS_T;
FUNC_ERRCODE_T printFloat(PRINTFLOAT_ARGS_T args);
typedef struct {
	int* i;
	float* f;
}PRINTFLOATANDINT_ARGS_T;
FUNC_ERRCODE_T printFloatAndInt(PRINTFLOATANDINT_ARGS_T args);
typedef struct {
	char* str;
}PRINTSTRING_ARGS_T;
FUNC_ERRCODE_T printString(PRINTSTRING_ARGS_T args);

FUNC_ERRCODE_T printInt(uint8_t argc, void** argv);
FUNC_ERRCODE_T printFloat(uint8_t argc, void** argv);
FUNC_ERRCODE_T printFloatAndInt(uint8_t argc, void** argv);
FUNC_ERRCODE_T printChar(uint8_t argc, void** argv);
FUNC_ERRCODE_T printString(uint8_t argc, void** argv);


void main(void) {
	Q_TASK_T queueArray[QUEUE_MAXLENGTH];
	FUNC_QUEUE_T taskQueue;
	taskQueue.array = queueArray;
	taskQueue.arrayLength = QUEUE_MAXLENGTH;
	taskQueue.headIndex = taskQueue.tailIndex = taskQueue.currLength = 0;
	Q_TASK_T task;
	int a = 5;
	int b = 90;
	float f = 0.123456f;
	char c = '?';
	const char* str = "Hello";
	void* f_vdptr = (void*)&f;

	//printf("%i and %i\r\n", sizeof(float*), sizeof(int*));


	task.handlerFuncPtr = (FUNC_PTR_T)printInt;
	task.retries = 0;
	task.argc = 1;
	task.argv = (void*)&a;
	queue_addTask(&taskQueue, task);

	task.handlerFuncPtr = (FUNC_PTR_T)printInt;
	task.retries = 0;
	task.argc = 1;
	task.argv = (void*)&b;
	queue_addTask(&taskQueue, task);

	task.handlerFuncPtr = (FUNC_PTR_T)printFloat;
	task.retries = 0;
	task.argc = 1;
	task.argv = (void*)&f;
	queue_addTask(&taskQueue, task);

	task.handlerFuncPtr = (FUNC_PTR_T)printChar;
	task.retries = 0;
	task.argc = 1;
	task.argv = (void*)&c;
	queue_addTask(&taskQueue, task);

	// TODO now get passing multiple variables in array to work without crashing
	task.handlerFuncPtr = (FUNC_PTR_T)printFloatAndInt;
	task.retries = 0;
	task.argc = 2;
	void* arr[2];
	arr[0] = (void*)&f;
	arr[1] = (void*)&a;
	task.argv = arr;
	queue_addTask(&taskQueue, task);


	task.handlerFuncPtr = (FUNC_PTR_T)printString;
	task.retries = 0;
	task.argc = 2;
	int len = 5;
	void* arr2[2] = { (void*)&len, (void*)&str };
	task.argv = arr2;
	queue_addTask(&taskQueue, task);
	printf("Goal addr:\r\nArg1: %u\r\nArg1 arr: %u \r\nArg1 val: %u\r\nArg2: %u\r\nArg1 arr: %u \r\nArg2 val: %u\r\n\n", &len, arr2[0], *(int*)arr2[0], &str, arr2[1], *(char*)arr2[1]);
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
		return ERRCODE_ERR;
	}

	if (q_ptr->tailIndex == q_ptr->arrayLength - 1) {
		q_ptr->tailIndex = 0;
	}
	else if (q_ptr->currLength != 0) {
		q_ptr->tailIndex++;
	}

	q_ptr->array[q_ptr->tailIndex] = task;
	//printf("Task argc: %i\r\n1st argv: %f\r\n", q_ptr->array[q_ptr->tailIndex].argc, *(float*)q_ptr->array[q_ptr->tailIndex].argv);

	q_ptr->currLength++;

	return ERRCODE_OK;
}

/* 	HandleTask
	handles task by calling function pointer with arguments provided in task struct and removing task from queue.
	if task fails, adds it again to the end of the queue.
*/
FUNC_ERRCODE_T queue_handleTask(FUNC_QUEUE_T* q) {
	Q_TASK_T task = q->array[q->headIndex];
	// TODO pointers? no pointers? keep pointing to same original variable in argv
	// argv is void** so one dereference turns it back into array? So no deref which means ptr
	FUNC_ERRCODE_T result = (task.handlerFuncPtr)(task.argc, (void**)task.argv);
	queue_popHead(q);
	if (result != ERRCODE_OK) {
		task.retries++;
		queue_addTask(q, task);
	}
	else {
		return ERRCODE_OK;
	}
}

FUNC_ERRCODE_T printInt(uint8_t argc, void** argv) {
	if (argc != 1) {
		printf("Wrong argc: %i\r\n", argc);
		return ERRCODE_ERR;
	}

	int a = *(int*)*argv;
	printf("INT: %i\r\n", a);

	return ERRCODE_OK;
}

// TODO this outputs 0.0000 no matter what
FUNC_ERRCODE_T printFloat(uint8_t argc, void** argv) {
	if (argc != 1) {
		printf("Wrong argc: %i\r\n", argc);
		return ERRCODE_ERR;
	}

	float a = *(float*)*argv;
	printf("FLOAT: %f\r\n", a);

	return ERRCODE_OK;
}

FUNC_ERRCODE_T printFloatAndInt(uint8_t argc, void** argv) {
	if (argc != 2) {
		printf("Wrong argc: %i\r\n", argc);
		return ERRCODE_ERR;
	}

	float f = *(float*)argv;
	int a = *(int*)((argv)+(sizeof(void*)));
	printf("FLOAT AND INT: %f and %i\r\n", f, a);

	return ERRCODE_OK;
}

FUNC_ERRCODE_T printChar(uint8_t argc, void** argv) {
	if (argc != 1) {
		printf("Wrong argc: %i\r\n", argc);
		return ERRCODE_ERR;
	}

	char c = *(char*)argv;
	printf("CHAR: %c\r\n", c);

	return ERRCODE_OK;
}

FUNC_ERRCODE_T printString(uint8_t argc, void** argv) {
	if (argc != 2) {
		printf("Wrong argc\r\n");
		return ERRCODE_ERR;
	}
	int length = argc;

	printf("STRING L=%i: ", length);
	//char* str = (char*)(argv[0]+sizeof(void*));

	//printf("%u\r\n", x);
	int ptr = 0;//argv[1];

	printf("Passed addr:\r\nArg1: %u\r\nArg1 val: %u\r\nArg2: %u\r\nArg2 val: %u\r\n", argv[0], (int*)argv[0], ptr, ptr);
	/*
	int i;
	for(i = 0; i < length; i++){
		char c = *(str+i);
		printf("%i ", c);
	}*/
	printf("\r\n");

	return ERRCODE_OK;
}
