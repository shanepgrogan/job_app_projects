// dictionary.h
#ifndef __DICTIONARY_HEADER
#define __DICTIONARY_HEADER

typedef struct _Pair {
	void* first;
	void* second;
} Pair;

typedef struct _Dictionary {
	BinaryTree* tree;
} Dictionary;

Dictionary* dict_initialize(int (*)(void*, void*), void (*)(void*));
bool dict_insert(Dictionary*, void*, void*);
void* dict_get(Dictionary*, void*);
ArrayList* dict_key_list(Dictionary*, int);
bool dict_contains(Dictionary*, void*);

#endif
