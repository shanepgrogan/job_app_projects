// dictionary.cpp
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "lib/array_list.h"
#include "bintree.h"
#include "dictionary.h"

Dictionary::Dictionary(){};

/* initializes dictionary by passing comparison and print functions */
Dictionary::Dictionary(int (*compare)(void*, void*), void (*print)(void*)){
	//Dictionary* dicPtr = malloc(sizeof(Dictionary));
	this->tree = &BinaryTree((int)sizeof(Pair), "Pair", compare, print);
	//return dicPtr;
};

Dictionary::Dictionary(const Dictionary& dict){};

/* inserts key-value pair into dictionary */
bool Dictionary::insert(void* keyPtr, void* valuePtr){
	if(keyPtr == NULL || valuePtr == NULL){
		return false;
	}
	Pair* pairPtr = new Pair;//malloc(sizeof(Pair));
	pairPtr->first = keyPtr;
	pairPtr->second = valuePtr;
	tree->insert_replace(pairPtr);	
	return true;	
};

/* recursive helper function for dict_get */
void* Dictionary::_get_recursive(BinaryTreeNode* node, void* keyPtr){
	// NULL check
	if(node == NULL || keyPtr == NULL){
		return NULL;
	}
	
	if(node->data == NULL){
		return NULL;
	}

	Pair* pair1 = node->data;
	Pair* pair2 = keyPtr;
	
	int c = tree->compare(pair1, pair2);
	
	if(c < 0){
		if(node->left != NULL){
			return _get_recursive(node->left, keyPtr);
		} else {
			return NULL;
		}
	} else if(c > 0){
		if(node->right != NULL){
			return _get_recursive(node->right, keyPtr);;
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

/* returns element from dictionary by iterating through
	underlying binary tree recursively */
void* Dictionary::get(void* keyPtr){
        // NULL check
        if(keyPtr == NULL){
			return NULL;
        }
	
        if(tree->get_top_node() == NULL){
			return NULL;
        } else {
			return _get_recursive(tree->get_top_node(), keyPtr);
        }
}

/* recursive helper fucntion for dict_key_list */
void Dictionary::_key_list_recursive(ArrayList* alistPtr, BinaryTree* bintreePtr, BinaryTreeNode* node){
        if(alistPtr != NULL && bintreePtr != NULL && node != NULL){
		Pair* pair = node->data;
		_key_list_recursive(alistPtr, bintreePtr, node->left);
		alistPtr->add(pair->first);
		_key_list_recursive(alistPtr, bintreePtr, node->right);
	}
};

/* returns arraylist of keys in dictionary */
ArrayList* Dictionary::key_list(int size){
	if(size >= 0){
		ArrayList* keyList = ArrayList(10, size, "char[50]");
		_key_list_recursive(keyList, tree, tree->get_top_node());
		return keyList;
	}	
};

/* tells whether dictionary contains a given key */
bool Dictionary::contains(void* keyPtr){
	// NULL check
	if(keyPtr == NULL){
		return false;
	}
	Pair* pair = new Pair;
	pair->first = keyPtr;
	return tree->search(pair);	
};

