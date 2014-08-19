#include "../include/beep.h"
#include "../include/syscall.h"
#include "../include/defs.h"

/* Octave 	0    1    2    3    4    5    6    7
	Note
	C     16   33   65  131  262  523 1046 2093
	C#    17   35   69  139  277  554 1109 2217
	D     18   37   73  147  294  587 1175 2349
	D#    19   39   78  155  311  622 1244 2489
	E     21   41   82  165  330  659 1328 2637
	F     22   44   87  175  349  698 1397 2794
	F#    23   46   92  185  370  740 1480 2960
	G     24   49   98  196  392  784 1568 3136
	G#    26   52  104  208  415  831 1661 3322
	A     27   55  110  220  440  880 1760 3520
	A#    29   58  116  233  466  932 1865 3729
	B     31   62  123  245  494  988 1975 3951 */
	
void beep_C4(double duration) {
	beep(262, duration); 
}

void beep_Csharp4(double duration) {
	beep(277, duration); 
}

void beep_D4(double duration) {
	beep(294, duration); 
}

void beep_Dsharp4(double duration) {
	beep(311, duration); 
}

void beep_D5(double duration) {
	beep(587, duration); 
}

void beep_Dsharp5(double duration) {
	beep(622, duration); 
}

void beep_E5(double duration) {
	beep(659, duration); 
}

void beep_Asharp5(double duration) {
	beep(880, duration); 
}

void beep_C6(double duration) {
	beep(1046, duration); 
}

void beep_Csharp6(double duration) {
	beep(1109, duration); 
}

void beep_Gsharp6(double duration) {
	beep(1661, duration); 
}

int beep(unsigned int freq, double duration) {
	if( freq < MIN_FREQ || freq > MAX_FREQ )
		return 1;
		
	unsigned int start = time_current_millis();
	
	_syscall(BEEP, ON, freq, 0);
	_sti();
	
	while( time_current_millis() - start < duration * 1000 );
	
	if( duration )		
		_syscall(BEEP, OFF, 0, 0);
		
	return 0;
}

