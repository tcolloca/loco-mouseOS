#ifndef _syscall_
#define _syscall_

#define READ		0
#define WRITE		1
#define TIME		2
#define VISUAL		3
#define BEEP		4
#define MILITIME	5
#define TICK		6

int int_80(int function, int arg1, int arg2, int arg3);

#endif
