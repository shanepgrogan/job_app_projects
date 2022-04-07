// stack.cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linked_list.h"
#include "stack.h"

Stack::Stack(){};

/* initialize stack according to data type and size */
Stack::Stack(int dataTypeSize, char* dataTypeName){
	arr = &LinkedList(dataTypeSize, dataTypeName);
}

Stack::Stack(const Stack& stack){};

/* pushes element onto the stack */
bool Stack::push(void* elementPtr){
	
	// NULL check
	if(elementPtr == NULL){
		return false;
	}

	return arr->add_first(elementPtr);
}

/* removes and returns element from top of stack */
void* Stack::pop(){

	 return arr->remove_first();

}

/* returns element from top of stack */
void* Stack::peek(){

	return arr->get(0);

}

/* returns stack size */
int Stack::size(){

	return arr->get_size();
}

/* tells whether or not stack contains element */
bool Stack::contains(void* elementPtr){
	
	// NULL check
    if(elementPtr == NULL){
        return false;
    }

	return arr->index_of(elementPtr) > -1;
}

/* destroys stack by destroying underlying linked list
	and deallocating memory */
Stack::~Stack(){
	
}
