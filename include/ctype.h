#ifndef _ctype_
#define _ctype_

#define islower(x) ('a' <= (x) && (x) <= 'z' )
#define isupper(x) ('A' <= (x) && (x) <= 'Z' )
#define isalpha(x) ( islower(x) || isupper(x) )
#define isdigit(x) ('0' <= (x) && (x) <= '9' )
#define isalnum(x) ( isalpha(x) || isdigit(x) )
#define isgraph(x) ( 33 <= (x) && (x) <= 126 )
#define isprint(x) ( isgraph(x) || (x) == ' ' )
#define iscntrl(x) ( ( 0 <= (x) && (x) <= 31 ) || (x) == 127 ) 
#define ispunct(x) ( isgraph(x) && !isalnum(x) ) 
#define isspace(x) ( (x) == ' ' || (x) == '\t' || (x) == '\n' || \
		     (x) == '\v' || (x) == '\f' || (x) == '\r' )

#define isxdigit(x) ( isdigit(x) || ( 'a' <= (x) && (x) <= 'f' ) || \
		      ( 'A' <= (x) && (x) <= 'F' ) )

#define isascii(x) ( 0 <= (x) && (x) <= 127 )

#endif

