#ifndef _stdio_
#define _stdio_

#include "../include/defs.h"
#include "../include/stdargs.h"

#define CHAR		0
#define PERCENTAGE	1
#define GETINT		2
#define GETCHAR		3
#define GETSTRING	4

#define DEC		10
#define OCT		8
#define HEX		16

typedef struct{
	int fd;
	int getc;
}FILE;

extern FILE * stdin;

int getc(FILE * stream);

int getchar();

char * gets(char * s);

char * fgets(char * s, int num, FILE * stream);

int printf(const char * fmt, ...);

int vprintf(const char * fmt, va_list args);

int fprintf(FILE * stream, const char * fmt, ...);

int vfprintf(FILE * stream, const char * fmt, va_list args);				

void putc(int c, FILE * stream);

void putchar(int c);

int vscanf(const char * fmt, va_list args);

int read(int fd, char * buff, size_t count);

int write(int fd, char * buff, size_t count);

void puts(const char * s);

int scanf(const char * fmt, ...);

int vscanf(const char * fmt, va_list args);

int sscanf(const char * src, const char * fmt, ...);

int vsscanf(const char * src, const char * fmt, va_list args);

static  print_int(FILE * stream, int num);

static int print_oct(FILE * stream, int num);

static int print_hex(FILE * stream, int num);

static int print_bin(FILE * stream, int num);

static int print_uns(FILE * stream, unsigned int num);

static int print_ptr(FILE * stream, void * ptr);

static int print_str(FILE * stream, char * s);

static int getInt(char c, int * dest, int * i, int base);

static int getIntFromString(char c, int * dest, int * i, int base, const char * src, int * j);

static int validNum(char c, int base);

static int getSign(char * c, int * neg);

#endif
