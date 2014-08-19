#include "../include/button.h"
#include "../include/string.h"
#include "../include/defs.h"
#include "../include/lomog.h"

void button_init(tButton * button, int width, int height, int x, int y, unsigned int format_normal, unsigned int format_over, char * text) {	
	panel_init(&(button->panel), width, height, x, y, format_normal);
	button->format_normal = format_normal;
	button->format_over = format_over;
	button->text = text;
	if(text != NULL) {
		button->blank = ( width - strlen(text) )/2;
		button->mid = ( height )/2;
	}
	
	mouse_listener_add(ENTER, video_button_enter, &(button->panel.listener));
	mouse_listener_add(OUT, video_button_out, &(button->panel.listener));
}

void video_button_enter(tMouseEvent * me) {
	tButton * button = (tButton *)(me->mystery);
	button->panel.format = button->format_over;
	lomog_update();
}

void video_button_out(tMouseEvent * me) {
	tButton * button = (tButton *)(me->mystery);
	button->panel.format = button->format_normal;
	lomog_update();
}
