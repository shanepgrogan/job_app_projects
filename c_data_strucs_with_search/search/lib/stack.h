// stack.h
#ifndef __STACK_HEADER
#define __STACK_HEADER

typedef struct _Stack{
	// Fields: Any you'd like
	// Functionality: whatever you deem necessary
	LinkedList* arr;
} Stack;

Stack* stack_initialize(int, char*);
bool stack_push(Stack*, void*);
void* stack_pop(Stack*);
void* stack_peek(Stack*);
int stack_size(Stack*);
bool stack_contains(Stack*, void*);
bool stack_destroy(Stack*);

#endif
