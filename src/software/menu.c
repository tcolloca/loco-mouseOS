#include "../../include/defs.h"
#include "../../include/lomog.h"
#include "../../include/stdio.h"

static tPanel buttonsPanel;

static tButton manHelpButton;
static tButton manManButton;
static tButton manGetTimeButton;
static tButton manSetTimeButton;
static tButton manTColorButton;
static tButton manBColorButton;
static tButton manClearButton;
static tButton manDateButton;
static tButton manDharmaButton;
static tButton manSvscrButton;

static int ret;

static void man_roll_over(tMouseEvent * me) {
	manHelpButton.panel.present = 1;
	manManButton.panel.present = 1;
	manGetTimeButton.panel.present = 1;
	manSetTimeButton.panel.present = 1;
	manTColorButton.panel.present = 1;
	manBColorButton.panel.present = 1;
	
	manClearButton.panel.present = 1;
	manDateButton.panel.present = 1;
	manDharmaButton.panel.present = 1;
	manSvscrButton.panel.present = 1;
	buttonsPanel.present = 1;
	lomog_update();
}

static void hide(tMouseEvent * me) {
	manHelpButton.panel.present = 0;
	manManButton.panel.present = 0;
	manGetTimeButton.panel.present = 0;
	manSetTimeButton.panel.present = 0;
	manTColorButton.panel.present = 0;
	manBColorButton.panel.present = 0;
	
	manClearButton.panel.present = 0;
	manDateButton.panel.present = 0;
	manDharmaButton.panel.present = 0;
	manSvscrButton.panel.present = 0;
	buttonsPanel.present = 0;
	lomog_update();
}

static void finish(tMouseEvent * me) {
	lomog_end();
}

static void help_handler(tMouseEvent * me) {
	ret = 1;
	lomog_end();
}

static void fortune_handler(tMouseEvent * me) {
	ret = 2;
	lomog_end();
}

static void date_handler(tMouseEvent * me) {
	ret = 3;
	lomog_end();
}

static void gettime_handler(tMouseEvent * me) {
	ret = 4;
	lomog_end();
}

static void dharma_handler(tMouseEvent * me) {
	ret = 5;
	lomog_end();
}

static void man_help_handler(tMouseEvent * me) {
	ret = 6;
	lomog_end();
}

static void man_man_handler(tMouseEvent * me) {
	ret = 7;
	lomog_end();
}

static void man_t_color_handler(tMouseEvent * me) {
	ret = 8;
	lomog_end();
}

static void man_b_color_handler(tMouseEvent * me) {
	ret = 9;
	lomog_end();
}

static void man_gettime_handler(tMouseEvent * me) {
	ret = 10;
	lomog_end();
}

static void man_settime_handler(tMouseEvent * me) {
	ret = 11;
	lomog_end();
}

static void man_date_handler(tMouseEvent * me) {
	ret = 12;
	lomog_end();
}

static void man_svscr_handler(tMouseEvent * me) {
	ret = 13;
	lomog_end();
}

static void man_clear_handler(tMouseEvent * me) {
	ret = 14;
	lomog_end();
}

static void man_dharma_handler(tMouseEvent * me) {
	ret = 15;
	lomog_end();
}


int exec_menu(tParams * params) {

	ret = 0;
	
	tPanel background;
	panel_init(&background, lomog_get_width(), lomog_get_height(), 0, 0, FORMAT(WHITE, WHITE));
	background.present = 1;
	lomog_add_panel(&background);
	
	tPanel heading;
	panel_init(&heading, lomog_get_width(), 1, 0, 0, FORMAT(WHITE, WHITE));
	heading.present = 1;
	lomog_add_panel(&heading);
	
	tPanel buttonContainer;
	panel_init(&buttonContainer, lomog_get_width(), 3, 0, 1, FORMAT(WHITE, BLUE));
	buttonContainer.present = 1;
	lomog_add_panel(&buttonContainer);
	
	panel_init(&buttonsPanel, 18, 15, 1, 4, FORMAT(WHITE, WHITE));
	buttonsPanel.present = 0;
	mouse_listener_add(OUT, hide, &(buttonsPanel.listener));
	lomog_add_panel(&buttonsPanel);
	
	tButton manButton;
	button_init(&manButton, 10, 3, 5, 1, FORMAT(WHITE, BLUE), FORMAT(WHITE, RED), "man");
	lomog_add_button(&manButton);
	manButton.panel.present = 1;
	mouse_listener_add(ENTER, man_roll_over, &(manButton.panel.listener));
	
	manHelpButton.text = "help";
	lomog_add_button_st(&manHelpButton, 1, 4);
	manHelpButton.panel.present = 0;
	mouse_listener_add(L_CLICK, man_help_handler, &(manHelpButton.panel.listener));
	
	manManButton.text = "man";
	lomog_add_button_st(&manManButton, 10, 4);
	manManButton.panel.present = 0;
	mouse_listener_add(L_CLICK, man_man_handler, &(manManButton.panel.listener));
	
	manTColorButton.text = "t_color";
	lomog_add_button_st(&manTColorButton, 1, 7);
	manTColorButton.panel.present = 0;
	mouse_listener_add(L_CLICK, man_t_color_handler, &(manTColorButton.panel.listener));
	
	manBColorButton.text = "b_color";
	lomog_add_button_st(&manBColorButton, 10, 7);
	manBColorButton.panel.present = 0;
	mouse_listener_add(L_CLICK, man_b_color_handler, &(manBColorButton.panel.listener));
	
	manGetTimeButton.text = "gettime";
	lomog_add_button_st(&manGetTimeButton, 1, 10);
	manGetTimeButton.panel.present = 0;
	mouse_listener_add(L_CLICK, man_gettime_handler, &(manGetTimeButton.panel.listener));
	
	manSetTimeButton.text = "settime";
	lomog_add_button_st(&manSetTimeButton, 10, 10);
	manSetTimeButton.panel.present = 0;
	mouse_listener_add(L_CLICK, man_settime_handler, &(manSetTimeButton.panel.listener));
	
	manDateButton.text = "date";
	lomog_add_button_st(&manDateButton, 1, 13);
	manDateButton.panel.present = 0;
	mouse_listener_add(L_CLICK, man_date_handler, &(manDateButton.panel.listener));
	
	manSvscrButton.text = "svscr";
	lomog_add_button_st(&manSvscrButton, 10, 13);
	manSvscrButton.panel.present = 0;
	mouse_listener_add(L_CLICK, man_svscr_handler, &(manSvscrButton.panel.listener));
	
	manClearButton.text = "clear";
	lomog_add_button_st(&manClearButton, 1, 16);
	manClearButton.panel.present = 0;
	mouse_listener_add(L_CLICK, man_clear_handler, &(manClearButton.panel.listener));
	
	manDharmaButton.text = "dharma";
	lomog_add_button_st(&manDharmaButton, 10, 16);
	manDharmaButton.panel.present = 0;
	mouse_listener_add(L_CLICK, man_dharma_handler, &(manDharmaButton.panel.listener));
	
	tButton helpButton = {"help"};
	lomog_add_button_st(&helpButton, 20,1);
	helpButton.panel.present = 1;
	mouse_listener_add(L_CLICK, help_handler, &(helpButton.panel.listener));
	
	tButton fortuneButton = {"fortune"};
	lomog_add_button_st(&fortuneButton, 30,1);
	fortuneButton.panel.present = 1;
	mouse_listener_add(L_CLICK, fortune_handler, &(fortuneButton.panel.listener));
	
	tButton dateButton = {"date"};
	lomog_add_button_st(&dateButton, 40, 1);
	dateButton.panel.present = 1;
	mouse_listener_add(L_CLICK, date_handler, &(dateButton.panel.listener));
	
	tButton gettimeButton = {"gettime"};
	lomog_add_button_st(&gettimeButton, 50, 1);
	gettimeButton.panel.present = 1;
	mouse_listener_add(L_CLICK, gettime_handler, &(gettimeButton.panel.listener));
	
	tButton dharmaButton = {"dharma"};
	lomog_add_button_st(&dharmaButton, 60, 1);
	dharmaButton.panel.present = 1;
	mouse_listener_add(L_CLICK, dharma_handler, &(dharmaButton.panel.listener));
	
	tButton shellButton = {"RETURN"};
	lomog_add_button_st(&shellButton, 80 - 10, 24 - 3);
	shellButton.panel.present = 1;
	mouse_listener_add(L_CLICK, finish, &(shellButton.panel.listener));
	
	lomog_init();
	
	return ret;
}
