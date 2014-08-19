#include "../include/error.h"
#include "../include/stdio.h"

static int error = NO_ERROR;

static char * errors[] = {"command not found",
						  "invalid arguments",
						  "math error",
						  "invalid file descriptor",
						  "lack of space"};

static char * reference;

void error_reset() {
	error = NO_ERROR;
}

void error_set(int e, char * ref) {
	error = e;
	reference = ref;
	error_display();
}

int error_found() {
	return error != NO_ERROR;
}

static void error_display() {
	if(error == INVALID_COMMAND) {
		printf("%s\n", errors[error]);
		return;
	}
	printf("%s: %s\n", reference, errors[error]);
}

