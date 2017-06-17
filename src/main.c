#include <stdio.h>
#include "bcm8544.h"


void main(int argc, char* argv[]) {
	int i;
	bcm8544_init();
	clear_screen();
	for (i=1;i<argc;i++) {
		goto_xy(0,i - 1);
		write(argv[i]);
	}

}
