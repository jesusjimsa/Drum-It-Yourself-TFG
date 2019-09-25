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

/* enum instrument{
	bass_drum,
	closed_hi_hat,
	crash_cymbal,
	open_hi_hat,
	ryde_cymbal,
	snare_drum,
	floor_tom,
	mid_tom,
	high_tom,
	bass_and_closed_hh,
	bass_and_open_hh,
	closed_hh_and_snare,
	crash_and_snare
}; */

void ChooseSound(char selected[]) {
	if (selected[0] == '\n' && selected[1] == '\0') {
		printf("You have to write one or more letter to make sounds\n");
	}
	else if (selected[0] == 'a' && selected[1] == '\n') {
		play("sounds/bass_drum.mp3");
	}
	else if (selected[0] == 'b' && selected[1] == '\n') {
		play("sounds/closed_hi_hat.mp3");
	}
	else if (selected[0] == 'c' && selected[1] == '\n') {
		play("sounds/crash_cymbal.mp3");
	}
	else if (selected[0] == 'd' && selected[1] == '\n') {
		play("sounds/floor_tom.mp3");
	}
	else if (selected[0] == 'e' && selected[1] == '\n') {
		play("sounds/high_tom.mp3");
	}
	else if (selected[0] == 'f' && selected[1] == '\n') {
		play("sounds/mid_tom.mp3");
	}
	else if (selected[0] == 'g' && selected[1] == '\n') {
		play("sounds/open_hi_hat.mp3");
	}
	else if (selected[0] == 'h' && selected[1] == '\n') {
		play("sounds/ryde_cymbal.mp3");
	}
	else if (selected[0] == 'i' && selected[1] == '\n') {
		play("sounds/snare_drum.mp3");
	}
	else if ((selected[0] == 'a' && selected[1] == 'b' && selected[2] == '\n')
			|| (selected[0] == 'b' && selected[1] == 'a' && selected[2] == '\n')) {
		play("sounds/combined/bass_and_closed_hh.mp3");
	}
	else if ((selected[0] == 'a' && selected[1] == 'g' && selected[2] == '\n')
			|| (selected[0] == 'g' && selected[1] == 'a' && selected[2] == '\n')) {
		play("sounds/combined/bass_and_open_hh.mp3");
	}
	else if ((selected[0] == 'a' && selected[1] == 'i' && selected[2] == '\n')
			|| (selected[0] == 'i' && selected[1] == 'a' && selected[2] == '\n')) {
		play("sounds/combined/bass_and_snare.mp3");
	}
	else if ((selected[0] == 'b' && selected[1] == 'i' && selected[2] == '\n')
			|| (selected[0] == 'i' && selected[1] == 'b' && selected[2] == '\n')) {
		play("sounds/combined/closed_hh_and_snare.mp3");
	}
	else if ((selected[0] == 'c' && selected[1] == 'i' && selected[2] == '\n')
			|| (selected[0] == 'i' && selected[1] == 'c' && selected[2] == '\n')) {
		play("sounds/combined/crash_and_snare.mp3");
	}
	else if ((selected[0] == 'a' && selected[1] == 'd' && selected[2] == '\n')
			|| (selected[0] == 'd' && selected[1] == 'a' && selected[2] == '\n')) {
		play("sounds/combined/bass_and_floor.mp3");
	}
	else if ((selected[0] == 'b' && selected[1] == 'e' && selected[2] == '\n')
			|| (selected[0] == 'e' && selected[1] == 'b' && selected[2] == '\n')) {
		play("sounds/combined/bass_and_high.mp3");
	}
	else if ((selected[0] == 'c' && selected[1] == 'h' && selected[2] == '\n')
			|| (selected[0] == 'h' && selected[1] == 'c' && selected[2] == '\n')) {
		play("sounds/combined/crash_and_ryde.mp3");
	}
	else if ((selected[0] == 'e' && selected[1] == 'd' && selected[2] == '\n')
			|| (selected[0] == 'd' && selected[1] == 'e' && selected[2] == '\n')) {
		play("sounds/combined/high_and_floor_tom.mp3");
	}
	else if ((selected[0] == 'e' && selected[1] == 'f' && selected[2] == '\n')
			|| (selected[0] == 'f' && selected[1] == 'e' && selected[2] == '\n')) {
		play("sounds/combined/high_and_mid_tom.mp3");
	}
	else if ((selected[0] == 'f' && selected[1] == 'd' && selected[2] == '\n')
			|| (selected[0] == 'd' && selected[1] == 'f' && selected[2] == '\n')) {
		play("sounds/combined/mid_and_floor_tom.mp3");
	}
	else if ((selected[0] == 'g' && selected[1] == 'i' && selected[2] == '\n')
			|| (selected[0] == 'i' && selected[1] == 'g' && selected[2] == '\n')) {
		play("sounds/combined/open_hh_and_snare.mp3");
	}
	else if ((selected[0] == 'i' && selected[1] == 'd' && selected[2] == '\n')
			|| (selected[0] == 'd' && selected[1] == 'i' && selected[2] == '\n')) {
		play("sounds/combined/snare_and_floor_tom.mp3");
	}
	else if ((selected[0] == 'i' && selected[1] == 'e' && selected[2] == '\n')
			|| (selected[0] == 'e' && selected[1] == 'i' && selected[2] == '\n')) {
		play("sounds/combined/snare_and_high_tom.mp3");
	}
	else if ((selected[0] == 'i' && selected[1] == 'f' && selected[2] == '\n')
			|| (selected[0] == 'f' && selected[1] == 'i' && selected[2] == '\n')) {
		play("sounds/combined/snare_and_mid_tom.mp3");
	}
	else if ((selected[0] == 'i' && selected[1] == 'h' && selected[2] == '\n')
			|| (selected[0] == 'h' && selected[1] == 'i' && selected[2] == '\n')) {
		play("sounds/combined/snare_and_ryde.mp3");
	}
	else if (selected[0] == '*') {
		return;
	}
	else{
		printf("Not valid character!\n");
	}

	kill(getpid(),SIGINT);
}

int main(int argc, char *argv[]) {
	/*
		The maximun is 5 (4 + '\0') because one person
		can only play 4 instruments at the same time
		when playing drums
	*/
	char selected[5];

	/*
		When reading a character from the keyboard, the
		program will play a different drums sound.
		It will change to drums hits in the final product.
	 */
	do{
		fgets(selected, sizeof(selected), stdin);
		
		if (fork() == 0) {
			ChooseSound(selected);
		}
	} while (selected[0] != '*');
}
