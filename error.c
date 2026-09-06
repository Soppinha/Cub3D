#include "cub3d.h"
#include <unistd.h>

static void putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
}

int fail(char *msg)
{
	putstr_fd("Error\n", 2);
	putstr_fd(msg, 2);
	putstr_fd("\n", 2);
	return (0);
}
