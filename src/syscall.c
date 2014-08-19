#include "../include/syscall.h"

int int_80(int function, int arg1, int arg2, int arg3) {

	int value = -1;

	switch(function) {
		case READ:
			value = io_read(arg1, (char*)arg2, arg3);
			break;
		case WRITE:
			value = io_write(arg1, (char*)arg2, arg3);
			break;			
		case TIME:
			value = rtc_time((unsigned int)arg1, (int*)arg2, arg3);
			break;
		case VISUAL:
			value = visual_handle(arg1, (void *)arg2, (void *)arg3);
			break;
		case BEEP:
			value = pc_speaker_beep(arg1, (unsigned int)arg2);
			break;
		case MILITIME:
			value = timertick_get_millis();
			break;
		case TICK:
			value = timertick_period(arg1, arg2);
			break;
	}
	
	return value;

}
