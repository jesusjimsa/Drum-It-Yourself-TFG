/**
 * Copyright 2020 Jesús Jiménez Sánchez
 *
 */

#include "../include/shared.h"

void intHandler(int dummy) {
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
	printf("Playing...\n");
	printf("Press Ctrl+C to close\n");

	signal(SIGINT, intHandler);
	readSerial();

	return 0;
}
