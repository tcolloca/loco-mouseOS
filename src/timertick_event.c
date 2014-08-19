#include "../include/timertick_event.h"
#include "../include/timertick_listener.h"
#include "../include/time.h"
#include "../include/defs.h"

static int listeners_amount = 0;
static tTimertickListener * listeners[TT_MAX_LISTENERS];

int timertick_event_add(tTimertickListener * ttl) {
	if(listeners_amount >= TT_MAX_LISTENERS) {
		return -1;
	}
	
	if(ttl == NULL) {
		return -2;
	}
	
	listeners[listeners_amount++] = ttl;
	return 1;
}

void timertick_event_shoot() {

	int i;
	for(i = 0; i < listeners_amount; i++) {
		if( listeners[i]->active ) {
			listeners[i]->handler();
		}
	}	
	
}
