#include "../../include/stdio.h"
#include "../../include/defs.h"
#include "../../include/time.h"
#include "../../include/error.h"
#include "../../include/stdlib.h"

int exec_settime(tParams * params) {

	if(params->args_amount != 4) {
		error_set(INVALID_ENTRY, (params->args)[0]);
		return 1;
	}
	
	if(!is_num(params->args[1]) || !is_num(params->args[2]) || !is_num(params->args[3])) {
		error_set(INVALID_ENTRY, (params->args)[0]);
		return 1;
	}
	
	int h, m, s;
	
	h = atoi(params->args[1]);
	m = atoi(params->args[2]);
	s = atoi(params->args[3]);
	
	if(!IS_HOUR(h) || !IS_MINUTE(m) || !IS_SECOND(s)) {
		error_set(INVALID_ENTRY, (params->args)[0]);
		return 1;
	}
	
	time_set_time(s,m,h);
	
	return 0;
}
