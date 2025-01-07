#include "../headers/main.h"
#include <stdio.h>

static t_data	*intialize(int ac, char **av);

int	main(int ac, char **av)
{
	/*t_data	*data;*/

	/*data = NULL;*/
	if (ac != 2 || !valid_args(ac, av))
		exit(0);
	else
	 printf("debug: valid valid");
	/*data = initialize(av);*/
	/*if (!data)*/
		/*ft_exit(data, NULL, INIT_ERROR, 1);*/
	/*ft_exit(data, NULL, NULL, 1);*/
	return (EXIT_SUCCESS);
}
