// A5.h

#ifndef A5_HEADER__
#define A5_HEADER__

typedef struct{
	int num;
} parameters;

void *producer(void*);
void *consumer(void*);
void insert_item(int);
void remove_item(int);

#endif
