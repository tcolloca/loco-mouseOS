#include "../include/stdlib.h"
#include "../include/ctype.h"
#include "../include/math.h"

static char s[33];
static unsigned long seed = 1;


char * itoa(int num, int base) {
	if( num == 0 ) {
		s[0] = '0';
		s[1] = '\0';
		return s;
	}
	
	int i = 0;
	
	if(num < 0) {
		s[i++] = '-';
		num *= (-1);
	}
	
	itoar(num, base, &i);
	s[i] = '\0';
	return s;
}

static void itoar(int num, int base, int * i) {
	if( num == 0 )
		return;

	int remain;
	int baseAscii = '0';	
	remain = num % base;
	num -= remain;
	num /= base;	
	itoar(num, base, i);
	if( remain > 9 ) {
		baseAscii = 'A' - 10;
	}
	s[(*i)++] = baseAscii + remain;
}

char * utoa(unsigned int num, int base) {
	if( num == 0 ) {
		s[0] = '0';
		s[1] = '\0';
		return s;
	}

	int i = 0;
	utoar(num, base, &i);
	s[i] = '\0';
	return s;
}


static void utoar(unsigned int num, int base, int * i) {
	if( num == 0 )
		return;

	int remain;
	int baseAscii = '0';
	remain = num % base;
	num -= remain;
	num /= base;	
	utoar(num, base, i);
	if( remain > 9 ) {
		baseAscii = 'A' - 10;
	}
	s[(*i)++] = baseAscii + remain;
}
		
char * ptoa(void * ptr) {
	return utoa((int)ptr, 16);
}

int atoi(char * s) {
	int n = 0;
	int i = 0;
	atoir(s, &n, &i, 10);
	return n;
}

static void atoir(char * s, int * dest, int * i, int base) {
	if( *s == '\0' || (base != 16 && !isdigit(*s)) || (base == 16 && !isxdigit(*s)) ||
	    *s - '0' >= base )
		return;
		
	atoir(s+1, dest, i, base);
	if( isdigit(*s) )
		*dest += (*s - '0') * pow(base, (*i)++); 
	else
		*dest += (*s - 'A' + 10) * pow(base, (*i)++);
}

int is_num(char * s) {
	int i;
	for(i = 0; s[i] != 0; i++) {
		if(!isdigit(s[i])) {
			return 0;
		}
	}
	return 1;
}

int rand(void) {
	seed = seed * 1103515245 + 7718299;
	return((unsigned)(seed/65536) % 32768);
}

void srand(unsigned new_seed) {
	seed = new_seed;
}
	
