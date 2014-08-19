#ifndef _kasm_
#define _kasm_

#include "defs.h"
#include "descriptors.h"

unsigned int   	 	_read_msw();

void            	_lidt(IDTR *idtr);

void			_maskPIC1(byte mask);
void			_maskPIC2(byte mask);

void			_cli(void);
void			_sti(void);

void			_int_08_hand(); /* Timertick */

void			_int_09_hand();	/* Keyboard */

void			_int_74_hand(); /* Mouse */

void			_int_80_hand(); /* Int 80h */

int			_syscall(int function, int arg1, int arg2, int arg3);

int			_inb(unsigned short int port);

void			_outb(unsigned short int port, unsigned char value);

void			_debug (void);

#endif
