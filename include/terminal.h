#ifndef _terminal_
#define _terminal_

#include "defs.h"
#include "keyboard_event.h"

#define KEYBOARD_BUFFER_SIZE 512

void terminal_init();

int terminal_read(char * buff, size_t count);

int terminal_write(char * buff, size_t count);

void terminal_video_handle(char c);

static void terminal_add(char ascii);

static void terminal_idle();

void terminal_char_handler(tKeyboardEvent * ke);

#endif
