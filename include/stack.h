#ifndef _stack_
#define _stack_

#define STACK_SIZE 64

#define INVALID_STATE -1

#define CHAR 0
#define INT 1

int stack_is_empty(int type);

int stack_is_full(int type);

void stack_push(char c);

/**
* @return INVALID if empty.
*/

char stack_pop();

/**
* @return INVALID if empty.
*/

char stack_peek();

void stack_clean(int type);

/**
* @return INVALID if empty.
*/

int stack_pop_int();

/**
* @return INVALID if empty.
*/

int stack_peek_int();

void stack_push_int(int i);

#endif
