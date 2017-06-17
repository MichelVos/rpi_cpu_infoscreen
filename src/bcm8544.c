#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "low.h"
#include "charset.h"

#define SIZE_X 84
#define SIZE_Y 6

void bcm8544_init() {
	low_initialise();
}


void goto_xy(int x, int y) {
	send_command_byte(0x40 + y);
	send_command_byte(0x80 + x * 6);
}

void write(char *message) {
	while (*message) {
		send_data(charSet7x8[*message - CHARSET_OFFSET], 6);
		message++;
	}
}

void write_at(int x, int y, char *message) {
	goto_xy(x, y);
	write(message);
}

void clear_screen() {
	int y;
	unsigned char *data;
	data = (unsigned char*) malloc(SIZE_X);
	memset((void*) data, 0, SIZE_X);
	for (y = 0; y < SIZE_Y; y++) {
		goto_xy(0, y);
		send_data(data, SIZE_X);
	}
	free(data);
}

