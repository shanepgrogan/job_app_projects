// linked_list.cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "linked_list.h"

LinkedList::LinkedList(){};

// initialize linked list with data type size and name
LinkedList::LinkedList(int dataTypeSize, char* dataTypeName){
	size = 0;
	itemSize = dataTypeSize;
	type = dataTypeName;
	first = NULL;
	last = NULL;
};

LinkedList::LinkedList(const LinkedList& llist){
	size = llist.size;
	itemSize = llist.itemSize;
	type = llist.type;
	first = llist.first;
	last = llist.last;
};

// adds element to list at specified index
bool LinkedList::add_at(int index, void* elementPtr){
	
	// NULL checks
	if(elementPtr == NULL){
		return false;
	}
	if(index < 0 || index > size){
		return false;
	}

	// copy in data
	Node* newNode = &Node();//malloc(sizeof(Node));
	newNode->data = elementPtr;
	//newNode->data = malloc(itemSize);
	//memcpy(newNode->data, elementPtr, itemSize);	

	// conditional block for adding node
	if(size == 0){
		first = newNode;
	    last = newNode;
		newNode->prev = NULL;
		newNode->next = NULL;
		size++;
	} else if(index == 0){
		newNode->next = first;
		newNode->prev = NULL;
		first = newNode;
		first->next->prev = newNode;
		size++;
	} else if (index == size){
		newNode->prev = last;
		newNode->next = NULL;
		last = newNode;
		last->prev->next = newNode;
		size++;
	} else {
		Node* node = first;
		for(int i = 0; i < index; i++){
		 	node = node->next;
		}
		node->prev->next = newNode;
		node->prev = newNode;
		newNode->prev = node->prev;
		newNode->next = node;
		size++;
	}
	return true;
};

// adds element to front of list
bool LinkedList::add_first(void* elementPtr){
	add_at(0, elementPtr);
	return true;
};

// adds element to end of list
bool LinkedList::add_last(void* elementPtr){
	if(elementPtr == NULL){
		return false;
	}
	add_at(size, elementPtr);
	return true;
};

// retrieves element from specified index in list
void* const LinkedList::get(int index){

	if(index < 0 || index >= size){
		return NULL;
	}
	Node* outputPtr = first;
	int i = 0;
	while(i < index){
		outputPtr = outputPtr->next;
		i++;
	}
	return outputPtr->data;
};

// returns index of specified element in list
int const LinkedList::index_of(void* elementPtr){
	
	// NULL checks
	if(elementPtr == NULL){
		return -1;
	}

	int i = 0;
	Node* node = first;
	bool found = false;
	while(!found){
		if(node->data == elementPtr){
			found = true;
		} else {
			node = node->next;
			i++;
		}
	}

	if(i >= size){
		return -1;
	} else {
		return i;
	}
};

int LinkedList::get_size(){
	return size;
}

// removes element from list at specified index
void* LinkedList::remove(int index){

	// NULL checks
	if(first == NULL || last == NULL){
		return NULL;
	}
	if(index < 0 || index >= size){
		return NULL;
	}
	
	Node* removedNodePtr = &Node();//malloc(sizeof(Node));

	if(size == 1){
		removedNodePtr = first;
                first = NULL;
                removedNodePtr->next = NULL;
                size--;
	}
	else if(index == 0){
		removedNodePtr = first;
		first = removedNodePtr->next;
		removedNodePtr->next->prev = NULL;
		removedNodePtr->next = NULL;
		size--;
	}
	else if(index == size-1){
		removedNodePtr = last;
		last = removedNodePtr->prev;
		removedNodePtr->prev->next = NULL;
		removedNodePtr->prev = NULL;
		size--;
	}
	else{
		removedNodePtr = first;
		int i = 0;
	        while(i < index){
        	        removedNodePtr = removedNodePtr->next;
                	i++;
       		}	
		removedNodePtr->prev->next = removedNodePtr->next;
		removedNodePtr->next->prev = removedNodePtr->prev;
		removedNodePtr->next = NULL;
		removedNodePtr->prev = NULL;
		size--;
	}
	void* data = malloc(sizeof(itemSize));
	memcpy(data, removedNodePtr->data, itemSize);
	free(removedNodePtr->data);
	free(removedNodePtr);
	return data;
};

// removes element from front of list
void* LinkedList::remove_first(){
	return remove(0);
};

// removes element from end of list
void* LinkedList::remove_last(){
	return remove(size-1);
};

// destroys node data, then the nodes, then the list itself.
LinkedList::~LinkedList(){
	
	Node* node = first;
	for(int i = 0; i < size; i++){
		remove_last();
	}

	type = NULL;
	//free(llistPtr);
};
