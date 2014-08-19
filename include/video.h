#ifndef _video_
#define _video_

#include "../include/mouse_event.h"
#include "../include/mouse_listener.h"
#include "../include/panel.h"
#include "../include/button.h"

#define CURSOR_DISABLE_MASK ( 1 << 5 )

#define INVALID_POSITION (-1)

#define VIDEO_START (0xb8000)
#define TAB_SPACE 3

#define IS_ALPHA(x) ( ((x) >= 'a' && (x) <= 'z') || ((x) >= 'A' && (x) <= 'Z') )
#define IS_NUM(x) ( (x) >= '0' && (x) <= '9' )

#define IS_ALPHA_NUM(x) (IS_ALPHA(x) || IS_NUM(x))

//Numeros asociados a los panels

#define MAX_PANELS	32
#define MAX_BUTTONS 	32

#define HEADING		0
#define CONSOLE		1
#define SAVE_SCREEN	2

//Numeros asociados a los buttons

#define B_RETURN	0
#define B_1		1

//dimensiones totales
#define COLUMNS 80
#define ROWS 25

//dimensiones de panels
#define HEADING_ROWS 1
#define	HEADING_COLUMNS COLUMNS

#define CONSOLE_ROWS (ROWS-HEADING_ROWS)
#define CONSOLE_COLUMNS COLUMNS

#define SHELL	0
#define VISUAL	1

/*
//TYPEDEFS
typedef struct {

	int present;

	int rows, columns;
	
	//i, j es el par (fila,columna) absoluto. Es decir, son tomados teniendo en cuenta que el origen es VIDEO_START
	int i, j;
	
	//Si bien solo shell maneja un cursor real, todos los panels tienen un concepto de cursor
	int cursor_i, cursor_j;
	
	unsigned int format;
	
	tMouseListener listener;
	
	int mouse_inside;
} tProperties;

*/

typedef struct {
	int x, y;
	unsigned int back_up_format;
	unsigned int mouse_format;
}tMouseState;

//FUNCTIONS
void video_init();

void video_save_screen();
void video_save_mem();
void video_unload_mem();
void video_wake_up();
void video_recover();

void video_switch_mode();

void video_print_mouse(int x, int y);
void video_mouse_update();

void video_clear_kill();
void video_clear_all();
void video_clear(tPanel * type);
void video_clear_current();
void video_shift_rows();
void video_copy_above(int row);
void video_clear_row(int row);

void video_put_char(char c);
void video_visual_put_char(char c);
void video_put_char_innocuous(char c);
void video_put_char_special(char c);
void video_write(char * w);
void video_visual_write(char * w);

void video_format_panel(tPanel * type);

void video_add_panel(tPanel * panel);

void video_add_button(tButton * button);

void video_update();

void video_backspace();
void video_new_line();
void video_draw_heading();
void video_draw_welcome();

int video_position(int i, int j);
int video_position_relative(int i, int j);
void video_set_cursor_ij(int i, int j);
void video_move_to(int i, int j);
void video_disable_cursor();
void video_enable_cursor();

void video_cursor_next();
void video_next_position();
void video_cursor_previous();
void video_cursor_update();

void video_set_focus(tPanel * f);
tPanel * video_get_focus();
void video_set_text_color(int color);
void video_set_background_color(int color);

unsigned int video_create_format(int text, int background);

void video_buffer_size();

void video_push_all();
void video_pop_all();

void video_mouse_move_handler(tMouseEvent * me);
void video_mouse_click_handler(tMouseEvent * me);

void video_panels_check_move(tMouseEvent * me);
void video_panels_check_click(tMouseEvent * me);

void video_mouse_print(int x, int y);
void video_mouse_undo();

int video_mouse_getX();

int video_mouse_getY();


void video_button_text_print(tButton * button);

int video_mouse_over(tPanel * panel, int i, int j);

//Funciones basicas imprecindibles de un button
void video_button_enter(tMouseEvent * me);
void video_button_out(tMouseEvent * me);

#endif
