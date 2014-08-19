#ifndef _keyboard_event_
#define _keyboard_event_

#define K_MAX_LISTENERS	16

#define K_HANDLERS	2

#define K_PRESSED		0
#define K_RELEASED	1

typedef struct {
	char key;
	int additional_data[4];
	void * mystery;
}tKeyboardEvent;

typedef void (*keyboard_event_handler)(tKeyboardEvent * ke);

typedef struct {
	int active;
	keyboard_event_handler handlers[K_HANDLERS];
}tKeyboardListener;

void keyboard_event_add(tKeyboardListener * kl);

void keyboard_event_shoot(int type, tKeyboardEvent * ke);

#endif
