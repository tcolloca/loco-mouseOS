#include "../include/kasm.h"
#include "../include/rtc.h"
#include "../include/stdio.h"
#include "../include/time.h"
#include "../include/defs.h"

void rtc_init() {
	rtc_set(REGIS_B, 0x06); // 00000110 (0x2) -> Binary Mode, (0x4) -> 24hrs  
	int s = time_get_seconds();
	int m = time_get_minutes();
	int h = time_get_hours();
	h = (h + 24 - 3)%24;
	time_set_time(s, m,  h);
}

int rtc_time(unsigned int regis_id, int * data, int op) {
	switch(op) {
		case GET:
			*data = rtc_get(regis_id);
			break;
		case SET:
			rtc_set(regis_id, *data);
			break;
		default:
			return 1;
	}
	
	return 0;
}

//a.k.a trezeguet
static int rtc_get(int regis_id) {
	_cli();
	_outb(REGIS_PORT, regis_id);
	int ans = _inb(DATA_PORT);
	_sti();
	return ans;
}

static void rtc_set(int regis_id, int value) {
	_cli();
	rtc_wait();
	_outb(REGIS_PORT, regis_id);
	_outb(DATA_PORT, value);
	_sti();
}

static void rtc_wait() {
	do {
		_outb(REGIS_A, REGIS_PORT);
	} while(( _inb(DATA_PORT) & UPDATE_F ));
}
