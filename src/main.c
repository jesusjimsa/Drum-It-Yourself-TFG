/**
 * Copyright 2020 Jesús Jiménez Sánchez
 *
 */

#include "../include/shared.h"

void intHandler(int dummy) {
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
	signal(SIGINT, intHandler);
	readSerial();

	return 0;
}
