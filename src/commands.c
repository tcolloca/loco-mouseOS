#include "../include/commands.h"
#include "../include/error.h"
#include "../include/stdio.h"
#include "../include/string.h"
#include "../include/defs.h"

/* Available commands */

int exec_help(tParams * params);

int exec_man(tParams * params);

int exec_t_color(tParams * params);

int exec_b_color(tParams * params);

int exec_clear(tParams * params);

int exec_gettime(tParams * params);

int exec_settime(tParams * params);

int exec_svscr(tParams * params);

int exec_date(tParams * params);

int exec_dharma(tParams * params);

int exec_fortune(tParams * params);

int exec_menu(tParams * params);

static tCommand commands[] = {
	{"clear", exec_clear}, 
	{"help", exec_help},
	{"man", exec_man},
	{"b_color", exec_b_color},
	{"t_color", exec_t_color},
	{"gettime", exec_gettime},
	{"settime", exec_settime},
	{"svscr", exec_svscr},
	{"date", exec_date},
	{"menu", exec_menu},
	{"dharma", exec_dharma},
	{"fortune", exec_fortune},
	{"", NULL}
};
int run_command(tParams * params) {	
	if( params == NULL )
		return 0;

	int k;
	for(k = 0; commands[k].name[0] != 0; k++) {
		if(strcmp(commands[k].name, (params->args)[0]) == 0) {
			int ans = commands[k].function(params);
			empty_buffer();
			return ans;
		}
	}
	
	error_set(INVALID_COMMAND, (params->args)[0]);
	return 0;
}

static void empty_buffer() {
	char c = 127;
	write(STDIN, &c, 1);
	while( getchar() != 127 );
}

int is_command(char * string) {
	int k;
	for(k = 0; commands[k].name[0] != 0; k++) {
		if(strcmp(commands[k].name, string) == 0) {
			return TRUE;
		}
	}
	
	return FALSE;
}




