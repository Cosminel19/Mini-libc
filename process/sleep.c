#include <internal/syscall.h>
#include <internal/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>

int nanosleep(const struct timespec *duration, struct timespec *rem)
{
	int ret = syscall(__NR_nanosleep, duration, rem);
	if (ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}

unsigned int sleep(unsigned int seconds)
{
	struct timespec duration;
	duration.tv_sec = (time_t)seconds;
	duration.tv_nsec = 0;
	nanosleep(&duration, NULL);
	return 0;
}
