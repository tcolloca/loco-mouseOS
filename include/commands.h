#ifndef _commands_
#define _commands_

#include "defs.h"

#define NOTHING			-1
#define NL_PROMPT		0
#define NL				1
#define PROMPT			2

typedef int (*tFunction)(tParams * params);

typedef struct {
	char * name;
	tFunction function;
}tCommand;

/**
* @return	Return value of the command executed. if no command was executed, returns 0.
*/

int run_command(tParams * params);

int is_command(char * string);

static void empty_buffer();

#endif
