#ifndef PLAY_H_
#define PLAY_H_

#define BITS 8

/* Instruments */
/*
const char * const
immutable pointer to immutable char value
*/
const char * const BASS_DRUM = "bass_drum.mp3";
const char * const CLOSED_HI_HAT = "closed_hi_hat.mp3";
const char * const CRASH_CYMBAL = "crash_cymbal.mp3";
const char * const FLOOR_TOM = "floor_tom.mp3";
const char * const HIGH_TOM = "high_tom.mp3";
const char * const MID_TOM = "mid_tom.mp3";
const char * const OPEN_HI_HAT = "open_hi_hat.mp3";
const char * const RYDE_CYMBAL = "ryde_cymbal.mp3";
const char * const SNARE_DRUM = "snare_drum.mp3";

void play(char *sound);

#endif
