#include "alloc.h"
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

void *head = NULL;

void *findFreeBlock(Meta **block, size_t size) {
	Meta *curr = head;
	while(curr && !(curr->isFree && curr->size >= size)) {
		*block = curr;
		curr = curr->next;
	}
	return curr;
}

void *allocSpace(Meta *last, size_t size) {
	Meta *block;
	block = sbrk(0);
	void *req = sbrk(size+META_SIZE);
	assert((void *)block == req);	
	if((void *)block == (void *)-1) {
		return NULL;
	}
	if(last) {
		last->next = block;
	}
	block->isFree = 0;
	block->next = NULL;
	block->size = size;
	return (void *)block;
}


void *alloc(size_t size) {
	Meta *block = NULL;
	if(size <= 0) {
		return NULL;
	}
	
	if(!head) {
		block = allocSpace(NULL, size);
		if(!block) {
			return NULL;
		}
		head = block;
	} else {
		Meta *last = head;
		block = findFreeBlock(&last, size);
		if(!block) {
			block = allocSpace(last, size);
			if(!block) {
				return NULL;
			}
		} else {
			block->isFree = 0;
		}
	}
	return (block+1);
}


Meta *getMetaInfo(void *ptr) {
	return ((Meta *)ptr-1);
}


void freeBlock(void *ptr) {	
	if(!ptr) {
		return;
	}
	Meta *block = getMetaInfo(ptr);
	assert(block->isFree == 0);
	block->isFree = 1;
}

void *reallocate(void *ptr, size_t size) {
	if(!ptr) {
		return alloc(size);
	}
	Meta *block = getMetaInfo(ptr);
	if(block->size >= size) {
		return ptr;
	}

	void *newPtr;
	newPtr = alloc(size);	
	if(!newPtr) {
		return NULL;
	}
	memcpy(newPtr, ptr, block->size);
	return newPtr;
}
