#ifndef _lomog_
#define _lomog_

#include "../include/button.h"
#include "../include/panel.h"

#define LOMOG_INIT	0
#define LOMOG_END	1
#define LOMOG_UPDATE	2
#define LOMOG_ADD_P	3
#define LOMOG_ADD_B	4
#define LOMOG_DRAW_S	5

typedef struct {
	int x, y;
}tPoint;

typedef struct {
	char * text;
	tButton button;
}tString;

int lomog_get_width();

int lomog_get_height();

void lomog_init();

void lomog_draw_string(tString * string, int x, int y, unsigned int format);

void lomog_add_button(tButton * button);

void lomog_add_button_st(tButton * button, int x, int y);

void lomog_add_panel(tPanel * panel);

void lomog_update();

void lomog_end();

int lomog_request(int operation, void * component, void * component2);

#endif
