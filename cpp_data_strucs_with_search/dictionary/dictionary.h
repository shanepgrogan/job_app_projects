// dictionary.h
#ifndef __DICTIONARY_HEADER
#define __DICTIONARY_HEADER

typedef struct _Pair {
	void* first;
	void* second;
} Pair;

class Dictionary {
	
	private:
		BinaryTree* tree;

	public:
		Dictionary(){};
		Dictionary(int (*)(void*, void*), void (*)(void*));
		Dictionary(const Dictionary&){};
		bool insert(void*, void*);
		void* _get_recursive(BinaryTreeNode*, void*);
		void* get(void*);
		void _key_list_recursive(ArrayList*, BinaryTree*, BinaryTreeNode*);
		ArrayList* key_list(int);
		bool contains(void*);

};

#endif
