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

const char * const sounds_list[24][3] = {
	{
		"sounds/volume/low/snare_drum.mp3",
		"sounds/snare_drum.mp3",
		"sounds/volume/high/snare_drum.mp3",
	},
	{
		"sounds/volume/low/closed_hi_hat.mp3",
		"sounds/closed_hi_hat.mp3",
		"sounds/volume/high/closed_hi_hat.mp3",
	},
	{
		"sounds/volume/low/crash_cymbal.mp3",
		"sounds/crash_cymbal.mp3",
		"sounds/volume/high/crash_cymbal.mp3",
	},
	{
		"sounds/volume/low/high_tom.mp3",
		"sounds/high_tom.mp3",
		"sounds/volume/high/high_tom.mp3",
	},
	{
		"sounds/volume/low/floor_tom.mp3",
		"sounds/floor_tom.mp3",
		"sounds/volume/high/floor_tom.mp3",
	},
	{
		"sounds/volume/low/bass_drum.mp3",
		"sounds/bass_drum.mp3",
		"sounds/volume/high/bass_drum.mp3",
	},
	{
		"sounds/volume/low/ryde_cymbal.mp3",
		"sounds/ryde_cymbal.mp3",
		"sounds/volume/high/ryde_cymbal.mp3",
	},
	{
		"sounds/volume/low/mid_tom.mp3",
		"sounds/mid_tom.mp3",
		"sounds/volume/high/mid_tom.mp3",
	},
	{
		"sounds/volume/low/open_hi_hat.mp3",
		"sounds/open_hi_hat.mp3",
		"sounds/volume/high/open_hi_hat.mp3",
	},
	{
		"",
		"sounds/combined/closed_hh_and_snare.mp3",
		""
	},
	{
		"",
		"sounds/combined/crash_and_snare.mp3",
		""
	},
	{
		"",
		"sounds/combined/snare_and_high_tom.mp3",
		""
	},
	{
		"",
		"sounds/combined/snare_and_floor_tom.mp3",
		""
	},
	{
		"",
		"sounds/combined/bass_and_snare.mp3",
		""
	},
	{
		"",
		"sounds/combined/closed_hh_and_crash.mp3",
		""
	},
	{
		"",
		"sounds/combined/closed_hh_and_high_tom.mp3",
		""
	},
	{
		"",
		"sounds/combined/closed_hh_and_floor_tom.mp3",
		""
	},
	{
		"",
		"sounds/combined/bass_and_closed_hh.mp3",
		""
	},
	{
		"",
		"sounds/combined/crash_and_high_tom.mp3",
		""
	},
	{
		"",
		"sounds/combined/crash_and_floor_tom.mp3",
		""
	},
	{
		"",
		"sounds/combined/bass_and_crash.mp3",
		""
	},
	{
		"",
		"sounds/combined/high_and_floor_tom.mp3",
		""
	},
	{
		"",
		"sounds/combined/bass_and_high.mp3",
		""
	},
	{
		"",
		"sounds/combined/bass_and_floor.mp3",
		""
	}
};

void intHandler(int dummy) {
	exit(EXIT_SUCCESS);
}

void PressToPlay(int instrument, int volume) {
	char *sound = (char *)malloc(sizeof(char) * 50);
	int can_play = true;
	int chosen_volume = 0;

	if (volume >= 200 && volume < 400) {
		chosen_volume = 0;
	}
	else if (volume >= 400 && volume < 800) {
		chosen_volume = 1;
	}
	else if (volume >= 800) {
		chosen_volume = 2;
	}
	else {
		/*
			In the case it returns a value less than 200,
			nothing should be played
		*/
		kill(getpid(), SIGINT);	// Exit process
	}

	if (instrument < 1 || instrument > 25) {
		can_play = false;
	}

	// sound = sounds_list[instrument][chosen_volume];
	sound = (char *)sounds_list[instrument - 1][chosen_volume];

	if (can_play) {
		play(sound);
	}

	kill(getpid(), SIGINT);	// Exit process
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

		if (buf[0] == '0' || buf[0] == '\0'){
			continue;
		}

		for (i = 0; i < 20; i++) {
			if (buf[i] == '\n') {
				buf[i] = '\0';
				break;
			}

			if (buf[i] == '\0'){
				break;
			}
		}

		// Separate instrument and string in string
		char *part = strtok(buf, delim);
		instrument = atoi(part);

		part = strtok(NULL, delim);
		volume = atoi(part);

		if (instrument != 0 && volume != 0 && fork() == 0) {
			PressToPlay(instrument, volume);
		}
	}
}

int main(int argc, char *argv[]) {
	signal(SIGINT, intHandler);
	readSerial();
}
