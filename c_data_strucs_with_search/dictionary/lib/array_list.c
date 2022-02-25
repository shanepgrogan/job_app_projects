// array_list.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "array_list.h"

// initializes array list by defining max size, the data type and the size of 
// the data type
ArrayList* alist_initialize(int mSize, int dataTypeSize, char* dataTypeName){
	ArrayList* alistPtr = malloc(sizeof(ArrayList));
	alistPtr->size = 0;
	alistPtr->maxSize = mSize;
	alistPtr->itemSize = dataTypeSize;
	alistPtr->type = dataTypeName;
	alistPtr->arr = malloc(mSize*sizeof(void*));
};

// adds element to end of ArrayList
bool alist_add(ArrayList* alistPtr, void* elementPtr){
	if(elementPtr == NULL){
		return false;
	}
	alist_add_at(alistPtr, alistPtr->size, elementPtr);
};

// adds element to ArrayList at specified index
bool alist_add_at(ArrayList* alistPtr, int index, void* elementPtr){
	if(alistPtr == NULL || elementPtr == NULL){
                return false;
        }
	if(index < 0 || index > alistPtr->size){
		return false;
	}
	if(alistPtr->size == alistPtr->maxSize){
		_alist_resize(alistPtr);
	}
	int x = alistPtr->size;
	while( x >= index ){
		alistPtr->arr[x+1] = alistPtr->arr[x];
		x--;
	}	
	alistPtr->arr[index] = malloc(alistPtr->itemSize);
	memcpy(alistPtr->arr[index], elementPtr, alistPtr->itemSize);
	alistPtr->size++;
	return true;
};

// clears ArrayList
void alist_clear(ArrayList* alistPtr){
	for(int i = 0; i < alistPtr->size; i++){
		free(alistPtr->arr[i]);
	}
	alistPtr->size = 0;
};

// returns element at given index
void* alist_get(ArrayList* alistPtr, int index){
	if(index < 0 || index >= alistPtr->size){
		return NULL;
	}
	void* copy = malloc(alistPtr->itemSize);
	memcpy(copy, alistPtr->arr[index], alistPtr->itemSize);
	return copy;
};

// returns index at which given element is located
int alist_index_of(ArrayList* alistPtr, void* elementPtr){
	
	// NULL checks
	if(alistPtr == NULL || elementPtr == NULL){
		return -1;
	}
	
	int i = 0;
	while(alistPtr->arr[i] != elementPtr){
		i++;
	}
	
	if(i < alistPtr->size){
		return i;
	} else {
		return -1;
	}
};

// removes element from ArrayList at specified index
void* alist_remove(ArrayList* alistPtr, int index){
	
	// NULL checks
	if(alistPtr == NULL){
		return NULL;
	}
	if(index < 0 || index >= alistPtr->size){
		return NULL;
	}

	int x = index;
	free(alistPtr->arr[x]);
	while(x < alistPtr->size-1){
		alistPtr->arr[x] = alistPtr->arr[x+1];
		x++;
	}
	alistPtr->size--;	
};

// destroys given ArrayList
bool alist_destroy(ArrayList* alistPtr){
	
	// NULL check	
	if(alistPtr == NULL){
		return false;
	}
	
	for(int i = 0; i < alistPtr->size; i++){
                free(alistPtr->arr[i]);
        }
	free(alistPtr->arr);
	alistPtr->type = NULL;
	free(alistPtr);
	return true;
};

// resizes ArrayList
bool _alist_resize(ArrayList* alistPtr){
	
	int newSize = 2*(int)alistPtr->maxSize;
	alistPtr->maxSize = newSize;
	alistPtr->arr = realloc(alistPtr->arr, alistPtr->maxSize*sizeof(void*));
	
	// add check for boolean return
	if(sizeof(alistPtr) == newSize){
		return true;
	} else {
		return false;
	}
}
