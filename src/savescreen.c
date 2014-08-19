#include "../include/savescreen.h"
#include "../include/timertick_listener.h"
#include "../include/kasm.h"

static int sleep_time;
static unsigned int color;
static tScreensaver screensaver;
static tTimertickListener ttListener;
static int initTime;
static int asleep;

void savescreen_set_time(int time) {
	sleep_time = time;
}

void savescreen_set_color(unsigned int c) {
	color = c;
}

int savescreen_get_time() {
	return sleep_time;
}

unsigned int savescreen_get_color() {
	return color;
}

static void savescreen_timer() { 
	if( savescreen_should_sleep() ) {
		screensaver();
		asleep = 1;
	}
}

static int savescreen_should_sleep() {
	return ((time_current_millis() - initTime)/1000) >= sleep_time && !asleep;
}

void savescreen_reset_timer() {
	initTime = time_current_millis();
	asleep = 0;
	_sti();
}

void savescreen_init(tScreensaver scsvr, int time, unsigned int c) {
	screensaver = scsvr;
	sleep_time = time;
	color = c;
	timertick_listener_init(&ttListener, savescreen_timer);
	timertick_event_add(&ttListener);	
	asleep = 0;
	savescreen_reset_timer();
}
