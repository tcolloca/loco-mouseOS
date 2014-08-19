#include "../include/time.h"
#include "../include/syscall.h"
#include "../include/defs.h"

static char* days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
static int prevDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

unsigned int time() {
	int i, y, m;
	unsigned int ans = 0;
	ans += time_get_year()*365;
	ans += 30*365;
	y = time_get_year() + 2000;
	ans += leap_years(1970, y);
	
	m = time_get_month();
	if(m >= 3 && IS_LEAP(y)) {
		ans++;
	}
	
	for(i = 0; i < m - 1; i++) {
		ans += prevDays[i];
	}
	
	ans += (time_get_day_num() - 1);
	ans *= 24*3600;
	
	ans += time_get_hours()*3600;
	ans += time_get_minutes()*60;
	ans += time_get_seconds();
	
	return ans;
}

static int leap_years(unsigned int year_i, unsigned int year_f) {

	int i, acum = 0;
	if(year_i > year_f) {
		return 0;
	}
	
	for(i = year_i; i < year_f; i++) {
		acum += IS_LEAP(i);
	}

	return acum;
}

int time_get_seconds() {
	return time_get(0x00);
}

int time_get_minutes() {
	return time_get(0x02);
}

int time_get_hours() {
	return time_get(0x04);
}

char * time_get_day() {
	return days[time_get(0x06)];
}

int time_get_day_num() {
	return time_get(0x07);
}

int time_get_month() {
	return time_get(0x08);
}

int time_get_year() {
	return time_get(0x09);
}

int time_get_century() {
	return time_get(0x32);
}

void time_set_time(int secs, int mins, int hour) {
	time_set(0, secs);
	time_set(2, mins);
	time_set(4, hour);
}

void time_set_date(int day, int day_num, int month, int year, int century) {
 	time_set(6, day);
	time_set(7, day_num);
	time_set(8, month);
	time_set(9, year);
	time_set(0x32, century);
}

void time_set_alarm(int secs, int mins, int hour) {
	time_set(1, secs);
	time_set(3, mins);
	time_set(5, hour);
}

static void time_set(unsigned int regis_id, int data) {
	time_rtc(regis_id, &data, SET);
}

static int time_get(unsigned int regis_id) {
	int data;
	time_rtc(regis_id, &data, GET);
	return data;
}

unsigned int time_current_millis() {
	return _syscall(MILITIME, 0, 0, 0);
}

int time_rtc(unsigned int regis_id, int * data, int op) {
	return _syscall(TIME, regis_id, (int)data, op);
}
