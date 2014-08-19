#include "../include/keyboard_event.h"
#include "../include/keyboard_listener.h"
#include "../include/defs.h"
#include "../include/error.h"
#include "../include/kasm.h"

static int listeners_amount = 0;
static tKeyboardListener * listeners[K_MAX_LISTENERS];

void keyboard_event_add(tKeyboardListener * kl) {
	if(listeners_amount >= K_MAX_LISTENERS) {
		error_set(LACK_OF_SPACE, "keyboard_event_add");
	}
	
	if(kl == NULL ) {
		error_set(INVALID_ENTRY, "keyboard_event_add");
	}
	
	listeners[listeners_amount++] = kl;
}

void keyboard_event_shoot(int type, tKeyboardEvent * ke) {
	int i;
	
	if( ke == NULL )
		error_set(INVALID_ENTRY, "keyboard_event_shoot");
	
	if( type < 0 || type >= K_HANDLERS )
		error_set(INVALID_ENTRY, "keyboard_event_shoot");
	
	for(i = 0; i < listeners_amount; i++) {
		if( listeners[i]->active && listeners[i]->handlers[type] != NULL ) {
			listeners[i]->handlers[type](ke);
		}
	}	
}
