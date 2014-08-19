#include "../include/stack.h"
#include "../include/defs.h"

static char stack[STACK_SIZE];
static int int_stack[STACK_SIZE];
static int index = 0;
static int int_index = 0;

int stack_is_empty(int type) {
	if(type == CHAR)
		return index == 0;
	return int_index == 0;
}

int stack_is_full(int type) {
	if(type == CHAR)
		return index >= STACK_SIZE;
	return int_index >= STACK_SIZE;
}

void stack_push(char c) {
	if(stack_is_full(CHAR)) {
		return;
	}
	
	stack[index] = c;
	index++;
}

void stack_push_int(int i) {
	if(stack_is_full(INT)) {
		return;
	}
	
	int_stack[int_index] = i;
	int_index++;
}

char stack_pop() {
	if(stack_is_empty(CHAR)) {
		return INVALID;
	}
	
	index--;
	return stack[index];
}

int stack_pop_int() {
	if(stack_is_empty(INT)) {
		return INVALID;
	}
	
	int_index--;
	return int_stack[int_index];
}

char stack_peek() {
	if(stack_is_empty(CHAR)) {
		return INVALID;
	}
	
	return stack[index];
}

int stack_peek_int() {
	if(stack_is_empty(INT)) {
		return INVALID;
	}
	
	return int_stack[int_index];
}

void stack_clean(int type) {
	if(type == CHAR) {
		index = 0;
		return;
	}
	
	int_index = 0;
}
