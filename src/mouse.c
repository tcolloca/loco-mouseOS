#include "../include/mouse.h"
#include "../include/kasm.h"
#include "../include/mouse_event.h"

static tMouse mouse;
static tMouseEvent me;

static unsigned int mouse_bytes[3];
static volatile int current_byte = 0;

static int acum_x = 0;
static int acum_y = 0;

void mouse_init() {
	mouse.left = 0;
	mouse.middle = 0;
	mouse.right = 0;
	
	me.mouse_x = 0;
	me.mouse_y = 0;
	
	mouse_config();
}

static void mouse_config() {
	
	unsigned int status;
	//it is recommended to disable "automatic packet streaming mode" while
	//"reprogramming" the mouse. To do this send command 0xF5 to mouse
	mouse_send_command(0xF5); // disable automatic packet streaming mode
	
	mouse_I_write(0xA8); //If bit 5 = 1, enable PS/2
	
	mouse_I_write(0x20); //Request compaq status
	
	status = mouse_read();
	status = status | 0x02; //enable PS/2 first and second ports interrupt
	mouse_I_write(0x60);
	mouse_R_write(status); //set config

	//mouse_send_command(0xFF); //reset mouse
	mouse_send_command(0xF6); //set default settings
	mouse_send_command(0xF4); //enable automatic package streaming
}

void mouse_handler(unsigned char b) {
	
	//if bit 3 is 0 the byte is out of place
	if(current_byte == 0 && ( b & 0x08 )==0) {
		return;
	}
	
	//stores mouse packet 
	mouse_bytes[current_byte++] = b;
		
	if(current_byte >= 3) {
	
		current_byte = 0;

		mouse_update_position();
		
		if(mouse_moved()) {
			if(mouse.left) {
				mouse_event_shoot(DRAG, &me);
				me.additional_data[1] = DRAG;
			} else {
				mouse_event_shoot(MOVE, &me);
				me.additional_data[1] = MOVE;
			}
		} else {
			if(mouse_l_clicked()) {
				mouse.left = 1;
				me.additional_data[1] = L_CLICK;
				mouse_event_shoot(L_CLICK, &me);
			}
			if(mouse_l_release()) {
				mouse.left = 0;
				me.additional_data[1] = L_RELEASE;
				mouse_event_shoot(L_RELEASE, &me);
			}
			if(mouse_r_clicked()) {
				mouse.right = 1;
				me.additional_data[1] = R_CLICK;
				mouse_event_shoot(R_CLICK, &me);
			}
			if(mouse_r_release()) {
				mouse.right = 0;
				me.additional_data[1] = R_RELEASE;
				mouse_event_shoot(R_RELEASE, &me);
			}
			if(mouse_m_clicked()) {
				mouse.middle = 1;
				me.additional_data[1] = M_CLICK;
				mouse_event_shoot(M_CLICK, &me);
			}
			if(mouse_m_release()) {
				mouse.middle = 0;
				me.additional_data[1] = M_RELEASE;
				mouse_event_shoot(M_RELEASE, &me);
			}
		}
	}
}

static void mouse_update_x(char delta) {
	if(delta > 0) {
		if(me.mouse_x + delta >= WIDTH) {
			me.mouse_x = WIDTH-1;
		} else {
			me.mouse_x += delta;
		}
	} else if(delta < 0) {
		if(me.mouse_x + delta < 0) {
			me.mouse_x = 0;
		} else {
			me.mouse_x += delta;
		}
	}
}

static void mouse_update_y(char delta) {
	if(delta < 0) {
		if(me.mouse_y - delta >= HEIGHT) {
			me.mouse_y = HEIGHT-1;
		} else {
			me.mouse_y -= delta;
		}
	} else if(delta > 0) {
		if(me.mouse_y - delta < 0) {
			me.mouse_y = 0;
		} else {
			me.mouse_y -= delta;
		}
	}
}

static void mouse_update_acum_x(char delta) {
	if(delta > 0) {
		if(acum_x + delta >= X_SENS) {
			mouse_update_x(1);
			acum_x = 0;
		} else {
			acum_x += delta;
		}
	} else if(delta < 0) {
		if(acum_x + delta <= -X_SENS) {
			mouse_update_x(-1);
			acum_x = 0;
		} else {
			acum_x += delta;
		}
	}
}

static void mouse_update_acum_y(char delta) {
	if(delta < 0) {
		if(acum_y - delta >= Y_SENS) {
			mouse_update_y(-1);
			acum_y = 0;
		} else {
			acum_y -= delta;
		}
	} else if(delta > 0) {
		if(acum_y - delta <= -Y_SENS) {
			mouse_update_y(1);
			acum_y = 0;
		} else {
			acum_y -= delta;
		}
	}
}

static void mouse_update_position() {
	char delta_x = (signed char)mouse_bytes[1];
	char delta_y = (signed char)mouse_bytes[2];
	
	mouse_update_acum_x(delta_x);
	mouse_update_acum_y(delta_y);
}

static int mouse_r_clicked() {
	return ((mouse_bytes[0] & RIGHT) && !mouse.right);
}
static int mouse_r_release() {
	return (!(mouse_bytes[0] & RIGHT) && mouse.right);
}
static int mouse_l_clicked() {
	return ((mouse_bytes[0] & LEFT) && !mouse.left);
}
static int mouse_l_release() {
	return (!(mouse_bytes[0] & LEFT) && mouse.left);
}
static int mouse_m_clicked() {
	return ((mouse_bytes[0] & MIDDLE) && !mouse.middle);
}
static int mouse_m_release() {
	return (!(mouse_bytes[0] & MIDDLE) && mouse.middle);
}

static int mouse_moved() {
	return !mouse_stand();
}

static int mouse_stand() {
	return ( mouse_bytes[1] == 0 && mouse_bytes[2] == 0 );
}


static void mouse_I_write(unsigned int value) {
	mouse_wait(WRITE);
	_outb(I_PORT, value);
}

static void mouse_R_write(unsigned int value) {
	mouse_wait(WRITE);
	_outb(R_PORT, value);
}

static unsigned int mouse_read() {
	mouse_wait(READ);
	return _inb(R_PORT);
}

static unsigned int mouse_I_read() {
	mouse_wait(READ);
	return _inb(I_PORT);
}

static void mouse_send_command(unsigned int command) {

	//Aviso que voy a mandar un comando
	mouse_I_write(0xD4);
	
	//Mando el comando
	mouse_R_write(command);
	
	//Espero el acknowledge
	mouse_wait(ACK);
}

static void mouse_wait(int type) {
	
	int time_out = 100000;
	
	while(time_out >= 0) {
		if(type == READ) {			
			if( (_inb(I_PORT) & 0x01) == 1 ) {break;}		
		} else if (type == WRITE) {
			if( (_inb(I_PORT) & 0x02) == 0 ) {break;}
		} else if (type == ACK) {
			if( mouse_read() == 0xFA ) {break;}
		} else {
			break;
		}
		
		time_out--;
	}
}




