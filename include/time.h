#ifndef _time_
#define _time_

#define	IS_SECOND(x)	( 0 <= (x) && (x) <= 59 )
#define IS_MINUTE(x)	IS_SECOND(x)
#define IS_HOUR(x)	( 0 <= (x) && (x) <= 23 )

#define IS_LEAP(x)	( ((x) % 4 == 0) && ( ((x) % 100 != 0) || ((x) % 400 == 0) ) )


/**
*	@return	time in seconds since epoch(1/1/1970).
*/

unsigned int 	time();

int 			time_get_seconds();

int 			time_get_minutes();

int 			time_get_hours();

char *			time_get_day();

int 			time_get_day_num();

int 			time_get_month();

int 			time_get_year();

int 			time_get_century();

void			time_set_time(int secs, int mins, int hours);

void			time_set_date(int day, int day_num, int month, int year, int century);

void 			time_set_alarm(int secs, int mins, int hours);

unsigned int 	time_current_millis();

int 			time_rtc(unsigned int regis_id, int * data, int op);

static void 	time_set(unsigned int regis_id, int data);

static int 		time_get(unsigned int regis_id);

static int 		leap_years(unsigned int year_i, unsigned int year_f);

#endif
