// array_list.cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "array_list.h"

// initializes array list by defining max size, the data type and the size of 
// the data type
ArrayList::ArrayList(){};

ArrayList::ArrayList(int mSize, int dataTypeSize, char* dataTypeName){
	size = 0;
	maxSize = mSize;
	itemSize = dataTypeSize;
	type = dataTypeName;
	//arr = malloc(mSize*sizeof(void*));
};

ArrayList::ArrayList(const ArrayList& alist){};

// adds element to end of ArrayList
bool ArrayList::add(void* elementPtr){
	if(elementPtr == NULL){
		return false;
	}
	this->add_at(size, elementPtr);
};

// adds element to ArrayList at specified index
bool ArrayList::add_at(int index, void* elementPtr){
	if(elementPtr == NULL){
                return false;
        }
	if(index < 0 || index > this->size){
		return false;
	}
	if(this->size == this->maxSize){
		this->resize();
	}
	int x = this->size;
	while( x >= index ){
		this->arr[x+1] = this->arr[x];
		x--;
	}	
	this->arr[index] = malloc(this->itemSize);
	memcpy(this->arr[index], elementPtr, this->itemSize);
	this->size++;
	return true;
};

// clears ArrayList
void ArrayList::clear(){
	for(int i = 0; i < this->size; i++){
		free(this->arr[i]);
	}
	this->size = 0;
};

// returns element at given index
void* const ArrayList::get(int index){
	if(index < 0 || index >= this->size){
		return NULL;
	}
	void* copy = malloc(this->itemSize);
	memcpy(copy, this->arr[index], this->itemSize);
	return copy;
};

// returns index at which given element is located
int const ArrayList::index_of(void* elementPtr){
	
	// NULL checks
	if(elementPtr == NULL){
		return -1;
	}
	
	int i = 0;
	while(this->arr[i] != elementPtr){
		i++;
	}
	
	if(i < this->size){
		return i;
	} else {
		return -1;
	}
};

// removes element from ArrayList at specified index
void* ArrayList::remove(int index){
	
	// NULL checks
	if(this == NULL){
		return NULL;
	}
	if(index < 0 || index >= this->size){
		return NULL;
	}

	int x = index;
	free(this->arr[x]);
	while(x < this->size-1){
		this->arr[x] = this->arr[x+1];
		x++;
	}
	this->size--;	
};

// destroys given ArrayList
ArrayList::~ArrayList(){
	
	// NULL check	
	// if(alistPtr == NULL){
	// 	return false;
	// }
	
	for(int i = 0; i < this->size; i++){
        free(this->arr[i]);
    }
	free(this->arr);
	this->type = NULL;
	free(this);
	//return true;
};

// resizes ArrayList
bool ArrayList::resize(){
	
	int newSize = 2*(int)this->maxSize;
	this->maxSize = newSize;
	//this->arr = realloc(this->arr, this->maxSize*sizeof(void*));
	
	// add check for boolean return
	if(sizeof(this) == newSize){
		return true;
	} else {
		return false;
	}
}

// main function
int main() {


	return 0;

}