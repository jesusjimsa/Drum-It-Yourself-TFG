/**
 * Copyright 2020 Jesús Jiménez Sánchez
 * 
 */

#ifndef PLAY_H_
#define PLAY_H_

#define BITS 8

struct read_intrument {
	int id;
	int volume;
};

/**
 * @brief Play mp3 sound
 * 
 * @param sound Path to mp3 file
 * 
 */
void play(char *sound);

/**
 * @brief Choose sound to play
 * 
 * @param instrument Instrument to play
 * 
 */
void PressToPlay(struct read_intrument r_instrument);

#endif
