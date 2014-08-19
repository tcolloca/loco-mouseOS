#include "../include/video.h"
#include "../include/stack.h"
#include "../include/ascii.h"
#include "../include/savescreen.h"
#include "../include/string.h"
#include "../include/defs.h"
#include "../include/stdio.h"

static tPanel * panels[MAX_PANELS];
static int panels_amount = 0;

static tPanel * focus;

static tPanel heading, console, savescreen, background;

static tButton * buttons[MAX_BUTTONS];
static int buttons_amount = 0;

static int buffer_length;

static char * video = (char*)VIDEO_START;

static char saved_mem[ROWS*COLUMNS*2];

static int saved = 0;

static int sleeping = 0;

static tMouseListener listener;

static tMouseState mouse_state;

static int mode;

void video_init() {	
	panel_init(&heading, HEADING_COLUMNS, HEADING_ROWS, 0, 0, FORMAT(WHITE, BLUE));
	video_add_panel(&heading);
	
	panel_init(&console, CONSOLE_COLUMNS, CONSOLE_ROWS, 0, HEADING_ROWS, FORMAT(WHITE, BLACK));
	video_add_panel(&console);
	
	panel_init(&savescreen, COLUMNS, ROWS, 0, 0, FORMAT(BLUE, BLUE));
	video_add_panel(&savescreen);
	
	panel_init(&background, COLUMNS, ROWS, 0, 0, FORMAT(WHITE, BLACK));
	video_add_panel(&background);
	
	heading.present = 1;
	console.present = 1;
	
	video_set_focus(&console);
	
	video_clear_kill();
	video_update();
	
	video_cursor_update();
	video_draw_heading();
	savescreen_init(video_save_screen, 10, LIGHT_BLUE);
	

	mouse_state.mouse_format = FORMAT(WHITE, GREEN);
	video_mouse_print(0,0);
	
	mouse_listener_init(&listener);
	mouse_listener_add(MOVE, video_mouse_move_handler, &listener);
	mouse_listener_add(DRAG, video_mouse_move_handler, &listener);
	mouse_listener_add(L_CLICK, video_mouse_click_handler, &listener);
	mouse_listener_add(R_CLICK, video_mouse_click_handler, &listener);
	mouse_listener_add(M_CLICK, video_mouse_click_handler, &listener);
	mouse_listener_add(L_RELEASE, video_mouse_click_handler, &listener);
	mouse_listener_add(R_RELEASE, video_mouse_click_handler, &listener);
	mouse_listener_add(M_RELEASE, video_mouse_click_handler, &listener);
	mouse_event_add(&listener);

	
	mode = SHELL;
}

void video_die() {
	video_push_all();
	video_save_mem();
	heading.present = 0;
	console.present = 0;
	background.present = 1;
	video_set_focus(&background);
	video_clear_kill();
	video_disable_cursor();
	mode = VISUAL;
	
}

void video_live() {
	heading.present = 1;
	console.present = 1;
	background.present = 0;
	video_set_focus(&console);
	
	//Me olvido de todos los componentes que agrego el usuario
	panels_amount = 4;
	buttons_amount = 0;
	
	video_enable_cursor();
	mode = SHELL;
	video_pop_all();
	video_unload_mem();
	video_format_panel(&heading);
	video_format_panel(&console);
	
	//mouse_state.back_up_format = video[ video_position(mouse_state.y, mouse_state.x) + 1];
	video_mouse_print(mouse_state.x, mouse_state.y);
}

void video_mouse_show() {

	int i;
	int flag = 0;
	for(i = 0; i < buttons_amount && !flag; i++) {
		if( video_mouse_over(&(buttons[i]->panel), mouse_state.y, mouse_state.x) ) {
			mouse_state.back_up_format = buttons[i]->format_over;
			flag = 1;
		}
	}
	if(!flag) {
		mouse_state.back_up_format = video[ video_position(mouse_state.y, mouse_state.x) + 1];
	}
	
	video[ video_position(mouse_state.y, mouse_state.x) + 1] = mouse_state.mouse_format;
}

void video_mouse_update() {
	video_mouse_print(mouse_state.x, mouse_state.y);
}

void video_update() {

	video_clear_kill();
	int i;
	for(i = 0; i <= panels_amount - 1; i++) {
		if(panels[i]->present) {
			video_format_panel(panels[i]);
		}
	}
	
	for(i = buttons_amount - 1; i >= 0; i--) {
		if(buttons[i]->panel.present) {
			video_format_panel(&(buttons[i]->panel));
			video_button_text_print(buttons[i]);
		}
	}
}

void video_button_text_print(tButton * button) {
	int blank = button->blank;
	int mid = button->mid;
	char * s = button->text;
	
	video_push_all();
	
	video_set_focus(&(button->panel));
	video_clear(&(button->panel));
	
	while(mid > 0) {
		video_new_line();
		mid--;
	}
	while(blank > 0) {
		video_visual_put_char(' ');
		blank--;
	}
	
	video_visual_write(s);
	
	video_pop_all();
}

void video_add_panel(tPanel * panel) {
	if(panels_amount >= MAX_PANELS) {
		return;
	}
	
	panels[panels_amount++] = panel;
}

void video_add_button(tButton * button) {
	if(buttons_amount >= MAX_BUTTONS) {
		return;
	}
	
	buttons[buttons_amount++] = button;
}

int video_mouse_getX() {
	return mouse_state.x;
}

int video_mouse_getY() {
	return mouse_state.y;
}

void video_mouse_undo() {
	video[ video_position(mouse_state.y, mouse_state.x) + 1 ] = mouse_state.back_up_format;
}

void video_mouse_print(int x, int y) {
	mouse_state.back_up_format = video[ video_position(y,x) + 1 ];
	mouse_state.x = x;
	mouse_state.y = y;
	video[ video_position(y,x) + 1 ] = mouse_state.mouse_format;
}

int video_mouse_over(tPanel * panel, int i, int j) {

	if(panel->i > i || panel->j > j) {
		return 0;
	}
	
	if(i >= panel->i + panel->rows || j >= panel->j + panel->columns) {
		return 0;
	}

	return 1;
}

void video_panels_check_move(tMouseEvent * me) {
	
	int i;
	
	for( i = panels_amount - 1; i >= 0; i-- ) {
		me->mystery = (void *)panels[i];
		if(panels[i]->present) {
			if( video_mouse_over(panels[i], me->mouse_y, me->mouse_x ) ) {
				
				if(!panels[i]->mouse_inside) {
					panels[i]->mouse_inside = 1;
					if(panels[i]->listener.handlers[ENTER] != NULL) {
						panels[i]->listener.handlers[ENTER](me);
					}
				} else {
					if(me->additional_data[1] == MOVE && panels[i]->listener.handlers[MOVE] != NULL) {
						panels[i]->listener.handlers[MOVE](me);
					}
					
					if(me->additional_data[1] == DRAG && panels[i]->listener.handlers[DRAG] != NULL) {
						panels[i]->listener.handlers[DRAG](me);
					}
				}
				
			} else {
				if(panels[i]->mouse_inside) {
					panels[i]->mouse_inside = 0;
					if(panels[i]->listener.handlers[OUT] != NULL) {
						panels[i]->listener.handlers[OUT](me);
						//la siguiente linea va solo para los botones
						//mouse_state.back_up_format = buttons[me->additional_data[0]].format_normal;
					}
				}
			}
		}
	}
}

void video_panels_check_click(tMouseEvent * me) {
	int i;
	
	for( i = panels_amount - 1; i >= 0; i-- ) {
		me->mystery = (void *)panels[i];
		if(panels[i]->present) {
			if( video_mouse_over(panels[i], me->mouse_y, me->mouse_x ) ) {
				
				if(panels[i]->listener.handlers[me->additional_data[1]] != NULL) {
					panels[i]->listener.handlers[me->additional_data[1]](me);
				}
				
			}
		}
	}
}

void video_buttons_check_move(tMouseEvent * me) {
	
	int i;
	
	for( i = buttons_amount - 1; i >= 0; i-- ) {
		me->mystery = (void *)buttons[i];
		if(buttons[i]->panel.present) {
			if( video_mouse_over(&(buttons[i]->panel), me->mouse_y, me->mouse_x ) ) {
				
				if(!buttons[i]->panel.mouse_inside) {
					buttons[i]->panel.mouse_inside = 1;
					if(buttons[i]->panel.listener.handlers[ENTER] != NULL) {
						buttons[i]->panel.listener.handlers[ENTER](me);
					}
				} else {
					if(me->additional_data[1] == MOVE && buttons[i]->panel.listener.handlers[MOVE] != NULL) {
						buttons[i]->panel.listener.handlers[MOVE](me);
					}
					
					if(me->additional_data[1] == DRAG && buttons[i]->panel.listener.handlers[DRAG] != NULL) {
						buttons[i]->panel.listener.handlers[DRAG](me);
					}
				}
				
			} else {
				if(buttons[i]->panel.mouse_inside) {
					buttons[i]->panel.mouse_inside = 0;
					if(buttons[i]->panel.listener.handlers[OUT] != NULL) {
						buttons[i]->panel.listener.handlers[OUT](me);
						mouse_state.back_up_format = buttons[me->additional_data[0]]->format_normal;
					}
				}
			}
		}
	}
}

void video_buttons_check_click(tMouseEvent * me) {
	int i;
	
	for( i = buttons_amount - 1; i >= 0; i-- ) {
		me->mystery = (void *)buttons[i];
		if(buttons[i]->panel.present) {
			if( video_mouse_over(&(buttons[i]->panel), me->mouse_y, me->mouse_x ) ) {
				
				if(buttons[i]->panel.listener.handlers[me->additional_data[1]] != NULL) {
					buttons[i]->panel.listener.handlers[me->additional_data[1]](me);
				}
				
			}
		}
	}
}

void video_mouse_move_handler(tMouseEvent * me) {
	if( sleeping )
		video_recover();
	
	video_panels_check_move(me);
	video_buttons_check_move(me);
	
	video_mouse_undo();
	video_mouse_print(me->mouse_x, me->mouse_y);
	
	me->mystery = NULL;
	video_wake_up();
}

void video_mouse_click_handler(tMouseEvent * me) {
	if( sleeping )
		video_recover();
	
	video_panels_check_click(me);
	video_buttons_check_click(me);
	video_wake_up();
}

void video_save_screen() {
	if(!sleeping) {
		video_push_all();
		video_set_focus(&savescreen);
		video_save_mem();
		video_disable_cursor();
		video_set_background_color(savescreen_get_color());
		video_clear_current();
		sleeping = TRUE;
		video_pop_all();
	}
}

void video_save_mem() {
	int i, j;
	
	if(!saved) {
		saved = TRUE;
		for(i = 0; i < ROWS; i++) {
			for(j = 0; j < COLUMNS; j++) {
				saved_mem[video_position(i,j)] = video[video_position(i,j)];
			}
		}
	}
}

void video_unload_mem() {
	int i, j;
	
	if(saved) {
		saved = FALSE;
		for(i = 0; i < ROWS; i++) {
			for(j = 0; j < COLUMNS; j++) {
				video[video_position(i,j)] = saved_mem[video_position(i,j)];
			}
		}
	}
}

void video_recover() {
	if(sleeping) {
		sleeping = FALSE;
		
		if(mode != VISUAL) {
			video_unload_mem();
			video_format_panel(&heading);
			video_format_panel(&console);
			video_enable_cursor();
		} else {
			video_update();
		}
	}
}

void video_wake_up() {
	savescreen_reset_timer();	
}

void video_clear_all() {
	int i;
	
	for(i = panels_amount;  i >= 0; i--) {
		if(panels[i]->present) {
			video_clear(panels[i]);
		}
	}
	
	for(i = buttons_amount;  i >= 0; i--) {
		if(buttons[i]->panel.present) {
			video_clear(&(buttons[i]->panel));
		}
	}
}

void video_clear_kill() {
	int i, j;
	
	for(i = 0; i < ROWS; i++) {
		for(j = 0; j < COLUMNS; j++) {
			video[video_position(i,j)] = ' ';
			video[video_position(i,j) + 1] = FORMAT(WHITE, BLACK);;
		}
	}
}

void video_clear(tPanel * type) {
	int flag = 0;
	if(type != focus) {
		video_push_all();
		video_set_focus(type);
		flag = 1;
	}

	int i, j;
	for(i = 0; i < type->rows; i++) {
		for(j = 0; j< type->columns; j++) {
			video[video_position_relative(i,j)] = ' ';
		}
	}
	
	video_move_to(0, 0);
	
	if(flag) {
		video_pop_all();
	}
	
	video_cursor_update();
}

void video_format_panel(tPanel * type) {
	int flag = 0;
	if(type != focus) {
		video_push_all();
		video_set_focus(type);
		flag = 1;
	}

	int i, j;
	for(i = 0; i < type->rows; i++) {
		for(j = 0; j < type->columns; j++) {
			video[video_position_relative(i,j)+1] = type->format;
		}
	}
	
	
	if(flag) {
		video_pop_all();
	}
	
	video_cursor_update();
}

void video_clear_current() {
	video_clear(focus);
}

void video_shift_rows() {
	int row;
	for(row = 1; row < focus->rows; row++) {
		video_copy_above(row);
	}
	video_clear_row(row-1);
}

void video_copy_above(int row) {
	int j;
	int linear_pos_down;
	int linear_pos_up;
	for(j = 0; j < focus->columns; j++) {
		linear_pos_down = video_position_relative(row, j);
		linear_pos_up = video_position_relative(row-1, j);
		video[linear_pos_up] = video[linear_pos_down];
	}
}

void video_clear_row(int row) {
	int j;
	int linear_pos;
	for(j = 0; j < focus->columns; j++) {
		video[video_position_relative(row, j)] = ' ';
	}
}

void video_put_char(char c) {

	if( sleeping ) {
		video_recover();
	}

	if(mode != VISUAL) {
		video_visual_put_char(c);
		buffer_length++;
	}
	
	video_wake_up();
}

void video_visual_put_char(char c) {
	if(c == '\n') {
		video_new_line();
	} else if(c == '\t') {
		int k;
		for(k = 0; k<TAB_SPACE; k++) {
			video_put_char(' ');
		}
	} else if( ASCII_IS_SPECIAL(c) ) {
		video_put_char_special(c);
	} else {
		int linear_pos = video_position_relative(focus->cursor_i, focus->cursor_j);
		video[linear_pos] = c;
		//video[linear_pos + 1] = panels_info[focus].format;
		video_cursor_next();
	}
}

void video_put_char_innocuous(char c) {
	video_put_char(c);
	buffer_length = 0;
}

void video_put_char_special(char c) {
	
	if(c == ASCII_CLEAR) {
		video_clear_current();
	} else if( ASCII_B_COLOR_BLACK <= c && c <= ASCII_B_COLOR_GRAY ) {
		video_set_background_color(c + 19);
	} else if( ASCII_T_COLOR_BLACK <= c && c <= ASCII_T_COLOR_GRAY ) {
		video_set_text_color(c + 10);
	}
	
}

void video_write(char * w) {
	if(mode != VISUAL) {
		video_visual_write(w);
	}
}

void video_visual_write(char * w) {
	int k;
	for(k = 0; w[k] != 0; k++) {
		video_visual_put_char(w[k]);
	}
}

void video_backspace() {
	if( sleeping )
		video_recover();
	if(buffer_length > 0) {
		if(mode != VISUAL) {
			video_cursor_previous();
			video_visual_put_char(' ');
			buffer_length++;
			video_cursor_previous();
		}
	}
	video_wake_up();
}

void video_new_line() {
	if( sleeping )
		video_recover();
	focus->cursor_j = 0;
	if(focus->cursor_i + 1 >= focus->rows) {
		video_shift_rows();
	} else {
		focus->cursor_i++;
	}
	video_cursor_update();
	buffer_length = 0;
	video_wake_up();
}

void video_draw_heading() {
	video_push_all();
	
	video_set_focus(&heading);
	video_write("\tloco mouse - v1.0");
	
	video_pop_all();
}

int video_position(int i, int j) {
	if(i < 0 || i>= ROWS || j < 0 || j >= COLUMNS) {
		return INVALID_POSITION;
	}
	return (i*COLUMNS + j)*2;
}

int video_position_relative(int i, int j) {
	if(i < 0 || i >= focus->rows || j < 0 || j >= focus->columns) {
		return INVALID_POSITION;
	}
	return video_position(focus->i, focus->j) + (i*COLUMNS + j)*2;
}

void video_set_cursor_ij(int i, int j) {
	int linear_pos = video_position_relative(i,j)/2;

	if(linear_pos != INVALID_POSITION) {
		_outb(0x03D4, 0x0E);
		_outb(0x03D5, linear_pos >> 8);
		
		_outb(0x03D4, 0x0F);
		_outb(0x03D5, linear_pos);
	}
}

void video_move_to(int i, int j) {
	focus->cursor_i = i;
	focus->cursor_j = j;
}

void video_disable_cursor() {
	char csr;
	_outb(0x03D4, 0x0A);
	csr = _inb(0x3D5);
	csr |= CURSOR_DISABLE_MASK;
	_outb(0x03D5, csr);
}


void video_enable_cursor() {
	char csr;
	_outb(0x03D4, 0x0A);
	csr = _inb(0x3D5);
	csr &= ~CURSOR_DISABLE_MASK;
	_outb(0x03D5, csr);
}

void video_cursor_next() {
	video_next_position();
	video_cursor_update();
}

void video_next_position() {
	
	focus->cursor_j++;
	if(focus->cursor_j >= focus->columns) {
		focus->cursor_j = 0;
		if(focus->cursor_i + 1 >= focus->rows) {
			video_shift_rows();
		} else {
			focus->cursor_i++;
		}
	}
}

void video_cursor_previous() {
	focus->cursor_j--;
	if(focus->cursor_j < 0) {
		focus->cursor_j = focus->columns - 1;
		focus->cursor_i--;
	}
	
	video_cursor_update();
	
	buffer_length--;
}

void video_cursor_update() {
	video_set_cursor_ij(focus->cursor_i, focus->cursor_j);
}

void video_set_focus(tPanel * f) {
	focus = f;
}

tPanel * video_get_focus() {
	return focus;
}

void video_set_text_color(int color) {
	focus->format = FORMAT(color, BACKGROUND_COLOR(focus->format));
	video_format_panel(focus);
}

void video_set_background_color(int color) {
	focus->format = FORMAT( TEXT_COLOR(focus->format), color );
	video_format_panel(focus);
}

void video_push_all() {
	stack_push_int(focus->cursor_i);
	stack_push_int(focus->cursor_j);
	stack_push_int(buffer_length);
	stack_push_int((int)focus);
	
	buffer_length = 0;
}

void video_pop_all() {
	video_set_focus((tPanel *)stack_pop_int());
	buffer_length = stack_pop_int();
	focus->cursor_j = stack_pop_int();
	focus->cursor_i = stack_pop_int();
}
