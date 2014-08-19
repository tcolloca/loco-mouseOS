#include "../include/buffer.h"
#include "../include/defs.h"

/**
* head & tail are mem. positions. 
* The elements in the buffer are scancodes.
*/

struct bufferCDT {
	char * mem_start;
	int size, head, tail;
};

static struct bufferCDT buffers[BUFFER_CANT];
static int buffers_used = 0;

bufferADT buffer_init(char * mem_start, int size) {
	buffers[buffers_used].mem_start = mem_start;
	buffers[buffers_used].size = size;
	buffers[buffers_used].head = 0;
	buffers[buffers_used].tail = 0;
	
	buffers_used++;
	
	return (bufferADT)( &(buffers[buffers_used-1]) );
}

void buffer_clean(bufferADT buffer) {
	buffer->tail = buffer->head;
}

void buffer_add(bufferADT buffer, char c) {
	if(buffer_is_full(buffer)) {
		buffer_consume(buffer);
	}
	
	buffer->mem_start[buffer->head] = c;
	buffer->head = buffer_next_index(buffer, buffer->head);
}

int buffer_is_empty(bufferADT buffer) {
	return buffer->head == buffer->tail;
}

int buffer_is_full(bufferADT buffer) {
	return buffer_next_index(buffer, buffer->head) == buffer->tail;
}

char buffer_consume(bufferADT buffer) {
	if(buffer_is_empty(buffer)) {
		return EMPTY;
	}
	
	char ans = buffer->mem_start[buffer->tail];
	buffer->tail = buffer_next_index(buffer, buffer->tail);
	return ans;
}

void buffer_back(bufferADT buffer) {
	if(!buffer_is_empty(buffer)) {
		buffer->head = buffer_previous_index(buffer, buffer->head);
	}
}

int buffer_size(bufferADT buffer) {
	if(buffer_is_empty(buffer))
		return 0;
	if(buffer->tail < buffer->head)
		return (buffer->head - buffer->tail);
	return buffer->size - (buffer->tail - buffer->head);
}

static int buffer_next_index(bufferADT buffer, int dir) {
	return (dir + 1)%(buffer->size);
}

static int buffer_previous_index(bufferADT buffer, int dir) {
	if(dir == 0) {
		return buffer->size - 1;
	}
	return dir - 1;
}
