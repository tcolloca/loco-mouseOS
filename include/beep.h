#ifndef _beep_
#define _beep_

#define MAX_FREQ	5000
#define MIN_FREQ	10

void beep_C4(double duration);

void beep_Csharp4(double duration);

void beep_D4(double duration);

void beep_Dsharp4(double duration);

void beep_D5(double duration);

void beep_Dsharp5(double duration);

void beep_E5(double duration);

void beep_Asharp5(double duration); 

void beep_C6(double duration);

void beep_Csharp6(double duration);

void beep_Gsharp6(double duration);

/**
* @param duration of the beep in seconds.
* @return 1 if freq. isn't allowed, else 0.
*/

int beep(unsigned int freq, double duration);

#endif
