#include "../include/io.h"
#include "../include/defs.h"
#include "../include/video.h"

int io_read(int fd, char * buff, size_t count) {
	int ans = -1;
	
	switch(fd) {
		case STDOUT:
		case STDERR:
			ans = 0;
			break;
		case STDIN:
			ans = terminal_read(buff, count);
			break;
	}
	
	return ans;	
}

int io_write(int fd, char * buff, size_t count) {
	int ans = -1;
	
	switch(fd) {
		case STDOUT:
		case STDERR:
			ans = terminal_write(buff, count);
			break;
		case STDIN:
			ans = terminal_buffer_write(buff, count);
			break;			
	}
	
	return ans;
}

