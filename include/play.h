/**
 * Copyright 2020 Jesús Jiménez Sánchez
 * 
 */

#ifndef PLAY_H_
#define PLAY_H_

#define BITS 8

const char * const sounds_list[9][3] = {
	{	
		"sounds/volume/low/snare_drum.mp3",
		"sounds/volume/snare_drum.mp3",
		"sounds/volume/high/snare_drum.mp3",
	}
	{	
		"sounds/volume/low/bass_drum.mp3",
		"sounds/volume/bass_drum.mp3",
		"sounds/volume/high/bass_drum.mp3",
	}
	{	
		"sounds/volume/low/closed_hi_hat.mp3",
		"sounds/volume/closed_hi_hat.mp3",
		"sounds/volume/high/closed_hi_hat.mp3",
	}
	{	
		"sounds/volume/low/crash_cymbal.mp3",
		"sounds/volume/crash_cymbal.mp3",
		"sounds/volume/high/crash_cymbal.mp3",
	}
	{	
		"sounds/volume/low/ryde_cymbal.mp3",
		"sounds/volume/ryde_cymbal.mp3",
		"sounds/volume/high/ryde_cymbal.mp3",
	}
	{	
		"sounds/volume/low/high_tom.mp3",
		"sounds/volume/high_tom.mp3",
		"sounds/volume/high/high_tom.mp3",
	}
	{	
		"sounds/volume/low/mid_tom.mp3",
		"sounds/volume/mid_tom.mp3",
		"sounds/volume/high/mid_tom.mp3",
	}
	{	
		"sounds/volume/low/floor_tom.mp3",
		"sounds/volume/floor_tom.mp3",
		"sounds/volume/high/floor_tom.mp3",
	}
	{	
		"sounds/volume/low/open_hi_hat.mp3",
		"sounds/volume/open_hi_hat.mp3",
		"sounds/volume/high/open_hi_hat.mp3",
	}
}

void play(char *sound);

#endif
