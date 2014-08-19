#include "../include/syscall.h"
#include "../include/defs.h"
#include "../include/error.h"
#include "../include/warning.h"

void tick_set_period(int period) {
	switch( _syscall(TICK, SET, period, 0) ) {
		case INVALID:
			error_set(INVALID_ENTRY, "tick_set_period");
			break;
		case SMALL:
			warning_set(TICK_SMALL, "tick_set_period");
			break;
		case BIG:
			warning_set(TICK_BIG, "tick_set_period");
			break;
	}
}

int tick_get_period() {
	return _syscall(TICK, GET, 0, 0);
}
