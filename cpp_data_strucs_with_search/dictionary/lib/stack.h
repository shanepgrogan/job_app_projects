// stack.h
#ifndef __STACK_HEADER
#define __STACK_HEADER

class Stack{
	private:
		LinkedList* arr;
	public:
		Stack();
		Stack(int, char*);
		Stack(const Stack&);
		bool push(void*);
		void* pop();
		void* peek();
		int size();
		bool contains(void*);
		virtual ~Stack();
};

#endif
