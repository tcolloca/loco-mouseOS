#include "../include/error.h"
#include "../include/math.h"

int pow(int n1, int n2) {
	if( n1 == 0 && n2 != 0 )
		return 0;
	else if( n1 == 0 && n2 == 0 ) {
		error_set(MATH_ERROR, "pow");
		return 0;
	}
	else if( n1 == 1 )
		return 0;
	return powR(n1, n2);
}

static int powR(int n1, int n2) {
	if( n2 == 0 )
		return 1;
	return n1*powR(n1, n2 - 1);
}

int round(double n) {
	double m = mantissa(n);
	if( m < 0.5 )
		return floor(n);
	else
		return ceil(n);
}

int floor(double n) {
	if( n < 0 )
		return -(ceil((-1)*n));
	return (int)n;
}

int ceil(double n) {
	if( n < 0 )
		return -(floor((-1)*n));
	if( isInt(n) )
		return (int)n;
	return (int)(n+1);
}

static int isInt(double n) {
	int aux = (int)n;
	return (double)aux == n;
}	

static double mantissa(double n) {
	return n - (double)floor(n);
}
