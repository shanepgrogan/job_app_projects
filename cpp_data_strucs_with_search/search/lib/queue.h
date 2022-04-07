// queue.h
#ifndef __QUEUE_HEADER
#define __QUEUE_HEADER

typedef struct _Queue{
	// Fields: any you'd like
	// Functionality: whatever you deem necessary
	LinkedList* arr;	
} Queue;

Queue* queue_initialize(int, char*);
bool queue_enqueue(Queue*, void*);
void* queue_dequeue(Queue*);
void* queue_peek(Queue*);
int queue_size(Queue*);
bool queue_contains(Queue*, void*);
bool queue_destroy(Queue*);

#endif
