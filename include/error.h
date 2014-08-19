#ifndef _error_
#define _error_

#define NO_ERROR 			-1
#define INVALID_COMMAND		0
#define INVALID_ENTRY 		1
#define MATH_ERROR 			2
#define INVALID_FD		 	3
#define LACK_OF_SPACE	 	4

void error_reset();

/**
* Sets and displays the error.
* @param error	resulting error.
* @param ref	reference where the error occurred.
*/

void error_set(int error, char * ref);

int error_found();

static void error_display();

#endif
