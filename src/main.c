/**
 * Copyright 2020 Jesús Jiménez Sánchez
 *
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

#define true (1 == 1)
#define false (!true)

void intHandler(int dummy) {
    printf("\nExiting...\n");
	exit(EXIT_SUCCESS);
}

void PressToPlay(int instrument, int volume) {
	char *sound = (char *)malloc(sizeof(char) * 50);
	int can_play = true;

	switch (instrument) {
		case 1:
			if (volume >= 200 && volume < 400) {
				sound = "sounds/volume/low/snare_drum.mp3";
			}
			else if (volume >= 400 && volume < 800) {
				sound = "sounds/snare_drum.mp3";
			}
			else if (volume >= 800) {
				sound = "sounds/volume/high/snare_drum.mp3";
			}
			else {
				/*
					In the case it returns a value less than 200,
					nothing should be played
				*/
				return;
			}

			break;
		case 2:
			if (volume >= 200 && volume < 400) {
				sound = "sounds/volume/low/bass_drum.mp3";
			}
			else if (volume >= 400 && volume < 800) {
				sound = "sounds/bass_drum.mp3";
			}
			else if (volume >= 800) {
				sound = "sounds/volume/high/bass_drum.mp3";
			}
			else {
				return;
			}
			
			break;
		case 3:
			if (volume >= 200 && volume < 400) {
				sound = "sounds/volume/low/closed_hi_hat.mp3";
			}
			else if (volume >= 400 && volume < 800) {
				sound = "sounds/closed_hi_hat.mp3";
			}
			else if (volume >= 800) {
				sound = "sounds/volume/high/closed_hi_hat.mp3";
			}
			else {
				return;
			}

			break;
		case 4:
			if (volume >= 200 && volume < 400) {
				sound = "sounds/volume/low/crash_cymbal.mp3";
			}
			else if (volume >= 400 && volume < 800) {
				sound = "sounds/crash_cymbal.mp3";
			}
			else if (volume >= 800) {
				sound = "sounds/volume/high/crash_cymbal.mp3";
			}
			else {
				return;
			}

			break;
		case 5:
			if (volume >= 200 && volume < 400) {
				sound = "sounds/volume/low/ryde_cymbal.mp3";
			}
			else if (volume >= 400 && volume < 800) {
				sound = "sounds/ryde_cymbal.mp3";
			}
			else if (volume >= 800) {
				sound = "sounds/volume/high/ryde_cymbal.mp3";
			}
			else {
				return;
			}

			break;
		case 6:
			if (volume >= 200 && volume < 400) {
				sound = "sounds/volume/low/high_tom.mp3";
			}
			else if (volume >= 400 && volume < 800) {
				sound = "sounds/high_tom.mp3";
			}
			else if (volume >= 800) {
				sound = "sounds/volume/high/high_tom.mp3";
			}
			else {
				return;
			}

			break;
		case 7:
			if (volume >= 200 && volume < 400) {
				sound = "sounds/volume/low/mid_tom.mp3";
			}
			else if (volume >= 400 && volume < 800) {
				sound = "sounds/mid_tom.mp3";
			}
			else if (volume >= 800) {
				sound = "sounds/volume/high/mid_tom.mp3";
			}
			else {
				return;
			}

			break;
		case 8:
			if (volume >= 200 && volume < 400) {
				sound = "sounds/volume/low/floor_tom.mp3";
			}
			else if (volume >= 400 && volume < 800) {
				sound = "sounds/floor_tom.mp3";
			}
			else if (volume >= 800) {
				sound = "sounds/volume/high/floor_tom.mp3";
			}
			else {
				return;
			}

			break;
		case 9:
			if (volume >= 200 && volume < 400) {
				sound = "sounds/volume/low/open_hi_hat.mp3";
			}
			else if (volume >= 400 && volume < 800) {
				sound = "sounds/open_hi_hat.mp3";
			}
			else if (volume >= 800) {
				sound = "sounds/volume/high/open_hi_hat.mp3";
			}
			else {
				return;
			}

			break;
		default:
			can_play = false;
			break;
	}

	if (can_play) {
		play(sound);
	}
}

void readSerial() {
	struct termios toptions;
	int fd, i;
	char buf[20] = {'\0'};
	const char delim[] = ":";
	int instrument = 0;
	int volume = 0;

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
		read(fd, buf, 20);

		// buf = removeFirstChar(buf, 10);

		for (i = 0; i < 20 || buf[i] == '\0'; i++) {
			if (buf[i] == '\n') {
				buf[i] = '\0';
				break;
			}
		}

		if (buf[0] == '\0'){
			continue;
		}

		char *part = strtok(buf, delim);
		instrument = atoi(part);

		part = strtok(NULL, delim);
		volume = atoi(part);

		// printf("Instrument: %d\n", instrument);
		// printf("Volume: %d\n", volume);

		if (instrument != 0 && volume != 0) {
			PressToPlay(instrument, volume);
		}
	}
}

int main(int argc, char *argv[]) {
	signal(SIGINT, intHandler);
	readSerial();
}
