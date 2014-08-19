#ifndef _timertick_listener_
#define _timertick_listener_

typedef void (*tt_event_handler)();

typedef struct {
	int active;
	tt_event_handler handler;
}tTimertickListener;

void timertick_listener_init(tTimertickListener * ttl, tt_event_handler tt_handler);

void timertick_listener_enable(tTimertickListener * ttl);

void timertick_listener_disable(tTimertickListener * ttl);

void timertick_listener_change_handler(tTimertickListener * ttl, tt_event_handler tt_handler);

#endif
