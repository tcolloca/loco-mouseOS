#ifndef _button_
#define _button_

#include "../include/panel.h"

typedef struct {
	char * text;
	tPanel panel;
	unsigned int format_over;
	unsigned int format_normal;
	int blank;
	int mid;
}tButton;

void button_init(tButton * button, int rows, int cols, int i, int j, unsigned int format_normal, unsigned int format_over, char * text);

void video_button_enter(tMouseEvent * me);

void video_button_out(tMouseEvent * me);

#endif
