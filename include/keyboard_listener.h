#ifndef _keyboard_listener_
#define _keyboard_listener_

#include "keyboard_event.h"

void keyboard_listener_init(tKeyboardListener * kl);

void keyboard_listener_enable(tKeyboardListener * kl);

void keyboard_listener_disable(tKeyboardListener * kl);

void keyboard_listener_add(int event, keyboard_event_handler handler, tKeyboardListener * kl);

#endif
