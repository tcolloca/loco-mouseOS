#include "../../include/defs.h"
#include "../../include/ascii.h"
#include "../../include/error.h"

int exec_clear(tParams * params) {
	if(params->args_amount != 1) {
		error_set(INVALID_ENTRY, (params->args)[0]);
		return 1;
	}

	printf("%c", ASCII_CLEAR);
	
	return 0;
}
