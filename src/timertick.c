#include "../include/timertick.h"
#include "../include/defs.h"
#include "../include/math.h"

static int ticks = 0;
static int tick_period;

void timertick_handler() {
	ticks++;
	timertick_event_shoot();
}

void timertick_init() {
	timertick_set_period(DEF_PERIOD);
} 

int timertick_period(int action, int period) {
	switch(action) {
		case GET:
			return timertick_get_period();
		case SET:
			return timertick_set_period(period);
		default:
			return 1;
	}
}

static int timertick_set_period(int period) {
	if( period < 0 )
		return INVALID;
	
	if( period < 1 ) {
		tick_period = 1;
		timertick_change_freq(tick_period);
		return SMALL;
	}
	
	if( round(CLOCK_FREQ*period/1000) > 65535 ) {
		tick_period = 55;
		timertick_change_freq(0);
		return BIG;
	}
	tick_period = period;
	timertick_change_freq(tick_period);
	return 0;
}

static int timertick_get_period() {
	return tick_period;
}

static void timertick_change_freq(int period) {
	unsigned int div;
	
	_cli();

	div = round(CLOCK_FREQ * period /1000);
 	_outb(CONFIG_PORT, 0x36); // 00|11|011|0 -> 0 Binary Mode, 011 -> Sqr Wave, 	
	_outb(CH0_PORT, (unsigned char) div);             //11 -> Access Mode low/hi bytes, 00 -> Ch 0
 	_outb(CH0_PORT, (unsigned char) (div >> 8));

	_sti();	
}

unsigned int timertick_get_millis() {
	return ticks*((unsigned int)tick_period);
}

