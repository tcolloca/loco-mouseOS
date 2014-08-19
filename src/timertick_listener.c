#include "../include/timertick_listener.h"
#include "../include/defs.h"

void timertick_listener_init(tTimertickListener * ttl, tt_event_handler tt_handler) {
	ttl->active = 1;
	ttl->handler = tt_handler;
}

void timertick_listener_enable(tTimertickListener * ttl) {
	ttl->active = 1;
}

void timertick_listener_disable(tTimertickListener * ttl) {
	ttl->active = 0;
}

void timertick_listener_change_handler(tTimertickListener * ttl, tt_event_handler tt_handler) {
	ttl->handler = tt_handler;
}

