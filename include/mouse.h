#ifndef _mouse_
#define _mouse_

#define INITIAL_PACKET	(0x41)

#define I_PORT		(0x64)
#define R_PORT 		(0x60)

#define LEFT	(0x01)
#define RIGHT	(0x02)
#define MIDDLE	(0x04)

#define X_SIGN	(0x10)
#define Y_SIGN	(0x20)

#define READ	0
#define WRITE	1
#define ACK	2

#define WIDTH	80
#define	HEIGHT	25

#define X_SENS	8
#define Y_SENS	3

typedef struct {
	int left, middle, right;
}tMouse;

void mouse_init();

static void mouse_config();

void mouse_handler(unsigned char b);

static void mouse_update_x(char delta);

static void mouse_update_y(char delta);

static void mouse_update_acum_x(char delta);

static void mouse_update_position();

static int mouse_r_clicked();

static int mouse_r_release();

static int mouse_l_clicked();

static int mouse_l_release();

static int mouse_m_clicked();

static int mouse_m_release();

static int mouse_moved();

static int mouse_stand();

static void mouse_I_write(unsigned int value);

static void mouse_R_write(unsigned int value);

static unsigned int mouse_read();

static unsigned int mouse_I_read();

static void mouse_send_command(unsigned int command);

static void mouse_wait(int type);

#endif
