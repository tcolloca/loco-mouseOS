#include "../../include/stdio.h"
#include "../../include/defs.h"
#include "../../include/time.h"
#include "../../include/error.h"

int exec_gettime(tParams * params) {
	int h, m, s;
	
	if(params->args_amount != 1) {
		error_set(INVALID_ENTRY, (params->args)[0]);
		return 1;
	}
	
	h = time_get_hours();
	m = time_get_minutes();
	s = time_get_seconds();
	
	printf("System's time:\t%d:%d:%d\n", h, m, s);
	
	return 0;
}
