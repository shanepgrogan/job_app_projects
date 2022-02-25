// stack.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linked_list.h"
#include "stack.h"

Stack* stack_initialize(int dataTypeSize, char* dataTypeName){
	Stack* stackPtr = malloc(sizeof(Stack));
	stackPtr->arr = llist_initialize(dataTypeSize, dataTypeName);
	return stackPtr;
}

bool stack_push(Stack* stackPtr, void* elementPtr){
	
	// NULL check
	if(stackPtr == NULL || elementPtr == NULL){
		return false;
	}

	llist_add_first(stackPtr->arr, elementPtr);
}

void* stack_pop(Stack* stackPtr){
       
	// NULL check
        if(stackPtr == NULL){
                return false;
        }

	llist_remove_first(stackPtr->arr);
}

void* stack_peek(Stack* stackPtr){

	// NULL check
        if(stackPtr == NULL){
                return false;
        }

	llist_get(stackPtr->arr, 0);
}

int stack_size(Stack* stackPtr){

	// NULL check
        if(stackPtr == NULL){
                return false;
        }

	return stackPtr->arr->size;
}

bool stack_contains(Stack* stackPtr, void* elementPtr){
	
	// NULL check
        if(stackPtr == NULL || elementPtr == NULL){
                return false;
        }

	return llist_index_of(stackPtr->arr, elementPtr) > -1;
}

bool stack_destroy(Stack* stackPtr){
	
	// NULL check
        if(stackPtr == NULL){
                return false;
        }

	llist_destroy(stackPtr->arr);
	free(stackPtr);
	return true;
}
