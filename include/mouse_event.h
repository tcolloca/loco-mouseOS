#ifndef _mouse_event_
#define _mouse_event_

#define MAX_LISTENERS	32

#define HANDLERS	10

#define MOVE		0
#define	DRAG		1
#define ENTER		2
#define OUT		3
#define L_CLICK		4
#define	L_RELEASE	5
#define	R_CLICK		6
#define R_RELEASE	7
#define M_CLICK		8
#define M_RELEASE	9

typedef struct {
	int mouse_x;
	int mouse_y;
	int additional_data[4];
	void * mystery; // TODO: What's mystery?
}tMouseEvent;

typedef void (*mouse_event_handler)(tMouseEvent * me);

typedef struct {
	int active;
	mouse_event_handler handlers[HANDLERS];
}tMouseListener;

void mouse_event_add(tMouseListener * ml);

void mouse_event_shoot(int type, tMouseEvent * me);

#endif
