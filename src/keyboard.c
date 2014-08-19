#include "../include/defs.h"
#include "../include/keyboard.h"
#include "../include/ascii.h"
#include "../include/keyboard_event.h"
#include "../include/stdio.h"

static char* keyboard_number_values[] = {"1!","2@","3#","4$","5%","6^","7&","8*","9(","0)","-_", "=+"};
static char* keyboard_row1[] = {"qQ","wW","eE","rR","tT","yY","uU","iI","oO","pP","[{","]}"};
static char* keyboard_row2[] = {"aA","sS","dD","fF","gG","hH","jJ","kK","lL",";:","\'\""};
static char* keyboard_row3[] = {"zZ","xX","cC","vV","bB","nN","mM",",<",".>","/?"};

static char* keyboard_number_values_es[] = {"1!","2@","3\"","4$","5%","6&","7/","8(","9)","0=","'?"};
static char* keyboard_row1_es[] = {"qQ","wW","eE","rR","tT","yY","uU","iI","oO","pP","`^","+*"};
static char* keyboard_row2_es[] = {"aA","sS","dD","fF","gG","hH","jJ","kK","lL"};
static char* keyboard_row3_es[] = {"zZ","xX","cC","vV","bB","nN","mM",",;",".:","-_"};

static int l_shift = FALSE;
static int r_shift = FALSE;
static int shifted = FALSE;
static int caps_lock = FALSE;

static unsigned int last_scancode = -1;
static unsigned int last_shift = -1;

static tKeyboardEvent ke;


void keyboard_handler() {

	unsigned int scancode = _inb(READ_PORT);
	char aux = scancode_to_char(scancode);

	if(IS_PRESSED(scancode)) {
		//printf("%d; ", scancode);
		if(IS_SHIFT(scancode)) {
			if(scancode == L_SHIFT) {
				l_shift = TRUE;
			} else {
				r_shift = TRUE;
			}
			return;
		}
		
		if(aux != INVALID) {
			ke.key = aux;
			keyboard_event_shoot(K_PRESSED, &ke);
			//printf("interrupcion\n");
			/*
			if(aux != ASCII_BACKSPACE) {
				write(STDIN, &aux, 1);
			}
			terminal_handle(aux);
			*/
		}
	} else {
		unsigned int pressed = scancode & ~RELEASED;
		
		if(IS_SHIFT(pressed)) {
			if(pressed == L_SHIFT) {
				l_shift = FALSE;
			} else {
				r_shift = FALSE;
			}
		}
		
		if(aux != INVALID) {
			ke.key = aux;
			keyboard_event_shoot(K_RELEASED, &ke);
		}
	}
}

static int is_mayus() {
	return XOR(is_shifted(), caps_lock);
}

static int is_shifted() {
	return l_shift || r_shift;
}

static char scancode_to_char(unsigned int scancode) {
	
	int type = classify(scancode);
	if(type == INVALID)
		return type;
	
	switch(type) {
		case NUMBER:
			return keyboard_number_values[scancode - NUMBER_INIT][is_mayus()];
		case ROW1:
			return keyboard_row1[scancode - ROW1_INIT][is_mayus()];
		case ROW2:
			return keyboard_row2[scancode - ROW2_INIT][is_mayus()];
		case ROW3:
			return keyboard_row3[scancode - ROW3_INIT][is_mayus()];
		case BACKSPACE:
			return ASCII_BACKSPACE;
		case ENTER:
			return ASCII_ENTER;
		case L_SHIFT:
		case R_SHIFT:
			return ASCII_SHIFT;
		case SPACE:
			return ASCII_SPACE;
			break;
		
	}
}

static int classify(unsigned int sc) {

	unsigned int scancode = sc & ~RELEASED;
	
	if(NUMBER_INIT <= scancode & scancode<= NUMBER_END) {
		return NUMBER;
	} else if(ROW1_INIT <= scancode & scancode <= ROW1_END){
		return ROW1;
	} else if(ROW2_INIT <= scancode & scancode <= ROW2_END){
		return ROW2;
	} else if(ROW3_INIT <= scancode & scancode <= ROW3_END){
		return ROW3;
	} else if(scancode == BACKSPACE || scancode == SPACE || IS_SHIFT(scancode) || scancode == ENTER) {
		return scancode;
	} else {
		return INVALID;
	}
}

