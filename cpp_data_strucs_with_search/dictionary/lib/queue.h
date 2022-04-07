// queue.h
#ifndef __QUEUE_HEADER
#define __QUEUE_HEADER

// typedef struct _Queue{
// 	// Fields: any you'd like
// 	// Functionality: whatever you deem necessary
// 	LinkedList* arr;	
// } Queue;
class Queue{
	private:
		LinkedList* arr;
	public:
		Queue();
		Queue(int, char*);
		Queue(const Queue&);
		bool enqueue(void*);
		void* dequeue();
		void* const peek();
		int const size();
		bool const contains(void*);
		virtual ~Queue();
};

#endif
