#ifndef _savescreen_
#define _savescreen_

typedef void (*tScreensaver)(void);

/**
* @params time	time in seconds.
*/

void savescreen_set_time(int time);

void savescreen_set_color(unsigned int c);

int savescreen_get_time();

unsigned int savescreen_get_color();

static void savescreen_timer();

static int savescreen_should_sleep();

void savescreen_reset_timer();

/**
* @params time	time in seconds.
*/

void savescreen_init(tScreensaver scsvr, int time, unsigned int color);

#endif
