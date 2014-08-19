#ifndef _kernel_
#define _kernel_

//TODO: Not used!

#define OS_PID	0 

int (*player)(void); 

typedef enum eINT_80 {WRITE=0, READ} tINT_80;
typedef enum eUSER {U_KERNEL=0, U_NORMAL} tUSERS;

#endif
