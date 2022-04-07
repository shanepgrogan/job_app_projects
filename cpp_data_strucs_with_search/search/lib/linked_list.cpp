// linked_list.cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "linked_list.h"

// initialize linked list with data type size and name
LinkedList* llist_initialize(int dataTypeSize, char* dataTypeName){
	LinkedList* llistPtr = malloc(sizeof(LinkedList));
	llistPtr->size = 0;
	llistPtr->itemSize = dataTypeSize;
	llistPtr->type = dataTypeName;
	llistPtr->first = NULL;
	llistPtr->last = NULL;
	return llistPtr;
};

// adds element to list at specified index
bool llist_add_at(LinkedList* llistPtr, int index, void* elementPtr){
	
	// NULL checks
	if(llistPtr == NULL || elementPtr == NULL){
		return false;
	}
	if(index<0 || index>llistPtr->size){
		return false;
	}

	// copy in data
	Node* new = malloc(sizeof(Node));
	new->data = malloc(llistPtr->itemSize);
	memcpy(new->data, elementPtr, llistPtr->itemSize);	

	// conditional block for adding node
	if(llistPtr->size == 0){
		llistPtr->first = new;
	       	llistPtr->last= new;
		new->prev = NULL;
		new->next = NULL;
		llistPtr->size++;
	} else if(index == 0){
		new->next = llistPtr->first;
		new->prev = NULL;
		llistPtr->first = new;
		llistPtr->first->next->prev = new;
		llistPtr->size++;
	} else if (index == llistPtr->size){
		new->prev = llistPtr->last;
		new->next = NULL;
		llistPtr->last = new;
		llistPtr->last->prev->next = new;
		llistPtr->size++;
	} else {
		Node* node = llistPtr->first;
		for(int i = 0; i < index; i++){
		 	node = node->next;
		}
		node->prev->next = new;
		node->prev = new;
		new->prev = node->prev;
		new->next = node;
		llistPtr->size++;
	}
	return true;
};

// adds element to front of list
bool llist_add_first(LinkedList* llistPtr, void* elementPtr){
	llist_add_at(llistPtr, 0, elementPtr);
	return true;
};

// adds element to end of list
bool llist_add_last(LinkedList* llistPtr, void* elementPtr){
	if(llistPtr == NULL){
		return false;
	}
	llist_add_at(llistPtr, llistPtr->size, elementPtr);
	return true;
};

// retrieves element from specified index in list
void* llist_get(LinkedList* llistPtr, int index){
	if(llistPtr == NULL){
		return NULL;
	}
	if(index < 0 || index >= llistPtr->size){
		return NULL;
	}
	Node* outputPtr = llistPtr->first;
	int i = 0;
	while(i < index){
		outputPtr = outputPtr->next;
		i++;
	}
	return outputPtr->data;
};

// returns index of specified element in list
int llist_index_of(LinkedList* llistPtr, void* elementPtr){
	
	// NULL checks
	if(llistPtr == NULL || elementPtr == NULL){
		return -1;
	}

	int i = 0;
	Node* node = llistPtr->first;
	bool found = false;
	while(!found){
		if(node->data == elementPtr){
			found = true;
		} else {
			node = node->next;
			i++;
		}
	}

	if(i >= llistPtr->size){
		return -1;
	} else {
		return i;
	}
};

// removes element from list at specified index
void* llist_remove(LinkedList* llistPtr, int index){

	// NULL checks
	if(llistPtr == NULL){
		return NULL;
	}
	if(llistPtr->first == NULL || llistPtr->last == NULL){
		return NULL;
	}
	if(index < 0 || index >= llistPtr->size){
		return NULL;
	}
	
	Node* removedNodePtr = malloc(sizeof(Node));

	if(llistPtr->size == 1){
		removedNodePtr = llistPtr->first;
                llistPtr->first = NULL;
                removedNodePtr->next = NULL;
                llistPtr->size--;
	}
	else if(index == 0){
		removedNodePtr = llistPtr->first;
		llistPtr->first = removedNodePtr->next;
		removedNodePtr->next->prev = NULL;
		removedNodePtr->next = NULL;
		llistPtr->size--;
	}
	else if(index == llistPtr->size-1){
		removedNodePtr = llistPtr->last;
		llistPtr->last = removedNodePtr->prev;
		removedNodePtr->prev->next = NULL;
		removedNodePtr->prev = NULL;
		llistPtr->size--;
	}
	else{
		removedNodePtr = llistPtr->first;
		int i = 0;
	        while(i < index){
        	        removedNodePtr = removedNodePtr->next;
                	i++;
       		}	
		removedNodePtr->prev->next = removedNodePtr->next;
		removedNodePtr->next->prev = removedNodePtr->prev;
		removedNodePtr->next = NULL;
		removedNodePtr->prev = NULL;
		llistPtr->size--;
	}
	void* data = malloc(sizeof(llistPtr->itemSize));
	memcpy(data, removedNodePtr->data, llistPtr->itemSize);
	free(removedNodePtr->data);
	free(removedNodePtr);
	return data;
};

// removes element from front of list
void* llist_remove_first(LinkedList* llistPtr){
	if(llistPtr == NULL){
		return NULL;
	}
	llist_remove(llistPtr, 0);
};

// removes element from end of list
void* llist_remove_last(LinkedList* llistPtr){
	if(llistPtr == NULL){
                return NULL;
        }
	llist_remove(llistPtr, llistPtr->size-1);
};

// destroys node data, then the nodes, then the list itself.
bool llist_destroy(LinkedList* llistPtr){

	if(llistPtr == NULL){
		return false;
	}
	
	Node* node = llistPtr->first;
	for(int i = 0; i < llistPtr->size; i++){
		llist_remove_last(llistPtr);
	}

	llistPtr->type = NULL;
	free(llistPtr);
	return true;
};
