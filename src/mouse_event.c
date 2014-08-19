#include "../include/mouse_event.h"
#include "../include/mouse_listener.h"
#include "../include/defs.h"
#include "../include/error.h"

static int listeners_amount = 0;
static tMouseListener * listeners[MAX_LISTENERS];

void mouse_event_add(tMouseListener * ml) {
	if(listeners_amount >= MAX_LISTENERS) {
		error_set(LACK_OF_SPACE, "mouse_event_add");
	}
	
	if(ml == NULL ) {
		error_set(INVALID_ENTRY, "mouse_event_add");
	}
	
	listeners[listeners_amount++] = ml;
}

void mouse_event_shoot(int type, tMouseEvent * me) {
	int i;
	
	if( me == NULL )
		error_set(INVALID_ENTRY, "mouse_event_shoot");
	
	if( type < 0 || type >= HANDLERS )
		error_set(INVALID_ENTRY, "mouse_event_shoot");
	
	for(i = 0; i < listeners_amount; i++) {
		if( listeners[i]->active && listeners[i]->handlers[type] != NULL ) {
			listeners[i]->handlers[type](me);
		}
	}		
}
