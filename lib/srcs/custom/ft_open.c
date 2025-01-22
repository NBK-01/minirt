#include "../../includes/libft.h"
#include <stdio.h>

int	ft_open(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd(RED "Error: failed to open file\n" RESET, 2), 0);
	if (read(fd, NULL, 0) < 0)
		return (ft_putstr_fd(RED "Error: failed to read file\n" RESET, 2), 0);
	return (fd);
}
