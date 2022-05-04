// bintree.cpp
#include <stdbool.h>
#include "linked_list.h"
#include "bintree.h"
#include "lib/stack.h"
#include "lib/queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

BinaryTree::BinaryTree(){};

/* Binary Tree initialized with inputs: size and type of data stored
	and functions for comparison and print */
BinaryTree::BinaryTree(int dataTypeSize, char* dataTypeName, int (*comp)(void* , void*), void (*print)(void*)){
	//BinaryTree* bintreePtr = malloc(sizeof(BinaryTree));
	// bintreePtr->top = NULL;
    //     bintreePtr->itemSize = dataTypeSize;
    //     bintreePtr->type = dataTypeName;
    //     bintreePtr->compare = comp;
    //     bintreePtr->print = print;
	this->top = NULL;
	this->itemSize = dataTypeSize;
	this->type = dataTypeName;
	this->compare = comp;
	this->print = print;

};

BinaryTree::BinaryTree(const BinaryTree& binTree){};

/* creates node for Binary Tree */
BinaryTreeNode* BinaryTree::create_node(int dataSize, void* elementPtr){
	//BinaryTreeNode* node = malloc(sizeof(BinaryTreeNode));
	BinaryTreeNode* node = &BinaryTreeNode();
	node->data = malloc(dataSize);
	node->data = elementPtr;
	node->left = NULL;
	node->right = NULL;
	return node;
};

/* retreives top node of Binary Tree */
BinaryTreeNode* BinaryTree::get_top_node(){
	return top;
};

/* inserts element into Binary Tree */
bool BinaryTree::insert(void* elementPtr){
	
	// NULL check
	if(elementPtr == NULL){
		return false;
	}
	
	if(top == NULL){
		BinaryTreeNode* node = create_node(itemSize, elementPtr);
		top = node;
	} else {
		return _insert_recursive(top, elementPtr);
	}
};

/* searches for a given element in a given Binary Tree */
bool BinaryTree::search(void* elementPtr){
	
	// NULL check
    if(elementPtr == NULL){
        return false;
    }
	
    if(top == NULL){
		return false;
	} else {
		return _search_recursive(top, elementPtr);
	}
};

/* recursively traverses Binary Tree from left to right (LNR)
	i.e. traverses left subtree, then parent node, then right subtree */
void BinaryTree::print_in_order(){
	if(this != NULL){
		_in_order_recursive(top);
	}
};

/* recursively traverses Binary Tree from left to right (NLR)
	i.e. traverses parent node, then left subtree, then right subtree */
void BinaryTree::print_pre_order(){
	if(this != NULL){
		_pre_order_recursive(top);
	}
};

/* recursively traverses Binary Tree from left to right (LRN)
	i.e. traverses left subtree, then right subtree, then parent node */
void BinaryTree::print_post_order(){
	if(this != NULL){
		_post_order_recursive(top);
	}
};

/* recursively traverses Binary Tree from left to right (RNL)
	i.e. traverses right subtree, then parent node, then left subtree */
void BinaryTree::print_reverse_order(){
	if(this != NULL){
        _reverse_order_recursive(top);
	}
};

/* recursively inserts element, determining where it goes by comparing
	it to the data of a given node */
bool BinaryTree::_insert_recursive(BinaryTreeNode* node, void* elementPtr){
	
	// NULL check
	if(node == NULL || elementPtr == NULL){
		return false;
	}

	if(compare(node->data, elementPtr) < 0){
		if(node->left == NULL){
			BinaryTreeNode* newNode = &BinaryTreeNode();//malloc(sizeof(BinaryTreeNode));
			newNode->data = elementPtr;
			node->left = newNode;
		} else {
			return _insert_recursive(node->left, elementPtr);
		}
	} else {
		if(node->right == NULL){
			BinaryTreeNode* newNode = &BinaryTreeNode();//malloc(sizeof(BinaryTreeNode));
			newNode->data = elementPtr;
			node->right = newNode;
		} else {
			return _insert_recursive(node->right, elementPtr);
		}
	}

	return true;
};

/* recursively searches for element in certain subtree given root node.
	Searches left or right subtree if no match is found. */
bool BinaryTree::_search_recursive(BinaryTreeNode* node, void* elementPtr){

	  // NULL check
	  if(node == NULL || elementPtr == NULL){
		  return false;
	  }
	  
	  int c = compare(node->data, elementPtr);
	  
	  if(c < 0){
		  if(node->left != NULL){
			  return _search_recursive(node->left, elementPtr);
		  } else {
			  return false;
		  }
	  } else if(c > 0){
		  if(node->right != NULL){
			  return _search_recursive(node->right, elementPtr);;
		  } else {
			  return false;
		  }
	  } else if (c == 0){
		  if(node->data != NULL){
			  return true;
		  } else {
			  return false;
		  }
	  }

};

/* recursive helper functions for the traversal functions*/
void BinaryTree::_in_order_recursive(BinaryTreeNode* node){
	if(this != NULL && node != NULL){
		_in_order_recursive(node->left);
		print(node->data);
		_in_order_recursive(node->right);
	}
};

void BinaryTree::_pre_order_recursive(BinaryTreeNode* node){
	if(this != NULL && node != NULL){
		print(node->data);
		_pre_order_recursive(node->left);
		_pre_order_recursive(node->right);
	}
};

void BinaryTree::_post_order_recursive(BinaryTreeNode* node){
	if(this != NULL && node != NULL){
		_post_order_recursive(node->left);
        _post_order_recursive(node->right);
		print(node->data);
	}
};

void BinaryTree::_reverse_order_recursive(BinaryTreeNode* node){
	if(this != NULL && node != NULL){
		_reverse_order_recursive(node->right);
        print(node->data);
		_reverse_order_recursive(node->left);
	}
};

/* depth-first binary tree traversal */
void BinaryTree::print_depth_first(){
    Stack* stackPtr = &Stack();//&Stack(sizeof(BinaryTreeNode), "BinaryTreeNode");
	stackPtr->push(top);
	BinaryTreeNode* node = NULL;
	while(stackPtr->size() != 0){
		node->data = stackPtr->pop();
		print(node->data);
		if(node->right != NULL){
			stackPtr->push(node->right);
		}
		if(node->left != NULL){
			stackPtr->push(node->left);
		}
	}
}

/* breadth-first binary tree traversal */
void BinaryTree::print_breadth_first(){
	
    Queue* qPtr = &Queue(sizeof(BinaryTreeNode), "BinaryTreeNode");
	qPtr->enqueue(top);
    BinaryTreeNode* node = NULL;
	
	while(qPtr->size() != 0){
		node->data = qPtr->dequeue();
		print(node->data);
		if(node->left != NULL){
			qPtr->enqueue(node->left);
		}
		if(node->right != NULL){
			qPtr->enqueue(node->right);
		}
	}
}

/* same as regular insert function, with added feature that if a duplicate node
	is found, its data will be overwritten by the input element */
bool BinaryTree::insert_replace(void* elementPtr){
	
	// NULL check
	if(this == NULL || elementPtr == NULL){
			return false;
	}
	
	if(this->top == NULL){
		BinaryTreeNode* node = create_node(itemSize, elementPtr);
		top = node;
	} else {
		return _insert_replace_recursive(top, elementPtr);
	}

}

/* recursive helper function for the insert-replace function */
bool BinaryTree::_insert_replace_recursive(BinaryTreeNode* node, void* elementPtr){

	// NULL check
	if(this == NULL || node == NULL || elementPtr == NULL){
			return false;
	}
	
	if(compare(node->data, elementPtr) == 0){
		node->data = elementPtr;
		return true;
	} else if (compare(node->data, elementPtr) < 0){
		if(node->left == NULL){
			BinaryTreeNode* newNode = &BinaryTreeNode();
			newNode->data = elementPtr;
			node->left = newNode;
			} else {
				return _insert_replace_recursive(node->left, elementPtr);
			}
        } else {
			if(node->right == NULL){
					BinaryTreeNode* newNode = &BinaryTreeNode();//malloc(sizeof(BinaryTreeNode));
					newNode->data = elementPtr;
					node->right = newNode;
			} else {
					return _insert_replace_recursive(node->right, elementPtr);
			}
        }

        return true;

}
