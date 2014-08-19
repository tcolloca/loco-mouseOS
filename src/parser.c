#include "../include/parser.h"
#include "../include/error.h"
#include "../include/defs.h"

static char args[MAX_ARGS][MAX_LENGTH];
static int args_amount;
static tParams params;

static void parser_generate_args(char * buff) {
	int state = SPACE_STATE;
	int c;
	char * aux = buff;
	int i = 0, j;
	args_amount = 0;
	
	while( (c = *aux) != '\n' ) {
		switch(state) {
			case SPACE_STATE:
				if(!IS_SPACE(c)) {
					j = 0;
					args[i][j++] = c;
					state = CHARACTER_STATE;
				}
				break;
			case CHARACTER_STATE:
				if(IS_SPACE(c)) {
					args[i++][j] = '\0'; //NULL-terminated Strings
					args_amount++;
					state = SPACE_STATE;
				} else {
					args[i][j++] = c;
				}
				break;
		}
		
		if(i >= MAX_ARGS) {
			if(is_command(args[0])) {
				error_set(INVALID_ENTRY, args[0]);
			} else {
				error_set(INVALID_COMMAND, args[0]);
			}
			return;
		} else if(j >= MAX_LENGTH) {
			if(is_command(args[0])) {
				error_set(INVALID_ENTRY, args[0]);
			} else {
				error_set(INVALID_COMMAND, args[0]);
			}
			return;
		}
		
		aux++;
	}
	
	
	if(state == CHARACTER_STATE) {
		args[i++][j] = '\0'; //NULL-terminated Strings
		args_amount++;
	}
	
	if(i >= MAX_ARGS) {
		if(is_command(args[0])) {
			error_set(INVALID_ENTRY, args[0]);
		} else {
			error_set(INVALID_COMMAND, args[0]);
		}
		return;
	}

	args[i][0] = NULL; //NULL-terminated args list.
}

tParams * parser_parse(char * buff) {
	error_reset();
	parser_generate_args(buff);
	if(!error_found()) {
		params.args_amount = args_amount;
		params.args = args;
		return &params;
	} else
		return NULL;
}






