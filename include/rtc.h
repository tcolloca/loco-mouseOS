#ifndef _rtc_
#define _rtc_

#define REGIS_PORT	0x70
#define DATA_PORT	0x71

#define REGIS_A		0x0A
#define REGIS_B 	0x0B

#define UPDATE_F	0x80

int rtc_time(unsigned int regis_id, int * data, int op);

static int rtc_get(int regis_id);

static void rtc_set(int regis_id, int value);

static void	rtc_wait();

#endif
