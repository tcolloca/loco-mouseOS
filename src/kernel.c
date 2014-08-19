#include "../include/kasm.h"
#include "../include/descriptors.h"
#include "../include/video.h"
#include "../include/mouse.h"
#include "../include/shell.h"
#include "../include/terminal.h"

#include "../include/stdio.h"


DESCR_INT idt[0x100];			/*256 IDT' entries*/
IDTR idtr;				/* IDTR */

kmain() {
	terminal_init();

	setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x09], 0x08, (dword)&_int_09_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x74], 0x08, (dword)&_int_74_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x80], 0x08, (dword)&_int_80_hand, ACS_INT, 0);
	

	/* IDTR Setting */ 

	idtr.base = 0;  
	idtr.base +=(dword) &idt;
	idtr.limit = sizeof(idt)-1;
	
	_lidt(&idtr);

	/* Interrupt unmasking */
	
	_cli();

	_maskPIC1(0xF8);           /*0XF8*/
	_maskPIC2(0xEF);		/*0XEF*/
	
	_sti();

	video_init();
	timertick_init();
	rtc_init();
	mouse_init();
	shell_run();
}

