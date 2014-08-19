#include "../include/string.h"
#include "../include/defs.h"

int strcmp(const char * s1, const char * s2) {
	int i = 0;
	
	while(s1[i] != 0 && s2[i] != 0 && s1[i] == s2[i]) {
		i++;
	}
	
	return s1[i] - s2[i];
}

int strlen(const char * s) {
	int n = 0;
	while( *(s++) != 0 )
		n++;
	return n;
}

char * strcpy(char * dest, const char * src) {
	char * aux = dest;	
	while(*(dest++) = *(src++));
	return aux;
}

char * strcat(char * s1, const char * s2) {
	strcpy (s1 + strlen (s1), s2);
     	return s1;
}

char * strchr(char *s, int c) {
	while( *s != c && *s != 0 ) {
		*s++;
	}
	if( *s == 0 && c != 0 )
		return NULL;
	return s;
} 
