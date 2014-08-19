#include "../include/mouse_listener.h"
#include "../include/mouse_event.h"
#include "../include/defs.h"
#include "../include/error.h"

void mouse_listener_init(tMouseListener * ml) {
	
	if( ml == NULL ) {
		error_set(INVALID_ENTRY, "mouse_listener_init");
	}
	
	ml->active = 1;
	
	int i;
	for(i = 0; i < HANDLERS; i++) {
		ml->handlers[i] = NULL;
	}
}

void mouse_listener_enable(tMouseListener * ml) {

	if( ml == NULL ) {
		error_set(INVALID_ENTRY, "mouse_listener_enable");
	}

	ml->active = 1;
}

void mouse_listener_disable(tMouseListener * ml) {

	if( ml == NULL ) {
		error_set(INVALID_ENTRY, "mouse_listener_disable");
	}

	ml->active = 0;
}

void mouse_listener_add(int event, mouse_event_handler handler, tMouseListener * ml) {
	
	if( ml == NULL ) {
		error_set(INVALID_ENTRY, "mouse_listener_add");
	}
	
	if(event < 0 || event >= HANDLERS) {
		error_set(INVALID_ENTRY, "mouse_listener_add");
	}
	
	if(handler == NULL) {
		error_set(INVALID_ENTRY, "mouse_listener_add");
	}
	
	ml->handlers[event] = handler;
}
