#ifndef _io_
#define _io_

#include "defs.h"

#define STDIN_FILENO	0
#define STDOUT_FILENO	1
#define STDERR_FILENO	2

/**
* @param fd 	file descriptor of file to be read.
* @param buff	buffer where content read must be written to. 	
* @param count	max size to be read.
* @return		size of buffer read. -1 in case of error (such as file descriptor unknown).
*/

int io_read(int fd, char * buff, size_t count);

/**
* @param fd 	file descriptor of file to be written.
* @param buff	buffer where content written must be read from. 	
* @param count	max size to be written.
* @return		size of buffer written. -1 in case of error (such as file descriptor unknown).
*/

int io_write(int fd, char * buff, size_t count);

#endif
