#ifndef _panel_
#define _panel_

#include "../include/mouse_listener.h"

#define BLACK (0x00)
#define BLUE (0x01)
#define GREEN (0x02)
#define LIGHT_BLUE (0x03)
#define RED (0x04)
#define VIOLET (0x05)
#define ORANGE (0x06)
//#define WHITE (0x07)
#define WHITE (0x0F)
#define GRAY (0x08)
#define SOFT_BLUE (0x09)
#define SOFT_GREEN (0x0A)
#define SOFT_LIGHT_BLUE (0x0B)
#define SOFT_RED (0x0C)
#define SOFT_VIOLET (0x0D)
#define SOFT_ORANGE (0x0E)

#define FORMAT(text, background)	( ( (background) << 4 ) | text ) //Gets the format according to the parameters
#define TEXT_COLOR(format)		( (format) & 0x0F )
#define BACKGROUND_COLOR(format)	( ((format) >> 4) & 0x0F )

typedef struct {
	int present;
	int rows, columns;
	int i, j;
	int cursor_i, cursor_j;
	unsigned int format;
	tMouseListener listener;
	int mouse_inside;
}tPanel;

void panel_init(tPanel * panel, int rows, int cols, int i, int j, unsigned int format);

#endif
