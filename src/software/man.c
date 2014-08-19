#include "../../include/defs.h"
#include "../../include/error.h"

typedef struct {
	char * name;
	char * description;
}tDescription;


static char help_desc[] = ""
"\nNAME \n"
"\thelp - States all the available commands with their respective synopsis.\n\n"
"SYNOPSIS \n"
"\tnone\n";
static char man_desc[] = ""
"\nNAME \n"
"\tman - Describes and explains how should be used the selected command.\n\n"
"SYNOPSIS \n"
"\tman [COMMAND]\n";
static char clear_desc[] = ""
"\nNAME \n"
"\tclear - Clears the screen.\n\n"
"SYNOPSIS \n"
"\tnone\n";
static char t_color_desc[] = ""
"\nNAME \n"
"\tt_color - Allows setting the text color.\n\n"
"SYNOPSIS \n"
"\tt_color [COLOR]\n\n"
"AVAILABLE COLORS\n"
"-\twhite\n"
"-\tblack\n"
"-\tblue\n"
"-\tlight_blue\n"
"-\tred\n"
"-\tgreen\n"
"-\torange\n"
"-\tviolet\n";
static char b_color_desc[] = ""
"\nNAME\n"
"\tb_color - Allows setting the background color.\n\n"
"SYNOPSIS \n"
"\tb_color [COLOR]\n\n"
"AVAILABLE COLORS\n"
"-\twhite\n"
"-\tblack\n"
"-\tblue\n"
"-\tlight_blue\n"
"-\tred\n"
"-\tgreen\n"
"-\torange\n"
"-\tviolet\n";

static char gettime_desc[] = ""
"\nNAME \n"
"\tgettime - Displays the system's time.\n\n"
"SYNOPSIS \n"
"\treceives no arguments\n";

static char settime_desc[] = ""
"\nNAME \n"
"\tsettime - Allows setting the system's time.\n\n"
"SYNOPSIS \n"
"\tsettime [HOUR] [MINUTES] [SECONDS]\n";

static char svscr_desc[] = ""
"\nNAME \n"
"\tsvscr - Allows setting the elapsed time in seconds for the screensaver to be activated.\n\n"
"SYNOPSIS \n"
"\tsvscr [-SETTING] [VALUE]\n\n"
"AVAILABLE SETTINGS:\n"
"-\ttime [SECONDS]\n"
"-\tcolor [COLOR]\n\n"
"EXAMPLES \n"
"\tsvscr -time 30\n"
"\tsvscr -color blue\n";

static char nodesc_desc[] = ""
"\nno manual entry\n";

static char fortune_desc[] = ""
"\nNAME \n"
"\tfortune - Displays a fortune cookie quote.\n\n"
"SYNOPSIS \n"
"\tnone\n";

static char date_desc[] = ""
"\nNAME \n"
"\tdate - Displays the date.\n\n"
"SYNOPSIS \n"
"\tnone\n";

static char dharma_desc[] = ""
"\nNAME \n"
"\tdharma - Are you a fan of Lost? Be ready to live a life-changing experience by having to introduce the Lost’ numbers every 108 minutes to save the world.\n\n"
"SYNOPSIS \n"
"\tnone\n\n"
"AVAILABLE COMMANDS:\n"
"-\t4 8 15 16 23 42 - resets the 108 timer.\n"
"-\tspeedup - the required time for each alarm is faster.\n"
"-\tslowdown - the timer is set again in 108 minutes.\n"
"-\tquit\n";

static char menu_desc[] = ""
"\nNAME \n"
"\tmenu - Displays an interactive button based menu with all the available single-argument commands and the manual.\n\n"
"SYNOPSIS \n"
"\tnone\n";


static tDescription manual[] = { 
	{"help", help_desc},
	{"man", man_desc},
	{"clear", clear_desc},
	{"t_color", t_color_desc},
	{"b_color", b_color_desc},
	{"settime", settime_desc},
	{"gettime", gettime_desc},
	{"svscr", svscr_desc},
	{"fortune", fortune_desc},
	{"date", date_desc},
	{"dharma", dharma_desc},
	{"menu", menu_desc},
	{"", NULL}
};

static char * man_get_info(char * command) {
	int k;
	for(k = 0; manual[k].name[0] != 0; k++) {
		if( strcmp(command, manual[k].name) == 0 ) {
			return manual[k].description;
		}
	}
	
	return nodesc_desc;
}

int exec_man(tParams * params) {
	if(params->args_amount != 2) {
		error_set(INVALID_ENTRY, (params->args)[0]);
		return 1;
	}
	
	char * info = man_get_info((params->args)[1]);
	
	if(info == NULL) {
		error_set(INVALID_ENTRY, (params->args)[0]);
		return 2;
	}
	
	printf("%s\n", info);
	
	return 0;
}
