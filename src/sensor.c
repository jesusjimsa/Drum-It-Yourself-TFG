/*********************************************************************
 *********************************************************************
 *********************** Jesús Jiménez Sánchez ***********************
 *********************************************************************
*********************************************************************/

#include <ao/ao.h>
#include <mpg123.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "../include/play.h"
#include </home/pi/Documents/WiringPi/wiringPi/wiringPi.h>

#define true (1 == 1)
#define false (!true)

void PressToPlay(int instrument, int volume) {
	char *sound = (char *)malloc(sizeof(char) * 50);
	int can_play = false;
	int from;

	if (volume >= 200 && volume < 400) {
		strcpy(sound, "sounds/volume/low");
	}
	else if (volume >= 400 && volume < 800) {
		strcpy(sound, "sounds/");
	}
	else if (volume >= 800) {
		strcpy(sound, "sounds/volume/high");
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
	}

	if (fork() == 0) {
		play(sound);
	}
}

char *getSerial(){
	char *value = (char *)malloc(sizeof(char) * 15);

	return value;
}

int main(int argc, char *argv[]) {
	char *serial_output = (char *)malloc(sizeof(char) * 15);
	int instrument = 0;
	int volume = 0;

	while (true) {
		serial_output = getSerial();

		/* 
		TODO:
			- Separate serial output and save instrument and volume
				* Output will be like:
					Intrument:Volume
					1:423
		*/

		PressToPlay(instrument, volume);
	}
}
