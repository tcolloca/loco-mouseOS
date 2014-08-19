#ifndef _defs_
#define _defs_

#define byte 		unsigned char
#define word 		short int
#define dword 		int

#define NULL 		0

#define STDIN		0
#define STDOUT		1
#define STDERR		2

#define FALSE		0
#define TRUE		1

#define OFF			0
#define ON			1

#define GET			0
#define SET			1

#define INVALID 	-1

#define SMALL		1
#define BIG			2

#define TICK_FREQ 	55

#define MAX_LENGTH	32

/* New types */

typedef int size_t;
typedef short int ssize_t;

/* Frequently used structures */

typedef struct {
	int args_amount;
	char (*args)[MAX_LENGTH]; //Axiom. Don't ask why it's declared this way.
}tParams;

#endif

