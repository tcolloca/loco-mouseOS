#ifndef _timertick_
#define _timertick_

#define DEF_PERIOD	10
#define CLOCK_FREQ 	1193180 

#define CONFIG_PORT		0x43
#define CH0_PORT		0x40		

void int_08();

void timertick_init();

int timertick_period(int action, int period);

/**
* @params	period of each tick in milliseconds.
* @return	-1 if period is invalid. 1 if period is too low, 2 if it is too big, else 0.
*/

static int timertick_set_period(int period);

static int timertick_get_period();

static void timertick_change_freq(int period);

unsigned int timertick_get_millis();

#endif
