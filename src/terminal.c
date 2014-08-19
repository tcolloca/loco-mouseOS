#include "../include/terminal.h"
#include "../include/defs.h"
#include "../include/buffer.h"
#include "../include/ascii.h"
#include "../include/video.h"
#include "../include/keyboard_event.h"
#include "../include/keyboard_listener.h"

static bufferADT keyboard_buffer;
static char keyboard_buffer_space[KEYBOARD_BUFFER_SIZE];
static volatile int idle = 0;
static tKeyboardListener listener;

void terminal_init() {
	keyboard_buffer = buffer_init(keyboard_buffer_space, KEYBOARD_BUFFER_SIZE);
	keyboard_listener_init(&listener);
	keyboard_listener_add(K_PRESSED, terminal_char_handler, &listener);
	
	keyboard_event_add(&listener);
}

int terminal_read(char * buff, size_t count) {
	int c;
	int index = 0;

	while( index < count && (c = buffer_consume(keyboard_buffer)) != ASCII_ENTER) {
		switch(c) {
			case EMPTY:
				terminal_idle();
				break;
			default:
				buff[index++] = (unsigned char)c;
		}
		
	}
	
	if(c == ASCII_ENTER) {
		buff[index++] = '\n';
	}
	return index;
}

int terminal_write(char * buff, size_t count) {
	int i;
	for( i = 0; i < count; i++) {
		video_put_char_innocuous(buff[i]);
	}
	return i;
}

int terminal_buffer_write(char * buff, size_t count) {
	int i;
	for(i = 0; i < count; i++) {
		terminal_add(buff[i]);
	}
	return i;
}

void terminal_handle(char c) {
	
	switch(c) {
		case ASCII_BACKSPACE:
			video_backspace();
			buffer_back(keyboard_buffer);
			break;
		case ASCII_ENTER:
			video_new_line();
			idle = 0;
			break;
		case ASCII_SHIFT:
			return;
		default:
			video_put_char(c);
	}
}

void terminal_char_handler(tKeyboardEvent * ke) {
	if(ke->key != ASCII_BACKSPACE && ke->key != ASCII_SHIFT) {
		char c = ke->key;
		write(STDIN, &c, 1);
	}
	
	terminal_handle(ke->key);
}

static void terminal_add(char c) {
	buffer_add(keyboard_buffer, c);
}

static void terminal_idle() {
	idle = 1;
	while(idle);
}










