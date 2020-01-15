/**
 * Copyright 2020 Jesús Jiménez Sánchez
 */

#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <signal.h>
#include <ao/ao.h>
#include <mpg123.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include "../include/play.h"
#include "/home/pi/Documents/WiringPi/wiringPi/wiringPi.h"

#define true (1 == 1)
#define false (!true)

/* Buttons in wiringPi */
#define BUTTON_1 0
#define BUTTON_2 2
#define BUTTON_3 3
#define BUTTON_4 21
#define BUTTON_5 22
#define BUTTON_6 23
#define BUTTON_7 24
#define BUTTON_8 25

#define NUM_BUTTONS 8

/*
	const char * const
	immutable pointer to immutable char value
	-----------------------------------------
	Instruments
*/
const char * const BASS_DRUM = "bass_drum.mp3";
const char * const CLOSED_HI_HAT = "closed_hi_hat.mp3";
const char * const CRASH_CYMBAL = "crash_cymbal.mp3";
const char * const FLOOR_TOM = "floor_tom.mp3";
const char * const HIGH_TOM = "high_tom.mp3";
const char * const MID_TOM = "mid_tom.mp3";
const char * const OPEN_HI_HAT = "open_hi_hat.mp3";
const char * const RYDE_CYMBAL = "ryde_cymbal.mp3";
const char * const SNARE_DRUM = "snare_drum.mp3";

void intHandler(int dummy) {
    printf("\nExiting...\n");
	exit(EXIT_SUCCESS);
}

void PressToPlay(int instrument, int volume) {
	char *sound = (char *)malloc(sizeof(char) * 50);
	int can_play = true;

	if (volume >= 200 && volume < 400) {
		sound = strdup("sounds/volume/low");
	}
	else if (volume >= 400 && volume < 800) {
		strdup("sounds/");
	}
	else if (volume >= 800) {
		strdup("sounds/volume/high");
	}

	switch (instrument) {
		case 1:
			strcat(sound, SNARE_DRUM);
			break;
		case 2:
			strcat(sound, BASS_DRUM);
			break;
		case 3:
			strcat(sound, CLOSED_HI_HAT);
			break;
		case 4:
			strcat(sound, CRASH_CYMBAL);
			break;
		case 5:
			strcat(sound, RYDE_CYMBAL);
			break;
		case 6:
			strcat(sound, HIGH_TOM);
			break;
		case 7:
			strcat(sound, MID_TOM);
			break;
		case 8:
			strcat(sound, FLOOR_TOM);
			break;
		case 9:
			strcat(sound, CLOSED_HI_HAT);
			break;
		default:
			can_play = false;
			break;
	}

	if (can_play && fork() == 0) {
		play(sound);
	}
}

int readSerial() {
	int fd, n;
	char buf[64] = "temp text";
	char delim[] = ":";
	int instrument = 0;
	int volume = 0;
	struct termios toptions;

	/* open serial port */
	fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);

	/* wait for the Arduino to reboot */
	// usleep(3500000);

	/* get current serial port settings */
	tcgetattr(fd, &toptions);

	/* set 9600 baud both ways */
	cfsetispeed(&toptions, B9600);
	cfsetospeed(&toptions, B9600);

	/* 8 bits, no parity, no stop bits */
	toptions.c_cflag &= ~PARENB;
	toptions.c_cflag &= ~CSTOPB;
	toptions.c_cflag &= ~CSIZE;
	toptions.c_cflag |= CS8;

	/* Canonical mode */
	toptions.c_lflag |= ICANON;

	while (true) {
		/* commit the serial port settings */
		tcsetattr(fd, TCSANOW, &toptions);

		/* Send byte to trigger Arduino to send string back */
		write(fd, "0", 1);

		/* Receive string from Arduino */
		n = read(fd, buf, 64);

		/* insert terminating zero in the string */
		buf[n] = 0;

		char *part = strtok(buf, delim);
		instrument = atoi(part);

		part = strtok(NULL, delim);
		volume = atoi(part);

		printf("Buffer --> '%s'\n", buf);
		printf("Instrument: %d\n", instrument);
		printf("Volume: %d\n", volume);

		PressToPlay(instrument, volume);
	}
}

int main(int argc, char *argv[]) {
	signal(SIGINT, intHandler);
	readSerial();
}
