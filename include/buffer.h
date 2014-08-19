#ifndef _buffer_
#define _buffer_

#define BUFFER_SIZE 	1024
#define BUFFER_CANT 	3
#define EMPTY 			-1

typedef struct bufferCDT * bufferADT;

/**
* @params mem_start initial position of the buffer. User must reserve from that space size bytes.
* @params size		size of the buffer.
*/

bufferADT buffer_init(char * mem_start, int size);

void buffer_clean(bufferADT buffer);

void buffer_add(bufferADT buffer, char c);

int buffer_is_empty(bufferADT buffer);

int buffer_is_full(bufferADT buffer);

char buffer_consume(bufferADT buffer);

void buffer_back(bufferADT buffer);

int buffer_size(bufferADT buffer);

static int buffer_next_index(bufferADT buffer, int dir);

static int buffer_previous_index(bufferADT buffer, int dir);

#endif
