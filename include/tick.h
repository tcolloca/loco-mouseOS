#ifndef _tick_
#define _tick_

/**
* @params	period of each tick in milliseconds.
* @return	may throw warning according to period.
*/

void tick_set_period(int period);

int tick_get_period();

#endif
