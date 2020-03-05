/**
 * Copyright 2020 Jesús Jiménez Sánchez
 * 
 */

#include "../include/shared.h"

void parseInstruments(char *buf) {
	int vol_snare, vol_hi_hat, vol_crash, vol_high_tom, vol_floor_tom, vol_bass;
	int snare, hi_hat, crash, high_tom, floor_tom, bass;
	const char delim[] = ":";

	snare = 0;
	hi_hat = 0;
	crash = 0;
	high_tom = 0;
	floor_tom = 0;
	bass = 0;

	vol_snare = 0;
	vol_hi_hat = 0;
	vol_crash = 0;
	vol_high_tom = 0;
	vol_floor_tom = 0;
	vol_bass = 0;

	// Separate instrument and string in string
	char *token = strtok(buf, delim);
	snare = atoi(token);

	token = strtok(NULL, delim);
	vol_snare = atoi(token);

	token = strtok(NULL, delim);
	hi_hat = atoi(token);

	token = strtok(NULL, delim);
	vol_hi_hat = atoi(token);

	token = strtok(NULL, delim);
	crash = atoi(token);

	token = strtok(NULL, delim);
	vol_crash = atoi(token);

	token = strtok(NULL, delim);
	high_tom = atoi(token);

	token = strtok(NULL, delim);
	vol_high_tom = atoi(token);

	token = strtok(NULL, delim);
	floor_tom = atoi(token);

	token = strtok(NULL, delim);
	vol_floor_tom = atoi(token);

	token = strtok(NULL, delim);
	bass = atoi(token);

	token = strtok(NULL, delim);
	vol_bass = atoi(token);

	if (vol_snare > 200 && fork() == 0) {
		PressToPlay(snare, vol_snare);
	}

	if (vol_hi_hat > 200 && fork() == 0) {
		PressToPlay(hi_hat, vol_hi_hat);
	}

	if (vol_crash > 200 && fork() == 0) {
		PressToPlay(crash, vol_crash);
	}

	if (vol_high_tom > 200 && fork() == 0) {
		PressToPlay(high_tom, vol_high_tom);
	}

	if (vol_floor_tom > 200 && fork() == 0) {
		PressToPlay(floor_tom, vol_floor_tom);
	}

	if (vol_bass > 200 && fork() == 0) {
		PressToPlay(bass, vol_bass);
	}
}

void readSerial() {
	struct termios toptions;
	int fd, i;
	char buf[40] = {'\0'};

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

	/* commit the serial port settings */
	tcsetattr(fd, TCSANOW, &toptions);

	/* Send byte to trigger Arduino to send string back */
	write(fd, "0", 1);

	while (true) {
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

		parseInstruments(buf);
	}
}
