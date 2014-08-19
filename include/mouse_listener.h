#ifndef _mouse_listener_
#define _mouse_listener_

#include "mouse_event.h"

void mouse_listener_init(tMouseListener * ml);

void mouse_listener_enable(tMouseListener * ml);

void mouse_listener_disable(tMouseListener * ml);

void mouse_listener_add(int event, mouse_event_handler handler, tMouseListener * ml);

#endif
