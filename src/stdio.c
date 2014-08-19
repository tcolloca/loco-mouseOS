#include "../include/stdio.h"
#include "../include/kasm.h"
#include "../include/syscall.h"
#include "../include/math.h"
#include "../include/ctype.h"

static char cut;
static char ungetc;
static int ungetc_flag;

FILE _stdin = { STDIN };
FILE _stdout = { STDOUT };
FILE _stderr = { STDERR };

FILE * stdin = &_stdin;

int getc(FILE * stream) {
	char c;
	read(stream->fd, &c, 1);
	stream->getc = 1;
	return c;
}

int getchar() {
	return getc(&_stdin);	 
}

char * gets(char * s) {
	int c;	
	while( (c = getchar()) != '\n' ) {
		*(s++) = (char)c;
	}
	*s = 0;
	return s;
}

char * fgets(char * s, int num, FILE * stream) {
	int c, i = 0;
	char * str = s;	
	while( i < num - 1 && (c = getc(stream)) != '\n' ) {
		*(s++) = (char)c;
		i++;
	}
	*s = 0;
	return str;
}

int printf(const char * fmt, ...) {
	va_list args;
	int read;

	va_start(args, fmt);
	read = vprintf(fmt, args);
	va_end(args);
	
	return read;
}

int vprintf(const char * fmt, va_list args) {
	return vfprintf(&_stdout, fmt, args);
} 

int fprintf(FILE * stream, const char * fmt, ...) {
	va_list args;
	int read;

	va_start(args, fmt);
	read = vfprintf(stream, fmt, args);
	va_end(args);
	
	return read;
}

int vfprintf(FILE * stream, const char * fmt, va_list args) {
	int i;
	int read = 0;
	for( i = 0; fmt[i] != 0; i++ ) {
		if( fmt[i] != '%' ) {
			putc(fmt[i], stream);
			read++;
		}
		else {
			i++;
			switch( fmt[i] ) {
				case 'd':				
				case 'i':
					read += print_int(stream, va_arg(args, int));
					break;	
				case 'o':
					read += print_oct(stream, va_arg(args, int));
					break;
				case 'x':
				case 'h':
					read += print_hex(stream, va_arg(args, int));
					break;
				case 'b':
					read += print_bin(stream, va_arg(args, int));
					break;
				case 'u':
					read += print_uns(stream, va_arg(args, unsigned int));
					break;
				case 'p':
					read += print_ptr(stream, va_arg(args, void *));
					break;
				case 'c':
					putc((int)va_arg(args, char), stream);
					read++;
					break;			
				case 's':
					read += print_str(stream, va_arg(args, char*));
					break;  
				case '\0':
					i--;				
				case '%':
					putc('%', stream);
					read++;
					break;
				default:
					putc('%', stream);
					putc(fmt[i], stream);
					read += 2;
			}
		}
	}

	return read;
}					
			
static int print_int(FILE * stream, int num) {
	return print_str(stream, (char *)itoa(num, 10));
} 

static int print_oct(FILE * stream, int num) {
	return print_str(stream, (char *)itoa(num, 8));
} 

static int print_hex(FILE * stream, int num) {
	return print_str(stream, (char *)itoa(num, 16));
} 

static int print_bin(FILE * stream, int num) {
	return print_str(stream, (char *)itoa(num, 2));
}

static int print_uns(FILE * stream, unsigned int num) {
	return print_str(stream, (char *)utoa(num, 10));
} 

static int print_ptr(FILE * stream, void * ptr) {
	return print_str(stream, (char *)ptoa(ptr));
}
static int print_str(FILE * stream, char * s) {
	int i = 0;
	while( s[i] != 0 ) {
		putc(s[i++], stream);
	}
	return i - 1;
}

void putc(int c, FILE * stream) {
	write(stream->fd, (char *)(&c), 1);
}

void putchar(int c) {
	putc(c, &_stdout);
}

void puts(const char * s) {
	while( *s != 0 )
		putc(*(s++), &_stdin);
}

int scanf(const char * fmt, ...) {
	va_list args;
	int read;

	va_start(args, fmt);
	read = vscanf(fmt, args);
	va_end(args);
	
	return read;
}

int vscanf(const char * fmt, va_list args) {

	int read = 0, i = 0, type, state = CHAR;
	int sign, hasSign, base;
	char * str, * sdest;	
	char c;
	while( fmt[i] != 0 ) {
		switch( state ) {
			case CHAR:
				switch( fmt[i] ) {
					case '%':
						state = PERCENTAGE;
						break;
					case ' ':
					default:
						c = getchar();
						if( c != fmt[i] )
							return read;
				}
				i++;
				break;
			case PERCENTAGE:
				switch( fmt[i] ) {
					case '%':
						state = CHAR;
						c = getchar();
						if( c != fmt[i] )
							return read;
						i++;
						break;
					case 'd':
						state = GETINT;
						type = DEC;
						break;
					case 'h':
					case 'x':
						state = GETINT;
						type = HEX;
						break;
					case 'o':
						state = GETINT;
						type = OCT;
						break;
					case 'c':
						state = GETCHAR;
						break;
					case 's':
						state = GETSTRING;
						break;
					default:
						return -1; //TODO: ERROR
				}
				break;
			case GETINT:
				base = 10;
				hasSign = 0;
				sign = 1;
				i++;
				cut = fmt[i++];
				state = CHAR;
				c = getchar();
				switch( c ) {
					case '-':
						sign = -1;
					case '+':
						c = getchar();
						hasSign = 1;
						break;
				}

				if( hasSign && c == cut ) {
					return read;
				} else if( !hasSign && c == cut ) {					
					break;
				}
 
				if( type == OCT || type == HEX) {
					if( c != '0' ) {
						return read;
					}
					c = getchar();
			
					if( type == HEX ) {
						if( c != 'x' )
							return read;
						c = getchar();
						base = 16;
					} else
						base = 8;
					
				}
				
				if( !validNum(c, base) ) {
					return read;
				} else {
					int * dest = va_arg(args, int *);
					int k = 0;
					int ret;
					*dest = 0;
					ret = getInt(c, dest, &k, base);
					*dest *= sign;
					read++;
					if( !ret ) {
						return read;
					} 
				}
				break;
			case GETCHAR:
				state = CHAR;
				c = getchar();
				if( !isgraph(c) )
					return read;
				*va_arg(args, char *) = c;
				i++;
				read++;
				break;
			case GETSTRING:	
				i++;		
				cut = fmt[i++];
				state = CHAR;
				c = getchar();
				sdest = va_arg(args, char *);
				str = sdest;	
					
				while( c != cut && isgraph(c) ) {
					*(sdest++) = c;
					c = getchar();					
				}	
				*sdest = 0;
					
				if( (*str) )
					read++;

				if( c != cut )
					return read;
				
				break;		
		}
	}
	return read;
}

int sscanf(const char * src, const char * fmt, ...) {
	va_list args;
	int read;

	va_start(args, fmt);
	read = vsscanf(src, fmt, args);
	va_end(args);
	
	return read;
}

int vsscanf(const char * src, const char * fmt, va_list args) {

	int read = 0, i = 0, j = 0, type, state = CHAR;
	int sign, hasSign, base;
	char * str, * sdest;	
	char c;
	while( fmt[i] != 0 ) {
		switch( state ) {
			case CHAR:
				switch( fmt[i] ) {
					case '%':
						state = PERCENTAGE;
						break;
					case ' ':
					default:
						c = src[j++];
						if( c != fmt[i] )
							return read;
				}
				i++;
				break;
			case PERCENTAGE:
				switch( fmt[i] ) {
					case '%':
						state = CHAR;
						c = src[j++];
						if( c != fmt[i] )
							return read;
						i++;
						break;
					case 'd':
						state = GETINT;
						type = DEC;
						break;
					case 'h':
					case 'x':
						state = GETINT;
						type = HEX;
						break;
					case 'o':
						state = GETINT;
						type = OCT;
						break;
					case 'c':
						state = GETCHAR;
						break;
					case 's':
						state = GETSTRING;
						break;
					default:
						return -1; //TODO: ERROR
				}
				break;
			case GETINT:
				base = 10;
				hasSign = 0;
				sign = 1;
				i++;
				cut = fmt[i++];
				state = CHAR;
				c = src[j++];
				switch( c ) {
					case '-':
						sign = -1;
					case '+':
						c = src[j++];
						hasSign = 1;
						break;
				}

				if( hasSign && c == cut ) {
					return read;
				} else if( !hasSign && c == cut ) {					
					break;
				}
 
				if( type == OCT || type == HEX) {
					if( c != '0' ) {
						return read;
					}
					c = src[j++];
			
					if( type == HEX ) {
						if( c != 'x' )
							return read;
						c = src[j++];
						base = 16;
					} else
						base = 8;
					
				}
				
				if( !validNum(c, base) ) {
					return read;
				} else {
					int * dest = va_arg(args, int *);
					int k = 0;
					int ret;
					*dest = 0;
					ret = getIntFromString(c, dest, &k, base, src, &j);
					*dest *= sign;
					read++;
					if( !ret ) {
						return read;
					} 
				}
				break;
			case GETCHAR:
				state = CHAR;
				c = src[j++];
				if( !isgraph(c) )
					return read;
				*va_arg(args, char *) = c;
				i++;
				read++;
				break;
			case GETSTRING:	
				i++;		
				cut = fmt[i++];
				state = CHAR;
				c = src[j++];
				sdest = va_arg(args, char *);
				str = sdest;	
					
				while( c != cut && isgraph(c) ) {
					*(sdest++) = c;
					c = src[j++];					
				}	
				*sdest = 0;
					
				if( (*str) )
					read++;

				if( c != cut )
					return read;
				
				break;		
		}
	}
	return read;
}

static int getInt(char c, int * dest, int * i, int base) {
	if( c == cut ) {
		return 1;
	} else if( !validNum(c, base) ) {
		return 0;
	}

	char chr = getchar();
	int ret = getInt(chr, dest, i, base);
	
	if( isdigit(c) )
		*dest += (c - '0') * pow(base, (*i)++); 
	else if( isupper(c) )
		*dest += (c - 'A' + 10) * pow(base, (*i)++); 
	else
		*dest += (c - 'a' + 10) * pow(base, (*i)++); 
	
	return ret;
}

static int getIntFromString(char c, int * dest, int * i, int base, const char * src, int * j) {
	if( c == cut ) {
		return 1;
	} else if( !validNum(c, base) ) {
		return 0;
	}

	char chr = src[(*j)++];
	int ret = getIntFromString(chr, dest, i, base, src, j);
	
	if( isdigit(c) )
		*dest += (c - '0') * pow(base, (*i)++); 
	else if( isupper(c) )
		*dest += (c - 'A' + 10) * pow(base, (*i)++); 
	else
		*dest += (c - 'a' + 10) * pow(base, (*i)++); 
	
	return ret;
}

static int validNum(char c, int base) {
	return (isdigit(c) && c - '0' < base) || (base == 16 && isxdigit(c));
}

int read(int fd, char * buff, size_t count) {
	return _syscall(READ, fd, (int)buff, count);
}

int write(int fd, char * buff, size_t count) {
	return _syscall(WRITE, fd, (int)buff, count);
}
