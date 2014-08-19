#include "../include/lomog.h"
#include "../include/syscall.h"
#include "../include/defs.h"
#include "../include/string.h"

static int width = 80;
static int height = 25;

int lomog_get_width() {
	return width;
}

int lomog_get_height() {
	return height;
}

//Esta es la ultima funcion que debe llamarse antes de arrancar la interfaz grafica
void lomog_init() {
	//lomog_request(LOMOG_INIT, NULL) se encarga de hacer desaparecer el panel de HEADING y de CONSOLE y dibujar el resto de paneles
	//que esten activados.
	lomog_request(LOMOG_INIT, NULL, NULL);
}

void lomog_draw_string(tString * string, int x, int y, unsigned int format) {

	//TODO: Hay un bug de 1 pixel cuando el cursor sale del boton del string

	int length = strlen(string->text);
	button_init( &(string->button), length + 1, 1, x, y, format, format, string->text);
	string->button.panel.present = 1;
	lomog_add_button(&(string->button));
}

void lomog_add_button(tButton * button) {
	lomog_request(LOMOG_ADD_B, (void *)button, NULL);
}

void lomog_add_button_st(tButton * button, int x, int y) {
	int length = strlen(button->text);
	button_init( button, 9, 3, x, y, FORMAT(WHITE, BLUE), FORMAT(WHITE, LIGHT_BLUE), button->text );
	lomog_add_button(button);
}

void lomog_add_panel(tPanel * panel) {
	lomog_request(LOMOG_ADD_P, (void *)panel, NULL);
}

void lomog_update() {
	lomog_request(LOMOG_UPDATE, NULL, NULL);
}


void lomog_end() {
	lomog_request(LOMOG_END, NULL, NULL);
}

int lomog_request(int operation, void * component, void * component2) {
	return _syscall(VISUAL, operation, (int)component, (int)component2);
}
