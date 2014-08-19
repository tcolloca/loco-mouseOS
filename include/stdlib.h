#ifndef _stdlib_
#define _stdlib_

#define RAND_MAX	32767

char * itoa(int num, int base);

char * utoa(unsigned int num, int base);
		
char * ptoa(void * ptr);

int atoi(char * s);

int rand(void);

void srand(unsigned new_seed);

int is_num(char * s);

static void atoir(char * s, int * n, int * i, int base);

static void utoar(unsigned int num, int base, int * i);

static void itoar(int num, int base, int * i);

#endif
