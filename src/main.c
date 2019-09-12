/*********************************************************************
 *********************************************************************
 *********************** Jesús Jiménez Sánchez ***********************
 *********************************************************************
*********************************************************************/

#include <ao/ao.h>
#include <mpg123.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#define BITS 8

#define true (1 == 1)
#define false (!true)

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
		ao_play(dev, buffer, done);
	}

	/* clean up */
	free(buffer);
	ao_close(dev);
	mpg123_close(mh);
	mpg123_delete(mh);
	mpg123_exit();
	ao_shutdown();

	kill(getpid(),SIGINT);
}

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
