#ifndef ALLOC
#define ALLOC


#include <stdio.h>


typedef struct meta{
	size_t size;
	int isFree;
	struct meta *next;
} Meta;

#define META_SIZE sizeof(Meta)


void *alloc(size_t);
void freeBlock(void *);
void *reallocate(void *, size_t);

#endif
