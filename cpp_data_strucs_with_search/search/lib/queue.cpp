// queue.cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "linked_list.h"
#include "queue.h"

/* initialize queue by data type and size */
Queue* queue_initialize(int dataTypeSize, char* dataTypeName){
	Queue* qPtr = malloc(sizeof(Queue));
	qPtr->arr = llist_initialize(dataTypeSize, dataTypeName);	
	return qPtr;
}

/* add element to queue */
bool queue_enqueue(Queue* qPtr, void* elementPtr){
	
	// NULL check
	if(qPtr == NULL || elementPtr == NULL){
		return false;
	}

	llist_add_first(qPtr->arr, elementPtr);
}

/* remove element from queue */
void* queue_dequeue(Queue* qPtr){
	
	// NULL check
	if(qPtr == NULL){
		return NULL;
	}

	llist_remove_last(qPtr->arr);
}

/* returns last element in queue */
void* queue_peek(Queue* qPtr){
	
	// NULL check
	if(qPtr == NULL){
		return NULL;
	}

	llist_get(qPtr->arr, qPtr->arr->size-1);
}

/* returns size of queue */
int queue_size(Queue* qPtr){
	
	// NULL check
	if(qPtr == NULL){
		return -1;
	}
	
	return qPtr->arr->size;
}

/* tells whether queue contains given element */
bool queue_contains(Queue* qPtr, void* elementPtr){
	
	// NULL check
	if(qPtr == NULL || elementPtr == NULL){
		return false;
	}
	
	return (llist_index_of(qPtr->arr, elementPtr) >  -1);
}

/* destroys queue by destroying underlying linked list
	and deallocating memeory */
bool queue_destroy(Queue* qPtr){
	
	// NULL check
	if(qPtr == NULL){
		return false;
	}
	
	llist_destroy(qPtr->arr);
	free(qPtr);
	return true;
}

