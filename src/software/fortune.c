#include "../../include/defs.h"
#include "../../include/stdlib.h"
#include "../../include/time.h"

static char quote1[] = "\n\tThe greatest risk is not taking one.\n";
static char quote2[] = "\n\tNow is the time to try something new.\n";
static char quote3[] = "\n\tYour succeess will astonish everyone.\n";
static char quote4[] = "\n\tTell them what you really think. Otherwise, nothing will change.\n";
static char quote5[] = "\n\tThe time is right to make new friends.\n";
static char quote6[] = "\n\tBe a generous friend and a fair enemy.\n";
static char quote7[] = "\n\tUse your talents. That's what they are intended for.\n";
static char quote8[] = "\n\tYour dream will come true when you least expect it.\n";
static char quote9[] = "\n\tYour ability to pick a winner will bring you success.\n";
static char quote10[] = "\n\tYou have a great capability to break cookies - use it wisely!\n";
static char quote11[] = "\n\tThe best is yet to come.\n";
static char quote12[] = "\n\tBe patient: in time, even an egg will walk.\n";
static char quote13[] = "\n\tEat something you never tried before.\n";
static char quote14[] = "\n\tA good time to finish up old tasks.\n";

static char * quotes[] = {quote1,quote2,quote3,quote4,quote5,quote6,quote7,quote8,quote9,quote10,quote11,quote12,quote13,quote14};



int exec_fortune(tParams * params) {
	
	srand(time());
	int random = rand();

	printf("%s\n",quotes[random%14]);
	
	return 0;
}
