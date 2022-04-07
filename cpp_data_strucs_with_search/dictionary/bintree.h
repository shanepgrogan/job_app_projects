// bintree.h
#ifndef __BINTREE_HEADER
#define __BINTREE_HEADER

typedef struct _BinTreeNode{
	void* data;
	struct _BinTreeNode* left;
	struct _BinTreeNode* right;
} BinaryTreeNode;

class BinaryTree{
	private:
		BinaryTreeNode* top;
		int itemSize;
		char* type;
		int (*compare)(void*, void*);
		void(*print)(void*);
	public:
		BinaryTree(){};
		BinaryTree(int, char*, int (*)(void*, void*), void (*)(void*)){};
		BinaryTree(const BinaryTree&){};
		BinaryTreeNode* create_node(int, void*);
		bool insert(void*);
		bool search(void*);
		void print_in_order();
		void print_pre_order();
		void print_post_order();
		void print_reverse_order();
		bool _insert_recursive(BinaryTreeNode*, void*);
		bool _search_recursive(BinaryTreeNode*, void*);
		void _in_order_recursive(BinaryTreeNode*);
		void _pre_order_recursive(BinaryTreeNode*);
		void _post_order_recursive(BinaryTreeNode*);
		void _reverse_order_recursive(BinaryTreeNode*);
		void print_depth_first();
		void print_breadth_first();
		bool insert_replace(void*);
		bool _insert_replace_recursive(BinaryTreeNode*, void*);
};

#endif
