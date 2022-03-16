// stack.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linked_list.h"
#include "stack.h"

/* initialize stack according to data type and size */
Stack* stack_initialize(int dataTypeSize, char* dataTypeName){
	Stack* stackPtr = malloc(sizeof(Stack));
	stackPtr->arr = llist_initialize(dataTypeSize, dataTypeName);
	return stackPtr;
}

/* pushes element onto the stack */
bool stack_push(Stack* stackPtr, void* elementPtr){
	
	// NULL check
	if(stackPtr == NULL || elementPtr == NULL){
		return false;
	}

	llist_add_first(stackPtr->arr, elementPtr);
}

/* removes and returns element from top of stack */
void* stack_pop(Stack* stackPtr){
       
	// NULL check
        if(stackPtr == NULL){
                return false;
        }

	llist_remove_first(stackPtr->arr);
}

/* returns element from top of stack */
void* stack_peek(Stack* stackPtr){

	// NULL check
        if(stackPtr == NULL){
                return false;
        }

	llist_get(stackPtr->arr, 0);
}

/* returns stack size */
int stack_size(Stack* stackPtr){

	// NULL check
        if(stackPtr == NULL){
                return false;
        }

	return stackPtr->arr->size;
}

/* tells whether or not stack contains element */
bool stack_contains(Stack* stackPtr, void* elementPtr){
	
	// NULL check
        if(stackPtr == NULL || elementPtr == NULL){
                return false;
        }

	return llist_index_of(stackPtr->arr, elementPtr) > -1;
}

/* destroys stack by destroying underlying linked list
	and deallocating memory */
bool stack_destroy(Stack* stackPtr){
	
	// NULL check
        if(stackPtr == NULL){
                return false;
        }

	llist_destroy(stackPtr->arr);
	free(stackPtr);
	return true;
}
