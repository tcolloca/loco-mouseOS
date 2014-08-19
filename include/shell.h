#ifndef _shell_
#define _shell_

#include "../include/defs.h"

#define SHELL_BUFFER_SIZE 512

void shell_run();

static int shell_do_command(tParams * params);

static char * trim(char * buffer);

static void shell_handle_ret(char * cmd, int ret);

#endif
