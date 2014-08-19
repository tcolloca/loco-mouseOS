#ifndef _parser_
#define _parser_

#include "defs.h"

#define SPACE_STATE 0
#define CHARACTER_STATE 1

#define MAX_ARGS 	8

#define IS_SPACE(x) ( (x) == ' ' )

/**
* Explodes a string using space(' ') as a delimiter.
* @return struct with the resulting substrings after the explosion.
*/

tParams * parser_parse(char * buffer);

static void parser_generate_args();

#endif
