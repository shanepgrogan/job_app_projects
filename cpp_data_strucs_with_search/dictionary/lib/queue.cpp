// queue.cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "linked_list.h"
#include "queue.h"

Queue::Queue(){};

/* initialize queue by data type and size */
Queue::Queue(int dataTypeSize, char* dataTypeName): arr(&LinkedList(dataTypeSize, dataTypeName)) {};

Queue::Queue(const Queue& queue){};

/* add element to queue */
bool Queue::enqueue(void* elementPtr){
	
	// NULL check
	if(elementPtr == NULL){
		return false;
	}

	return arr->add_first(elementPtr);
}

/* remove element from queue */
void* Queue::dequeue(){
	return arr->remove_last();
}

/* returns last element in queue */
void* const Queue::peek(){
	
	return arr->get(arr->get_size()-1);

}

/* returns size of queue */
int const Queue::size(){
	
	return arr->get_size();

}

/* tells whether queue contains given element */
bool const Queue::contains(void* elementPtr){
	
	// NULL check
	if(elementPtr == NULL){
		return false;
	}
	
	return (arr->index_of(elementPtr) >  -1);
}

/* destroys queue by destroying underlying linked list
	and deallocating memeory */
Queue::~Queue(){
	
}

