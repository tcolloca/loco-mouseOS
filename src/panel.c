#include "../include/panel.h"

void panel_init(tPanel * panel, int width, int height, int x, int y, unsigned int format) {
	panel->present = 0;
	panel->rows = height;
	panel->columns = width;
	panel->i = y;
	panel->j = x;
	panel->cursor_i = 0;
	panel->cursor_j = 0;
	panel->format = format;
	panel->mouse_inside = 0;
	
	mouse_listener_init(&(panel->listener));
}
