/**
 * Copyright 2020 Jesús Jiménez Sánchez
 *
 */

#include "../include/shared.h"

void parseInstruments(char *buf) {
	struct read_intrument r_snare, r_hi_hat, r_crash, r_high_tom, r_floor_tom, r_bass;
	const char delim[] = ":";

	// Separate instrument and string in string
	char *token = strtok(buf, delim);
	r_snare.id = atoi(token);

	token = strtok(NULL, delim);
	r_snare.volume = atoi(token);

	token = strtok(NULL, delim);
	r_hi_hat.id = atoi(token);

	token = strtok(NULL, delim);
	r_hi_hat.volume = atoi(token);

	token = strtok(NULL, delim);
	r_crash.id = atoi(token);

	token = strtok(NULL, delim);
	r_crash.volume = atoi(token);

	token = strtok(NULL, delim);
	r_high_tom.id = atoi(token);

	token = strtok(NULL, delim);
	r_high_tom.volume = atoi(token);

	token = strtok(NULL, delim);
	r_floor_tom.id = atoi(token);

	token = strtok(NULL, delim);
	r_floor_tom.volume = atoi(token);

	token = strtok(NULL, delim);
	r_bass.id = atoi(token);

	token = strtok(NULL, delim);
	r_bass.volume = atoi(token);

	if (r_snare.volume > 200 && fork() == 0) {
		PressToPlay(r_snare);
	}

	if (r_hi_hat.volume > 200 && fork() == 0) {
		PressToPlay(r_hi_hat);
	}

	if (r_crash.volume > 200 && fork() == 0) {
		PressToPlay(r_crash);
	}

	if (r_high_tom.volume > 200 && fork() == 0) {
		PressToPlay(r_high_tom);
	}

	if (r_floor_tom.volume > 200 && fork() == 0) {
		PressToPlay(r_floor_tom);
	}

	if (r_bass.volume > 200 && fork() == 0) {
		PressToPlay(r_bass);
	}
}

void readSerial() {
	struct termios toptions;
	int fd, i, j;
	char buf[60] = {'\0'};

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
		read(fd, buf, 60);

		if (buf[0] == '0' || buf[0] == '\0'){
			continue;
		}

		for (i = 0; i < 60; i++) {
			if (buf[i] == '\n') {
				buf[i] = '\0';
				break;
			}

			if (buf[i] == '\000'){
				for (j = i; j < 60; j++) {
					if (buf[j] == '\n') {
						break;
					}

					buf[j] = buf[j + 1];
				}
			}
		}

		parseInstruments(buf);
	}
}
