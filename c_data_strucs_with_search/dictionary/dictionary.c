// dictionary.c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "array_list.h"
#include "bintree.h"
#include "dictionary.h"

Dictionary* dict_initialize(int (*comp)(void*, void*), void (*print)(void*)){
	Dictionary* dicPtr = malloc(sizeof(Dictionary));
	dicPtr->tree = bintree_initialize(sizeof(Pair), "Pair", comp, print);
	dicPtr->tree->compare = comp;
	dicPtr->tree->print = print;
	return dicPtr;
};

bool dict_insert(Dictionary* dicPtr, void* keyPtr, void* valuePtr){
	if(dicPtr == NULL || keyPtr == NULL || valuePtr == NULL){
		return false;
	}
	Pair* pairPtr = malloc(sizeof(Pair));
	pairPtr->first = keyPtr;
	pairPtr->second = valuePtr;
	bintree_insert_replace(dicPtr->tree, pairPtr);	
	return true;	
};

void* _dict_get_recursive(Dictionary* dicPtr, BinaryTreeNode* node, void* keyPtr){
	  // NULL check
          if(dicPtr == NULL || node == NULL || keyPtr == NULL){
          	return NULL;
          }
	  
	  if(node->data == NULL){
	  	return NULL;
	  }

	  Pair* pair1 = node->data;
	  Pair* pair2 = malloc(sizeof(Pair));
	  pair2->first = keyPtr;
	  
	  int c = dicPtr->tree->compare(pair1, pair2);
	  
          if(c < 0){
                  if(node->left != NULL){
			  return _dict_get_recursive(dicPtr, node->left, keyPtr);
                  } else {
                          return NULL;
                  }
          } else if(c > 0){
                  if(node->right != NULL){
                          return _dict_get_recursive(dicPtr, node->right, keyPtr);;
                  } else {
                          return NULL;
                  }
          } else if (c == 0){
                  if(node->data != NULL){
                          return pair1->second;
                  } else {
                          return NULL;
                  }
          }
	
}

void* dict_get(Dictionary* dicPtr, void* keyPtr){
        // NULL check
        if(dicPtr == NULL || keyPtr == NULL){
                return NULL;
        }
	
        if(dicPtr->tree->top == NULL){
                return NULL;
        } else {
                return _dict_get_recursive(dicPtr, dicPtr->tree->top, keyPtr);
        }
}

void _dict_key_list_recursive(ArrayList* alistPtr, BinaryTree* bintreePtr, BinaryTreeNode* node){
        if(alistPtr != NULL && bintreePtr != NULL && node != NULL){
		Pair* pair = node->data;
		_dict_key_list_recursive(alistPtr, bintreePtr, node->left);
		alist_add(alistPtr, pair->first);
		_dict_key_list_recursive(alistPtr, bintreePtr, node->right);
	}
};

ArrayList* dict_key_list(Dictionary* dicPtr, int size){
	if(dicPtr != NULL && size >= 0){
		ArrayList* keyList = alist_initialize(10, size, "char[50]");
		_dict_key_list_recursive(keyList, dicPtr->tree, dicPtr->tree->top);
		return keyList;
	}	
};

bool dict_contains(Dictionary* dicPtr, void* keyPtr){
	// NULL check
	if(dicPtr == NULL || keyPtr == NULL){
		return false;
	}
	Pair* pair = malloc(sizeof(Pair));
	pair->first = keyPtr;
	return bintree_search(dicPtr->tree, pair);	
};

