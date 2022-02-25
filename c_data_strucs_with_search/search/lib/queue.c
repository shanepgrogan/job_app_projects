// queue.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "linked_list.h"
#include "queue.h"
// find out how to include linked_list.h

Queue* queue_initialize(int dataTypeSize, char* dataTypeName){
	Queue* qPtr = malloc(sizeof(Queue));
	qPtr->arr = llist_initialize(dataTypeSize, dataTypeName);	
	return qPtr;
}

bool queue_enqueue(Queue* qPtr, void* elementPtr){
	
	// NULL check
	if(qPtr == NULL || elementPtr == NULL){
		return false;
	}

	llist_add_first(qPtr->arr, elementPtr);
}

void* queue_dequeue(Queue* qPtr){
	
	// NULL check
	if(qPtr == NULL){
		return NULL;
	}

	llist_remove_last(qPtr->arr);
}

void* queue_peek(Queue* qPtr){
	
	// NULL check
	if(qPtr == NULL){
		return NULL;
	}

	llist_get(qPtr->arr, qPtr->arr->size-1);
}

int queue_size(Queue* qPtr){
	
	// NULL check
	if(qPtr == NULL){
		return -1;
	}
	
	return qPtr->arr->size;
}

bool queue_contains(Queue* qPtr, void* elementPtr){
	
	// NULL check
	if(qPtr == NULL || elementPtr == NULL){
		return false;
	}
	
	return (llist_index_of(qPtr->arr, elementPtr) >  -1);
}

bool queue_destroy(Queue* qPtr){
	
	// NULL check
	if(qPtr == NULL){
		return false;
	}
	
	llist_destroy(qPtr->arr);
	free(qPtr);
	return true;
}

