// bintree.c
#include <stdbool.h>
#include "linked_list.h"
#include "bintree.h"
#include "stack.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Binary Tree initialized with inputs: size and type of data stored
	and functions for comparison and print */
BinaryTree* bintree_initialize(int dataTypeSize, char* dataTypeName, int (*comp)(void* , void*), void (*print)(void*)){
	BinaryTree* bintreePtr = malloc(sizeof(BinaryTree));
	bintreePtr->top = NULL;
        bintreePtr->itemSize = dataTypeSize;
        bintreePtr->type = dataTypeName;
        bintreePtr->compare = comp;
        bintreePtr->print = print;
	return bintreePtr;
};

/* creates node for Binary Tree */
BinaryTreeNode* bintree_create_node(int dataSize, void* elementPtr){
	BinaryTreeNode* node = malloc(sizeof(BinaryTreeNode));
	node->data = malloc(dataSize);
	node->data = elementPtr;
	node->left = NULL;
	node->right = NULL;
	return node;
};

/* inserts element into Binary Tree */
bool bintree_insert(BinaryTree* bintreePtr, void* elementPtr){
	
	// NULL check
	if(bintreePtr == NULL || elementPtr == NULL){
		return false;
	}
	
	if(bintreePtr->top == NULL){
		BinaryTreeNode* node = bintree_create_node(bintreePtr->itemSize, elementPtr);
		bintreePtr->top = node;
	} else {
		return _bintree_insert_recursive(bintreePtr, bintreePtr->top, elementPtr);
	}
};

/* searches for a given element in a given Binary Tree */
bool bintree_search(BinaryTree* bintreePtr, void* elementPtr){
	
	// NULL check
    if(bintreePtr == NULL || elementPtr == NULL){
        return false;
    }
	
    if(bintreePtr->top == NULL){
		return false;
	} else {
		return _bintree_search_recursive(bintreePtr, bintreePtr->top, elementPtr);
	}
};

/* recursively traverses Binary Tree from left to right (LNR)
	i.e. traverses left subtree, then parent node, then right subtree */
void bintree_print_in_order(BinaryTree* bintreePtr){
	if(bintreePtr != NULL){
		_bintree_in_order_recursive(bintreePtr, bintreePtr->top);
	}
};

/* recursively traverses Binary Tree from left to right (NLR)
	i.e. traverses parent node, then left subtree, then right subtree */
void bintree_print_pre_order(BinaryTree* bintreePtr){
	if(bintreePtr != NULL){
		_bintree_pre_order_recursive(bintreePtr, bintreePtr->top);
	}
};

/* recursively traverses Binary Tree from left to right (LRN)
	i.e. traverses left subtree, then right subtree, then parent node */
void bintree_print_post_order(BinaryTree* bintreePtr){
	if(bintreePtr != NULL){
        	_bintree_post_order_recursive(bintreePtr, bintreePtr->top);
	}
};

/* recursively traverses Binary Tree from left to right (RNL)
	i.e. traverses right subtree, then parent node, then left subtree */
void bintree_print_reverse_order(BinaryTree* bintreePtr){
	if(bintreePtr != NULL){
        	_bintree_reverse_order_recursive(bintreePtr, bintreePtr->top);
	}
};

/* recursively inserts element, determining where it goes by comparing
	it to the data of a given node */
bool _bintree_insert_recursive(BinaryTree* bintreePtr, BinaryTreeNode* node, void* elementPtr){
	
	// NULL check
	if(bintreePtr == NULL || node == NULL || elementPtr == NULL){
		return false;
	}

	if(bintreePtr->compare(node->data, elementPtr) < 0){
		if(node->left == NULL){
			BinaryTreeNode* new = malloc(sizeof(BinaryTreeNode));
			new->data = elementPtr;
			node->left = new;
		} else {
			return _bintree_insert_recursive(bintreePtr, node->left, elementPtr);
		}
	} else {
		if(node->right == NULL){
                        BinaryTreeNode* new = malloc(sizeof(BinaryTreeNode));
                        new->data = elementPtr;
                        node->right = new;
                } else {
                        return _bintree_insert_recursive(bintreePtr, node->right, elementPtr);
                }
	}

	return true;
};

/* recursively searches for element in certain subtree given root node.
	Searches left or right subtree if no match is found. */
bool _bintree_search_recursive(BinaryTree* bintreePtr, BinaryTreeNode* node, void* elementPtr){

	  // NULL check
          if(bintreePtr == NULL || node == NULL || elementPtr == NULL){
		  return false;
          }
	  
	  int c = bintreePtr->compare(node->data, elementPtr);
	  
	  if(c < 0){
		  if(node->left != NULL){
			  return _bintree_search_recursive(bintreePtr, node->left, elementPtr);
		  } else {
			  return false;
		  }
	  } else if(c > 0){
		  if(node->right != NULL){
			  return _bintree_search_recursive(bintreePtr, node->right, elementPtr);;
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
void _bintree_in_order_recursive(BinaryTree* bintreePtr, BinaryTreeNode* node){
	if(bintreePtr != NULL && node != NULL){
		_bintree_in_order_recursive(bintreePtr, node->left);
		bintreePtr->print(node->data);
		_bintree_in_order_recursive(bintreePtr, node->right);
	}
};

void _bintree_pre_order_recursive(BinaryTree* bintreePtr, BinaryTreeNode* node){
        if(bintreePtr != NULL && node != NULL){
		bintreePtr->print(node->data);
		_bintree_pre_order_recursive(bintreePtr, node->left);
        	_bintree_pre_order_recursive(bintreePtr, node->right);
	}
};

void _bintree_post_order_recursive(BinaryTree* bintreePtr, BinaryTreeNode* node){
	if(bintreePtr != NULL && node != NULL){
		_bintree_post_order_recursive(bintreePtr, node->left);
        	_bintree_post_order_recursive(bintreePtr, node->right);
		bintreePtr->print(node->data);
	}
};

void _bintree_reverse_order_recursive(BinaryTree* bintreePtr, BinaryTreeNode* node){
	if(bintreePtr != NULL && node != NULL){
		_bintree_reverse_order_recursive(bintreePtr, node->right);
        	bintreePtr->print(node->data);
		_bintree_reverse_order_recursive(bintreePtr, node->left);
	}
};

/* depth-first binary tree traversal */
void bintree_print_depth_first(BinaryTree* bintreePtr){
        Stack* stackPtr = stack_initialize(sizeof(BinaryTreeNode), "BinaryTreeNode");
	stack_push(stackPtr, bintreePtr->top);
	BinaryTreeNode* node = NULL;
	while(stack_size(stackPtr) != 0){
		node = stack_pop(stackPtr);
		bintreePtr->print(node->data);
		if(node->right != NULL){
			stack_push(stackPtr, node->right);
		}
		if(node->left != NULL){
			stack_push(stackPtr, node->left);
		}
	}
}

/* breadth-first binary tree traversal */
void bintree_print_breadth_first(BinaryTree* bintreePtr){
	
       	Queue* qPtr = queue_initialize(sizeof(BinaryTreeNode), "BinaryTreeNode");
	queue_enqueue(qPtr, bintreePtr->top);
        BinaryTreeNode* node = NULL;
	
	while(queue_size(qPtr) != 0){
                node = queue_dequeue(qPtr);
                bintreePtr->print(node->data);
                if(node->left != NULL){
			queue_enqueue(qPtr, node->left);
		}
		if(node->right != NULL){
			queue_enqueue(qPtr, node->right);
		}
	}
}

/* same as regular insert function, with added feature that if a duplicate node
	is found, its data will be overwritten by the input element */
bool bintree_insert_replace(BinaryTree* bintreePtr, void* elementPtr){
	
	// NULL check
        if(bintreePtr == NULL || elementPtr == NULL){
                return false;
        }
	
	if(bintreePtr->top == NULL){
                BinaryTreeNode* node = bintree_create_node(bintreePtr->itemSize, elementPtr);
                bintreePtr->top = node;
        } else {
                return _bintree_insert_replace_recursive(bintreePtr, bintreePtr->top, elementPtr);
        }

}

/* recursive helper function for the insert-replace function */
bool _bintree_insert_replace_recursive(BinaryTree* bintreePtr, BinaryTreeNode* node, void* elementPtr){

	// NULL check
        if(bintreePtr == NULL || node == NULL || elementPtr == NULL){
             return false;
        }
	
	if(bintreePtr->compare(node->data, elementPtr) == 0){
		node->data = elementPtr;
		return true;
	} else if (bintreePtr->compare(node->data, elementPtr) < 0){
                if(node->left == NULL){
                        BinaryTreeNode* new = malloc(sizeof(BinaryTreeNode));
                        new->data = elementPtr;
                        node->left = new;
                } else {
                        return _bintree_insert_replace_recursive(bintreePtr, node->left, elementPtr);
                }
        } else {
                if(node->right == NULL){
                        BinaryTreeNode* new = malloc(sizeof(BinaryTreeNode));
                        new->data = elementPtr;
                        node->right = new;
                } else {
                        return _bintree_insert_replace_recursive(bintreePtr, node->right, elementPtr);
                }
        }

        return true;

}
