#ifndef TIME_H
#define TIME_H

#include <internal/types.h>

typedef long int time_t;
struct timespec {
	time_t tv_sec;
	long tv_nsec;
};

int nanosleep(const struct timespec *duration, struct timespec *rem);
unsigned int sleep(unsigned int seconds);
#endif
