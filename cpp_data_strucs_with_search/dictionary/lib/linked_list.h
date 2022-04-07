// linked_list.h
#ifndef __LINKED_LIST_HEADER
#define __LINKED_LIST_HEADER

typedef struct _Node{
	void* data;
	struct _Node* next;
	struct _Node* prev;
} Node;

class LinkedList{
	private:
		Node* first;
		Node* last;
		int size;
		int itemSize;
		char* type;
	
	public:
		LinkedList();
		LinkedList(int, char*);
		LinkedList(const LinkedList&);
		bool add_at(int, void*);
		bool add_first(void*);
		bool add_last(void*);
		void* const get(int);
		int const index_of(void*);
		int get_size();
		void* remove(int);
		void* remove_first();
		void* remove_last();
		virtual ~LinkedList();

};

#endif