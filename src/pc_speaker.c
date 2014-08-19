#include "../include/pc_speaker.h"
#include "../include/defs.h"
#include "../include/kasm.h"

int pc_speaker_beep(int type, unsigned int freq) {
	_cli();	
	switch( type ) {
		case ON:
			pc_speaker_start_beep(freq);	
			break;		
		case OFF:
			pc_speaker_shut_up();
			break;
	}
	_sti();
	return 0;
}

static void pc_speaker_start_beep(unsigned int freq) {
 	unsigned int div;
 	unsigned char tmp;
 
 	div = PIT_FREQ / freq;
 	_outb(CONFIG_PORT, 0xB6); // 10|11|011|0 -> Binary Mode, 011 -> Sqr Wave, 	
	_outb(CH2_PORT, (unsigned char) div);             //11 -> Access Mode low/hi bytes, 10 -> Ch 2
 	_outb(CH2_PORT, (unsigned char) (div >> 8));
 
 	tmp = _inb(STATUS_PORT);
  	if (tmp != (tmp | 3)) { //enables speaker.
 		_outb(STATUS_PORT, tmp | 3);
	}
}
 
static void pc_speaker_shut_up() {
	unsigned char tmp = (_inb(STATUS_PORT) & 0xFC); //disables speaker.
 
 	_outb(STATUS_PORT, tmp);
}

