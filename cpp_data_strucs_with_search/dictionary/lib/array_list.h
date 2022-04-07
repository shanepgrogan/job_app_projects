// array_list.h
#ifndef __ARRAY_LIST_HEADER
#define __ARRAY_LIST_HEADER

// typedef struct _AList{
// 	void** arr;
// 	int size;
// 	int maxSize;
// 	int itemSize;
// 	char* type;
// } ArrayList;

class ArrayList{

	private:
		void** arr;
		int size;
		int maxSize;
		int itemSize;
		char* type;
	
	public:
		ArrayList();
		ArrayList(int, int, char*);
		ArrayList(const ArrayList&);
		bool add(void*);
		bool add_at(int, void*);
		void clear();
		void* const get(int);
		int const index_of(void*);
		void* remove(int);
		~ArrayList();
		bool resize();

};

// ArrayList* alist_initialize(int, int, char*);
// bool alist_add(ArrayList*, void*);
// bool alist_add_at(ArrayList*, int, void*);
// void alist_clear(ArrayList*);
// void* alist_get(ArrayList*, int);
// int alist_index_of(ArrayList*, void*);
// void* alist_remove(ArrayList*, int);
// bool alist_destroy(ArrayList*);
// bool _alist_resize(ArrayList*);

#endif
