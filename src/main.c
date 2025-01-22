#include "../headers/main.h"
#include "../headers/minirt.h"

bool	initialize(char *filename)
{
	t_list	*file;

	file = NULL;
	if (!read_file(filename, &file))
		return (false);
	if (!parse_file(&file))
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	if (!valid_args(ac, av))
		exit(EXIT_FAILURE);
	if (!initialize(av[1]))
		exit(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
