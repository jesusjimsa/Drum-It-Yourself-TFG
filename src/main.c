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
#include "../include/play.h"
#include </home/pi/Documents/WiringPi/wiringPi/wiringPi.h>

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

const unsigned int NUM_BUTTONS = 8;
int no_more_from[NUM_BUTTONS] = {false};
pthread_t tid[NUM_BUTTONS];

void PlayAndDie(char *sound){
	play(sound);
	kill(getpid(),SIGINT);
}

/* 
	When a button is pressed, multiple signals to play a sound are sent.
	no_more_from set to false stops that.
	A thread for every button with this function waits until the button is
	released to let it play a sound again.
*/
void *OneSound(void *from){
	int origin = (int)from;
	unsigned int button = 0;
	int pressed = -1;

	switch (origin) {
		case 0:
			button = BUTTON_1;
			break;
		case 1:
			button = BUTTON_2;
			break;
		case 2:
			button = BUTTON_3;
			break;
		case 3:
			button = BUTTON_4;
			break;
		case 4:
			button = BUTTON_5;
			break;
		case 5:
			button = BUTTON_6;
			break;
		case 6:
			button = BUTTON_7;
			break;
		case 7:
			button = BUTTON_8;
			break;
	}

	if (button == BUTTON_4 || button == BUTTON_5) {
		pressed = 0
	}
	else{
		pressed = 1
	}

	while (digitalRead(button) == pressed){
		// Repeat until not pressed
	} 

	no_more_from[origin] = false;

	return NULL;
}

void PressToPlay(){
	char *sound = (char *)malloc(sizeof(char) * 50);
	int can_play = false;
	int from;

	if (digitalRead(BUTTON_1) == 1 && !no_more_from[0]) {
		sound = "sounds/bass_drum.mp3";
		can_play = true;
		no_more_from[0] = true;
		from = 0;
	}
	else if (digitalRead(BUTTON_2) == 1 && !no_more_from[1]) {
		sound = "sounds/closed_hi_hat.mp3";
		can_play = true;
		no_more_from[1] = true;
		from = 1;
	}
	else if (digitalRead(BUTTON_3) == 1 && !no_more_from[2]) {
		sound = "sounds/crash_cymbal.mp3";
		can_play = true;
		no_more_from[2] = true;
		from = 2;
	}
	else if (digitalRead(BUTTON_4) == 0 && !no_more_from[3]) {
		sound = "sounds/floor_tom.mp3";
		can_play = true;
		no_more_from[3] = true;
		from = 3;
	}
	else if (digitalRead(BUTTON_5) == 0 && !no_more_from[4]) {
		sound = "sounds/high_tom.mp3";
		can_play = true;
		no_more_from[4] = true;
		from = 4;
	}
	else if (digitalRead(BUTTON_6) == 1 && !no_more_from[5]) {
		sound = "sounds/mid_tom.mp3";
		can_play = true;
		no_more_from[5] = true;
		from = 5;
	}
	else if (digitalRead(BUTTON_7) == 1 && !no_more_from[6]) {
		sound = "sounds/ryde_cymbal.mp3";
		can_play = true;
		no_more_from[6] = true;
		from = 6;
	}
	else if (digitalRead(BUTTON_8) == 1 && !no_more_from[7]) {
		sound = "sounds/snare_drum.mp3";
		can_play = true;
		no_more_from[7] = true;
		from = 7;
	}

	if (can_play) {
		pthread_create(&tid[from], NULL, OneSound, (void *)from);

		if (fork() == 0) {
			PlayAndDie(sound);
		}
	}

	//free(sound);
}

void SetupPi(){
	wiringPiSetup();

	pinMode(BUTTON_1, INPUT);
	pinMode(BUTTON_2, INPUT);
	pinMode(BUTTON_3, INPUT);
	pinMode(BUTTON_4, INPUT);
	pinMode(BUTTON_5, INPUT);
	pinMode(BUTTON_6, INPUT);
	pinMode(BUTTON_7, INPUT);
	pinMode(BUTTON_8, INPUT);
}

int main(int argc, char *argv[]){
	SetupPi();

	while (true){
		PressToPlay();
	}
}
