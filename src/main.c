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
#include "../include/play.h"
#include </home/pi/Documents/WiringPi/wiringPi/wiringPi.h>

#define true (1 == 1)
#define false (!true)

/* Buttons in wiringPi */
#define BUTTON_1 0
#define BUTTON_2 2
#define BUTTON_3 3

void ChooseSound(int selected){
	switch (selected){
		case 1:
			play("sounds/bass_drum.mp3");
			break;
		case 2:
			play("sounds/closed_hi_hat.mp3");
			break;
		case 3:
			play("sounds/crash_cymbal.mp3");
			break;
		case 4:
			play("sounds/floor_tom.mp3");
			break;
		case 5:
			play("sounds/high_tom.mp3");
			break;
		case 6:
			play("sounds/mid_tom.mp3");
			break;
		case 7:
			play("sounds/open_hi_hat.mp3");
			break;
		case 8:
			play("sounds/ryde_cymbal.mp3");
			break;
		case 9:
			play("sounds/snare_drum.mp3");
			break;
		case 10:
			play("sounds/combined/bass_and_closed_hh.mp3");
			break;
		case 11:
			play("sounds/combined/bass_and_open_hh.mp3");
			break;
		case 12:
			play("sounds/combined/bass_and_snare.mp3");
			break;
		case 13:
			play("sounds/combined/closed_hh_and_snare.mp3");
			break;
		case 14:
			play("sounds/combined/crash_and_snare.mp3");
			break;
		case 15:
			play("sounds/combined/bass_and_floor.mp3");
			break;
		case 16:
			play("sounds/combined/bass_and_high.mp3");
			break;
		case 17:
			play("sounds/combined/crash_and_ryde.mp3");
			break;
		case 18:
			play("sounds/combined/high_and_floor_tom.mp3");
			break;
		case 19:
			play("sounds/combined/high_and_mid_tom.mp3");
			break;
		case 20:
			play("sounds/combined/mid_and_floor_tom.mp3");
			break;
		case 21:
			play("sounds/combined/open_hh_and_snare.mp3");
			break;
		case 22:
			play("sounds/combined/snare_and_floor_tom.mp3");
			break;
		case 23:
			play("sounds/combined/snare_and_high_tom.mp3");
			break;
		case 24:
			play("sounds/combined/snare_and_mid_tom.mp3");
			break;
		case 25:
			play("sounds/combined/snare_and_ryde.mp3");
			break;
		case 0:
			printf("Bye bye!\n");
			break;	
		default:
			printf("You have to write a number between 0 and 25 (0 to exit)\n");
			break;
	}

	kill(getpid(),SIGINT);
}

void PlayAndDie(char *sound){
	play(*sound);
	delay(10);
	kill(getpid(),SIGINT);
}

void PressToPlay(){
	char *sound = (char *)malloc(sizeof(char) * 50);

	if (digitalRead(BUTTON_1) == 1) {
		sound = "sounds/bass_drum.mp3";
	} else if (digitalRead(BUTTON_2) == 1) {
		sound = "sounds/snare_drum.mp3";
	} else if (digitalRead(BUTTON_3) == 1) {
		sound = "sounds/ryde_cymbal.mp3";
	}

	if(fork() == 0){
		PlayAndDie(*sound);
	}

	//free(sound);
}

int main(int argc, char *argv[]) {
	// int selected = 1;

	wiringPiSetup();

	pinMode(BUTTON_1, INPUT);
	pinMode(BUTTON_2, INPUT);
	pinMode(BUTTON_3, INPUT);

	while (true){
		PressToPlay();
	}
}
