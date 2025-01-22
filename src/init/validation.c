#include "../../headers/main.h"

static bool	valid_ext(char *str)
{
	size_t	len;

	len = ft_strlen(str);

	while (len > 0 && str[len] != '.')
		len--;
	if (ft_strncmp(str + len, ".rt", 3))
		return (false);
	return (true);
}

bool	valid_args(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd(RED "Error: usage: <./minirt> <filename>\n" RESET, 2);
		return (false);
	}
	if (!valid_ext(av[1]))
	{
		ft_putstr_fd(RED "Error: invalid file extension: must be .rt\n" RESET, 2);
		return (false);
	}
	return (true);
}
