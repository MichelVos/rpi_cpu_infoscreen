#include <stdio.h>
#include <wiringPi.h>

#define CLK 0
#define DIN 1
#define DC 2
#define CE 3
#define RST 4
#define BACKLIGHT_CONTROL 7

void set_command(int value) {
	digitalWrite(DC, value ? 1 : 0);
}

void set_chip_select(int value) {
	digitalWrite(CE, value ? 1 : 0);
}

void set_clock(int value) {
	digitalWrite(CLK, value ? 1 : 0);
}

void set_data(int value) {
	digitalWrite(DIN, value ? 1 : 0);
}

void set_reset(int value) {
	digitalWrite(RST, value ? 1 : 0);

}

void clock_out_byte(unsigned char byte) {
	int i;
	set_clock(0); // make sure clock is 0
	set_chip_select(0);
	for (i = 0; i < 8; i++) {
		set_data(byte & 0x80);
		set_clock(1);
		set_clock(0);
		byte <<= 1;
	}
	set_chip_select(1);
}

void send_byte(unsigned char byte) {
	set_command(1);
	clock_out_byte(byte);
}

void send_command_byte(unsigned char byte) {
	set_command(0);
	clock_out_byte(byte);
}

void send_data(unsigned char* data, int data_length) {
	int j;
	unsigned char byte;
	set_command(1);
	set_clock(0); // make sure clock is 0
	set_chip_select(0);
	while (data_length--) {
		byte = *data++;
		for (j = 0; j < 8; j++) {
			set_data(byte & 0x80);
			set_clock(1);
			set_clock(0);
			byte <<= 1;
		}
	}
	set_chip_select(1);
}

void low_initialise() {
        if (wiringPiSetup () == -1) {
		printf("Init failed\n");
		return;
	}
	pinMode(CE, OUTPUT);
	pinMode(RST, OUTPUT);
	pinMode(DC, OUTPUT);
	pinMode(DIN, OUTPUT);
	pinMode(CLK, OUTPUT);
	set_reset(0);
	set_reset(1);
	send_command_byte(0x21);	  // LCD Extended Commands.
	send_command_byte(0xB1);	  // Set LCD Vop (Contrast).
	send_command_byte(0x04);	  // Set Temp coefficent. //0x04
	send_command_byte(0x14);	  // LCD bias mode 1:48. //0x13
	send_command_byte(0x20);	  // LCD Basic Commands
	send_command_byte(0x0C);	  // LCD in normal mode.
}

