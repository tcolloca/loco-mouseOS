#include "../../include/defs.h"
#include "../../include/error.h"
#include "../../include/ascii.h"

int exec_t_color(tParams * params) {
	if(params->args_amount != 2) {
		error_set(INVALID_ENTRY, (params->args)[0]);
		return 1;
	}
	
	if( strcmp( (params->args)[1], "blue" ) == 0 ) {
		printf("%c", ASCII_T_COLOR_BLUE);
	} else if( strcmp( (params->args)[1], "red" ) == 0 ) {
		printf("%c", ASCII_T_COLOR_RED);
	} else if( strcmp( (params->args)[1], "green" ) == 0 ) {
		printf("%c", ASCII_T_COLOR_GREEN);
	} else if( strcmp( (params->args)[1], "orange" ) == 0 ) {
		printf("%c", ASCII_T_COLOR_ORANGE);
	} else if( strcmp( (params->args)[1], "violet" ) == 0 ) {
		printf("%c", ASCII_T_COLOR_VIOLET);
	} else if( strcmp( (params->args)[1], "light_blue" ) == 0 ) {
		printf("%c", ASCII_T_COLOR_LIGHT_BLUE);
	} else if( strcmp( (params->args)[1], "white" )  == 0) {
		printf("%c", ASCII_T_COLOR_WHITE);
	} else if( strcmp( (params->args)[1], "black" ) == 0 ) {
		printf("%c", ASCII_T_COLOR_BLACK);
	} else {
		error_set(INVALID_ENTRY, (params->args)[0]);
		return;
	}
	
	return 0;
}
