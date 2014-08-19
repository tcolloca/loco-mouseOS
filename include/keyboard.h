#ifndef _keyboard_
#define _keyboard_

#define READ_PORT		(0x60)

#define NUMBER			0
#define ROW1			1
#define ROW2			2
#define ROW3			3

#define XOR(x,y)		( !((x) & (y) ) & ( (x) | (y) ) )

#define ENTER			(0x1C)
#define BACKSPACE		(0x0E)
#define SPACE			(0x39)

#define CAPS_LOCK		(0x3A)
#define L_SHIFT			(0x2A)
#define R_SHIFT			(0x36)
#define IS_SHIFT(x)		( (x)==L_SHIFT | (x)==R_SHIFT )

#define	NUMBER_INIT		(0x02)
#define	NUMBER_END		(0x0D)

#define ROW1_INIT		(0x10)
#define ROW1_END		(0x1B)

#define ROW2_INIT		(0x1E)
#define ROW2_END		(0x29)

#define ROW3_INIT		(0x2C)
#define ROW3_END		(0x35)

#define	NUMBER_INIT_ES	(0x02)
#define	NUMBER_END_ES	(0x0C)

#define ROW1_INIT_ES	(0x10)
#define ROW1_END_ES		(0x1B)

#define ROW2_INIT_ES	(0x1E)
#define ROW2_END_ES		(0x26)

#define ROW3_INIT_ES	(0x2C)
#define ROW3_END_ES		(0x35)

#define BIT(x)			(1 << ((x)-1))
#define RELEASED		BIT(8)
#define IS_RELEASED(x)	((x) & RELEASED)
#define IS_PRESSED(x)	(!(IS_RELEASED(x)))

void keyboard_handler(void);

static char scancode_to_char(unsigned int scancode);

static int is_mayus();

static int is_shifted();

static int classify(unsigned int scancode);

#endif
