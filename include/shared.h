/**
 * Copyright 2020 Jesús Jiménez Sánchez
 * 
 */

#ifndef SHARED_H_
#define SHARED_H_

#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <signal.h>
#include <ao/ao.h>
#include <mpg123.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include "../include/play.h"
#include "../include/read.h"

#define true (1 == 1)
#define false (!true)

#endif
