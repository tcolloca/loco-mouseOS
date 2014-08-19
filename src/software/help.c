#include "../../include/defs.h"
#include "../../include/error.h"

int exec_help(tParams * params) {

	if(params->args_amount != 1) {
		error_set(INVALID_ENTRY, (params->args)[0]);
		return 1;
	}
	
	printf("COMMANDS:\n");

	printf("-\thelp\n");
	printf("-\tman\t[COMMAND]\n");
	printf("-\tclear\n");
	printf("-\tmenu\n");
	printf("-\tdate\n");
	printf("-\tt_color\t[COLOR]\n");
	printf("-\tb_color\t[COLOR]\n");
	printf("-\tgettime\n");
	printf("-\tsettime\t[HOUR] [MINUTES] [SECONDS]\n");
	printf("-\tsvscr\t[-SETTING] [VALUE]\n");
	printf("-\tfortune\n");
	printf("-\tdharma\n");
		
	return 0;
}
