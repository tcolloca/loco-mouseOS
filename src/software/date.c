#include "../../include/defs.h"
#include "../../include/time.h"
#include "../../include/stdio.h"
#include "../../include/error.h"

int exec_date(tParams * params) {
	if(params->args_amount != 1) {
		error_set(INVALID_ENTRY, (params->args)[0]);
		return 1;
	}
	
	int d, m, y;
	
	d = time_get_day_num();
	m = time_get_month();
	y = time_get_year();
	
	printf("System's date: %d/%d/%d\n", d, m, 2000 + y);
	
	return 0;
}
