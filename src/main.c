/*********************************************************************
 *********************************************************************
 *********************** Jesús Jiménez Sánchez ***********************
 *********************************************************************
*********************************************************************/

/**
 * TODO: Threading
*/

#include <ao/ao.h>
#include <mpg123.h>
#include <pthread.h>

#define BITS 8

void *play(void *var){
	mpg123_handle *mh;
	unsigned char *buffer;
	size_t buffer_size;
	size_t done;
	int err;
	char *sound = (char *)var;

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
		ao_play(dev, buffer, done);
	}

	/* clean up */
	free(buffer);
	ao_close(dev);
	mpg123_close(mh);
	mpg123_delete(mh);
	mpg123_exit();
	ao_shutdown();

	pthread_exit(NULL);			/* terminate the thread */
	return NULL;
}

int main(int argc, char *argv[]){
	char option;
	pthread_t tid[10];
	int i = 0;
	char *instrument = malloc(30);

	/* 
		When reading a character from the keyboard, the
		program will play a different drums sound.
		It will change to drums hits in the final product.
	 */
	do{
		scanf("%c", &option);

		if(i == 10){
			i = 0;
		}

		switch (option){
			case 'a':
				instrument = "sounds/bass_drum.mp3";
				// play("sounds/bass_drum.mp3");
				break;
			case 'b':
				instrument = "sounds/closed_hi_hat.mp3";
				// play("sounds/closed_hi_hat.mp3");
				break;
			case 'c':
				instrument = "sounds/crash_cymbal.mp3";
				// play("sounds/crash_cymbal.mp3");
				break;
			case 'd':
				instrument = "sounds/open_hi_hat.mp3";
				// play("sounds/open_hi_hat.mp3");
				break;
			case 'e':
				instrument = "sounds/ryde_cymbal.mp3";
				// play("sounds/ryde_cymbal.mp3");
				break;
			case 'f':
				instrument = "sounds/snare_drum.mp3";
				// play("sounds/snare_drum.mp3");
				break;
			default:
				break;
		}

		if(option != '*'){
			pthread_create(&tid[i], NULL, play, (void *)instrument);
			i++;
		}
	} while (option != '*');

	printf("Bye bye!\n");
	
	pthread_exit(NULL);
}
