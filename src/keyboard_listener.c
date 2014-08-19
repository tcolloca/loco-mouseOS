#include "../include/keyboard_listener.h"
#include "../include/keyboard_event.h"
#include "../include/defs.h"
#include "../include/error.h"

void keyboard_listener_init(tKeyboardListener * ml) {
	
	if( ml == NULL ) {
		error_set(INVALID_ENTRY, "keyboard_listener_init");
	}
	
	ml->active = 1;
	
	int i;
	for(i = 0; i < K_HANDLERS; i++) {
		ml->handlers[i] = NULL;
	}
}

void keyboard_listener_enable(tKeyboardListener * ml) {

	if( ml == NULL ) {
		error_set(INVALID_ENTRY, "keyboard_listener_enable");
	}

	ml->active = 1;
}

void keyboard_listener_disable(tKeyboardListener * ml) {

	if( ml == NULL ) {
		error_set(INVALID_ENTRY, "keyboard_listener_disable");
	}

	ml->active = 0;
}

void keyboard_listener_add(int event, keyboard_event_handler handler, tKeyboardListener * ml) {
	
	if( ml == NULL ) {
		error_set(INVALID_ENTRY, "keyboard_listener_add");
	}
	
	if(event < 0 || event >= K_HANDLERS) {
		error_set(INVALID_ENTRY, "keyboard_listener_add");
	}
	
	if(handler == NULL) {
		error_set(INVALID_ENTRY, "keyboard_listener_add");
	}
	
	ml->handlers[event] = handler;
}
