#ifndef _timertick_event_
#define _timertick_event_

#include "timertick_listener.h"

#define TT_MAX_LISTENERS	32

void timertick_event_shoot();

int timertick_event_add(tTimertickListener * ttl);

#endif
