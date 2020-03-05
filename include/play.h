/**
 * Copyright 2020 Jesús Jiménez Sánchez
 * 
 */

#ifndef PLAY_H_
#define PLAY_H_

#define BITS 8

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
 * @param volume Volume the instrument will be played
 * 
 */
void PressToPlay(int instrument, int volume);

#endif
