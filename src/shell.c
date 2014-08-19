#include "../include/shell.h"
#include "../include/stdio.h"
#include "../include/parser.h"
#include "../include/commands.h"

void shell_run() {
	
	char buffer[SHELL_BUFFER_SIZE];
	char * input;	
	tParams * params;	
	int total_read;
	int ret;
	tParams * cmd;
	/* Prompt */
	
	char * prompt = ">:";
	
	buffer[SHELL_BUFFER_SIZE-1] = '\n';	
	
	/* Welcome message */
	
	printf("Welcome. Type help to display available commands.\n");
	
	while(1) {
		
		printf(" %s ", prompt);
		
		total_read = read(STDIN, buffer, SHELL_BUFFER_SIZE-1); //TODO: Remove return?
		input = trim((char *)buffer); //TODO: Removable, already done by parser?
		cmd = parser_parse(input);
		if(input[0] != '\n') {
			ret = shell_do_command(cmd);
			shell_handle_ret(cmd->args[0], ret);
		}
	}	
	
}

static void shell_handle_ret(char * cmd, int ret) {
	
	if( !strcmp(cmd, "menu") ) {
		switch(ret) {
			case 1:
				shell_do_command(parser_parse("help\n"));
				break;
			case 2:
				shell_do_command(parser_parse("fortune\n"));
				break;
			case 3:
				shell_do_command(parser_parse("date\n"));
				break;
			case 4:
				shell_do_command(parser_parse("gettime\n"));
				break;
			case 5:
				shell_do_command(parser_parse("dharma\n"));
				break;
			case 6:
				shell_do_command(parser_parse("man help\n"));
				break;
			case 7:
				shell_do_command(parser_parse("man man\n"));
				break;
			case 8:
				shell_do_command(parser_parse("man t_color\n"));
				break;
			case 9:
				shell_do_command(parser_parse("man b_color\n"));
				break;
			case 10:
				shell_do_command(parser_parse("man gettime\n"));
				break;
			case 11:
				shell_do_command(parser_parse("man settime\n"));
				break;
			case 12:
				shell_do_command(parser_parse("man date\n"));
				break;
			case 13:
				shell_do_command(parser_parse("man svscr\n"));
				break;
			case 14:
				shell_do_command(parser_parse("man clear\n"));
				break;
			case 15:
				shell_do_command(parser_parse("man dharma\n"));
				break;
		}
	}
}

static int shell_do_command(tParams * params) {
	
	return run_command(params);
}

static char * trim(char * buff) { //TODO: Removable, already done by parser?
	int i = 0;
	while( buff[i++] == ' ' );
	return (char *)(buff + i - 1);
}

