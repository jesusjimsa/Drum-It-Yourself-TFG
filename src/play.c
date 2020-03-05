/**
 * Copyright 2020 Jesús Jiménez Sánchez
 * 
 */

#include "../include/shared.h"

const char * const sounds_list[24][3] = {
	{
		"sounds/volume/low/snare_drum.mp3",
		"sounds/snare_drum.mp3",
		"sounds/volume/high/snare_drum.mp3",
	},
	{
		"sounds/volume/low/closed_hi_hat.mp3",
		"sounds/closed_hi_hat.mp3",
		"sounds/volume/high/closed_hi_hat.mp3",
	},
	{
		"sounds/volume/low/crash_cymbal.mp3",
		"sounds/crash_cymbal.mp3",
		"sounds/volume/high/crash_cymbal.mp3",
	},
	{
		"sounds/volume/low/high_tom.mp3",
		"sounds/high_tom.mp3",
		"sounds/volume/high/high_tom.mp3",
	},
	{
		"sounds/volume/low/floor_tom.mp3",
		"sounds/floor_tom.mp3",
		"sounds/volume/high/floor_tom.mp3",
	},
	{
		"sounds/volume/low/bass_drum.mp3",
		"sounds/bass_drum.mp3",
		"sounds/volume/high/bass_drum.mp3",
	},
	{
		"sounds/volume/low/ryde_cymbal.mp3",
		"sounds/ryde_cymbal.mp3",
		"sounds/volume/high/ryde_cymbal.mp3",
	},
	{
		"sounds/volume/low/mid_tom.mp3",
		"sounds/mid_tom.mp3",
		"sounds/volume/high/mid_tom.mp3",
	},
	{
		"sounds/volume/low/open_hi_hat.mp3",
		"sounds/open_hi_hat.mp3",
		"sounds/volume/high/open_hi_hat.mp3",
	},
	{
		"sounds/volume/low/closed_hh_and_snare.mp3",
		"sounds/combined/closed_hh_and_snare.mp3",
		"sounds/volume/high/closed_hh_and_snare.mp3"
	},
	{
		"sounds/volume/low/crash_and_snare.mp3",
		"sounds/combined/crash_and_snare.mp3",
		"sounds/volume/high/crash_and_snare.mp3"
	},
	{
		"sounds/volume/low/snare_and_high_tom.mp3",
		"sounds/combined/snare_and_high_tom.mp3",
		"sounds/volume/high/snare_and_high_tom.mp3"
	},
	{
		"sounds/volume/low/snare_and_floor_tom.mp3",
		"sounds/combined/snare_and_floor_tom.mp3",
		"sounds/volume/high/snare_and_floor_tom.mp3"
	},
	{
		"sounds/volume/low/bass_and_snare.mp3",
		"sounds/combined/bass_and_snare.mp3",
		"sounds/volume/high/bass_and_snare.mp3"
	},
	{
		"sounds/volume/low/closed_hh_and_crash.mp3",
		"sounds/combined/closed_hh_and_crash.mp3",
		"sounds/volume/high/closed_hh_and_crash.mp3"
	},
	{
		"sounds/volume/low/closed_hh_and_high_tom.mp3",
		"sounds/combined/closed_hh_and_high_tom.mp3",
		"sounds/volume/high/closed_hh_and_high_tom.mp3"
	},
	{
		"sounds/volume/low/closed_hh_and_floor_tom.mp3",
		"sounds/combined/closed_hh_and_floor_tom.mp3",
		"sounds/volume/low/closed_hh_and_floor_tom.mp3"
	},
	{
		"sounds/volume/low/bass_and_closed_hh.mp3",
		"sounds/combined/bass_and_closed_hh.mp3",
		"sounds/volume/high/bass_and_closed_hh.mp3"
	},
	{
		"sounds/volume/low/crash_and_high_tom.mp3",
		"sounds/combined/crash_and_high_tom.mp3",
		"sounds/volume/high/crash_and_high_tom.mp3"
	},
	{
		"sounds/volume/low/crash_and_floor_tom.mp3",
		"sounds/combined/crash_and_floor_tom.mp3",
		"sounds/volume/high/crash_and_floor_tom.mp3"
	},
	{
		"sounds/volume/low/bass_and_crash.mp3",
		"sounds/combined/bass_and_crash.mp3",
		"sounds/volume/high/bass_and_crash.mp3"
	},
	{
		"sounds/volume/low/high_and_floor_tom.mp3",
		"sounds/combined/high_and_floor_tom.mp3",
		"sounds/volume/low/high_and_floor_tom.mp3"
	},
	{
		"sounds/volume/low/bass_and_high.mp3",
		"sounds/combined/bass_and_high.mp3",
		"sounds/volume/high/bass_and_high.mp3"
	},
	{
		"sounds/volume/low/bass_and_floor.mp3",
		"sounds/combined/bass_and_floor.mp3",
		"sounds/volume/high/bass_and_floor.mp3"
	}
};

struct read_intrument {
	int id;
	int volume;
};

void play(char *sound){
	mpg123_handle *mh;
	unsigned char *buffer;
	size_t buffer_size;
	size_t done;
	int err;

	int driver;
	ao_device *dev;

	ao_sample_format format;
	int channels, encoding;
	long rate;

	/* initializations */
	ao_initialize();
	driver = ao_default_driver_id();
	mpg123_init();
	mh = mpg123_new(NULL, &err);
	buffer_size = mpg123_outblock(mh);
	buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

	/* open the file and get the decoding format */
	mpg123_open(mh, sound);
	mpg123_getformat(mh, &rate, &channels, &encoding);

	/* set the output format and open the output device */
	format.bits = mpg123_encsize(encoding) * BITS;
	format.rate = rate;
	format.channels = channels;
	format.byte_format = AO_FMT_NATIVE;
	format.matrix = 0;
	dev = ao_open_live(driver, &format, NULL);

	/* decode and play */
	while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK){
		ao_play(dev, (char*)buffer, done);
	}

	/* clean up */
	free(buffer);
	ao_close(dev);
	mpg123_close(mh);
	mpg123_delete(mh);
	mpg123_exit();
	ao_shutdown();
}

void PressToPlay(void *instrument) {
	char *sound = (char *)malloc(sizeof(char) * 50);
	int can_play = true;
	int chosen_volume = 0;
	struct read_intrument r_instrument = (struct read_intrument) instrument;

	if (r_instrument.volume >= 200 && r_instrument.volume < 400) {
		chosen_volume = 0;
	}
	else if (r_instrument.volume >= 400 && r_instrument.volume < 800) {
		chosen_volume = 1;
	}
	else if (r_instrument.volume >= 800) {
		chosen_volume = 2;
	}
	else {
		/*
			In the case it returns a value less than 200,
			nothing should be played
		*/
		kill(getpid(), SIGINT);	// Exit process
	}

	if (r_instrument.id < 1 || r_instrument.id > 25) {
		can_play = false;
	}

	sound = (char *)sounds_list[r_instrument.id - 1][chosen_volume];

	if (can_play) {
		play(sound);
	}

	kill(getpid(), SIGINT);	// Exit child process
}
