#include <unistd.h>
#include <internal/syscall.h>
#include <string.h>
#include <errno.h>

int puts(const char *str)
{
	char nl = '\n';
	if (strlen(str)) {
		if (write(1, str, strlen(str)) == -1) {
			return -1;
		}
	}
	if (write(1, &nl, 1) == -1) {
		return -1;
	}
	return 1;
}
