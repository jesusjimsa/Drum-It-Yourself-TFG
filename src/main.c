/*********************************************************************
 *********************************************************************
 *********************** Jesús Jiménez Sánchez ***********************
 *********************************************************************
*********************************************************************/

/* 
TODO:
	PTP
*/

#include <ao/ao.h>
#include <mpg123.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include "../include/play.h"

#define true (1 == 1)
#define false (!true)

int main(int argc, char *argv[]){
	char option;

	/* 
		When reading a character from the keyboard, the
		program will play a different drums sound.
		It will change to drums hits in the final product.
	 */
	do{
		scanf(" %c", &option);	// scanf needs an extra space at the beginning to consume the new line character

		switch (option){
			case 'a':
				if(fork() == 0)
					play("sounds/bass_drum.mp3");
				break;
			case 'b':
				if(fork() == 0)
					play("sounds/closed_hi_hat.mp3");
				break;
			case 'c':
				if(fork() == 0)
					play("sounds/crash_cymbal.mp3");
				break;
			case 'd':
				if(fork() == 0)
					play("sounds/open_hi_hat.mp3");
				break;
			case 'e':
				if(fork() == 0)
					play("sounds/ryde_cymbal.mp3");
				break;
			case 'f':
				if(fork() == 0)
					play("sounds/snare_drum.mp3");
				break;
			case 'g':
				if(fork() == 0)
					play("sounds/floor_tom.mp3");
				break;
			case 'h':
				if(fork() == 0)
					play("sounds/mid_tom.mp3");
				break;
			case 'i':
				if(fork() == 0)
					play("sounds/high_tom.mp3");
				break;
			case '*':
				printf("Bye bye!\n");
				break;
			default:
				printf("Not allowed!\n");
				break;
		}
	} while (option != '*');
}
