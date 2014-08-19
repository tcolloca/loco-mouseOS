#include "../../include/stdio.h"
#include "../../include/string.h"
#include "../../include/time.h"
#include "../../include/timertick_listener.h"
#include "../../include/timertick_event.h"
#include "../../include/beep.h"
#include "../../include/error.h"
#include "../../include/ascii.h"

#define SFIRST_BEEP	2
#define SSECOND_BEEP	10
#define STHIRD_BEEP	20
#define SFOURTH_BEEP	25
#define FIRST_BEEP	6240
#define SECOND_BEEP 	6420 
#define THIRD_BEEP	6470
#define FOURTH_BEEP	6480

static int numbers[6] = {4, 8, 15, 16, 23, 42};
static int initTime = 0;
static int dead;
static tTimertickListener ttListener;
static initFlag = 0;

static int empty_buffer() {
	int flag = 0;	
	char c;
	while( ( c = getchar() ) != '\n' ) {
		flag = 1;
	}
	return flag;
}

static int onSecond(double sec) {
	return (time_current_millis() - initTime) % (int)(sec*1000) == 0;
}

static void speed_up() {
	double elapsedTime = (time_current_millis() - initTime)/1000;
	if( SFIRST_BEEP <= elapsedTime && elapsedTime < SSECOND_BEEP ) { 
		if( onSecond(2) ) {
			beep_Dsharp5(0.1);	
		}
	}
	else if( SSECOND_BEEP <= elapsedTime && elapsedTime < STHIRD_BEEP ) { 
		if( onSecond(2) ) {
			beep_Asharp5(1);	
		}
	}
	else if( STHIRD_BEEP <= elapsedTime && elapsedTime < SFOURTH_BEEP ) { 
		if( onSecond(1.1) ) {
			beep_Asharp5(0.6);	
		}
	}
	else if( SFOURTH_BEEP <= elapsedTime ) { 
		if( !dead )
			dead = 1;
		/*if( onSecond(0.2) )
			printf("System Failure\n");*/		
		if( onSecond(1.1) ) {
			beep(2000, 0.6);		 	
		}
	}
}

static void counter() {
	double elapsedTime = (time_current_millis() - initTime)/1000;
	if( FIRST_BEEP <= elapsedTime && elapsedTime < SECOND_BEEP ) { 
		if( onSecond(2) ) {
			beep_Dsharp5(0.1);	
		}
	}
	else if( SECOND_BEEP <= elapsedTime && elapsedTime < THIRD_BEEP ) { 
		if( onSecond(2) ) {
			beep_Asharp5(1);	
		}
	}
	else if( THIRD_BEEP <= elapsedTime && elapsedTime < FOURTH_BEEP ) { 
		if( onSecond(1.1) ) {
			beep_Asharp5(0.6);	
		}
	}
	else if( FOURTH_BEEP <= elapsedTime ) {
		if( !dead )
			dead = 1; 
		if( onSecond(0.2) )
			printf("System Failure");			
		if( onSecond(1.1) ) {
			beep(2000, 0.8);		 	
		}
	}
} 


static void clean(char * s, int count) {
	while( count > 0 ) {
		*(s+count - 1) = 0;
		count--;
	}
}

static void validateNumbers(int nums[]) {
	int i, flag = 1;
	for( i = 0; i < 6 && flag; i++ ) {
		if( nums[i] != numbers[i] )
			flag = 0;
	}
	if( flag ) {
		initTime = time_current_millis();
		if( dead ) {
			dead = 0;
		}
	}
}

static int isQuit(char * s) {
	if( !strcmp(s, "quit") ) {
		timertick_listener_disable(&ttListener);
		printf("%c", ASCII_T_COLOR_WHITE);
		printf("%c", ASCII_B_COLOR_BLACK);
		dead = 0;
		return 1;
	}
	return 0;
}

static int isSpeedUp(char * s) {
	return !strcmp(s, "speedup") && (initTime = time_current_millis());
}

static int isSlowDown(char * s) {
	if( !dead )
		return !strcmp(s, "slowdown");
}

static void init() {
	if( !initFlag ) {
		timertick_listener_init(&ttListener, counter);
		timertick_event_add(&ttListener);
		initFlag = 1;		
	}
	printf("%c", ASCII_T_COLOR_GREEN);
	printf("%c", ASCII_B_COLOR_BLACK);
	timertick_listener_change_handler(&ttListener, counter);
	timertick_listener_enable(&ttListener);
	initTime = time_current_millis(); 	

	printf("\n\n Welcome to the Swan Station! Your role is to press the numbers 4 8 15 16 23 42 every 108 minutes to save the world. If you are tired, and want a replacement,  just enter 'quit'.\n\n");
}

int exec_dharma(tParams * params) {
	if(params->args_amount != 1) {
		error_set(INVALID_ENTRY, (params->args)[0]);
		return 1;
	}	
	
	init();	

	while( 1 ) {	
		int read, flag = 1, nums[6];
		char c, str[16], command[16];

		printf(" >: ");
		
		clean(str, 16);
		clean(command, 16);
		fgets(str, 16, stdin);
		read = sscanf(str, "%s", command);
		
		if( read == 1 ) {
			if( isQuit(command) )
				break;
			else if( isSpeedUp(command) ) {
				timertick_listener_change_handler(&ttListener, speed_up);
				continue;
			}	
			else if( isSlowDown(command) ) {
				timertick_listener_change_handler(&ttListener, counter);
				continue;
			}	
		}

		read = sscanf(str, "%d %d %d %d %d %d", nums, nums+1, nums+2, nums+3, nums+4, nums+5);
		if( str[14] != 0 )
			flag = empty_buffer();
		
		if( read == 6 && !flag ) {
			validateNumbers(nums);
		}	
	}
	return 0;
}	
