#include "../../include/defs.h"
#include "../../include/string.h"
#include "../../include/stdlib.h"
#include "../../include/error.h"

static char * colors[] = {"black", "blue", "green", "light_blue", "red", "violet", "orange", "white", ""};

int exec_svscr(tParams * params) {
	
	if(params->args_amount != 3) {
		error_set(INVALID_ENTRY, (params->args)[0]);
		return 1;
	}
	
	char * com = params->args[1];
	char * val = params->args[2];
	if( !strcmp( com, "-time" ) ) {
		if( !is_num(val) ) {
			error_set(INVALID_ENTRY, (params->args)[0]);
			return 1;
		}
		
		int num = atoi(val);
		savescreen_set_time(num);
		
	} else if( !strcmp(com, "-color") ) {
	
		int i;
		int flag = 1;
		for(i = 0; colors[i][0] != 0 && flag; i++) {
			if ( !strcmp( val, colors[i] ) ) {
				savescreen_set_color(i);
				flag = 0;
			}
		}
		
		if(flag) {
			error_set(INVALID_ENTRY, (params->args)[0]);
			return 1;
		}
	
	} else {
		error_set(INVALID_ENTRY, (params->args)[0]);
		return 1;
	}
	
	return 0;
}
