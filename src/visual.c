#include "../include/visual.h"
#include "../include/video.h"
#include "../include/lomog.h"
#include "../include/button.h"
#include "../include/panel.h"
#include "../include/defs.h"

static volatile int running;

void visual_init() {

	video_die();
	
	video_update();
	
	video_mouse_show();

	running = TRUE;
	while(running);
	
	video_live();
}

void visual_end() {
	running = FALSE;
}

void visual_update() {
	video_update();
}

void visual_add_panel(tPanel * panel) {
	video_add_panel(panel);
}

void visual_add_button(tButton * button) {
	video_add_button(button);
}

void visual_draw_string(char * string, tPoint * point) {
	video_move_to(point->y, point->x);
	video_write(string);
}

int visual_handle(int operation, void * component, void * component2) {

	int ans = -1;

	switch(operation) {
		case LOMOG_INIT:
			visual_init();
			ans = 0;
			break;
		
		case LOMOG_END:
			visual_end();
			ans = 0;
			break;	
		
		case LOMOG_UPDATE:
			visual_update();
			ans = 0;
			break;
		
		case LOMOG_ADD_P:
			visual_add_panel((tPanel *)component);
			ans = 0;
			break;
		
		case LOMOG_ADD_B:
			visual_add_button((tButton *)component);
			ans = 0;
			break;
		case LOMOG_DRAW_S:
			visual_draw_string((char *)component, (tPoint *)component2);
			ans = 0;
			break;
	}
	
	return ans;
}


