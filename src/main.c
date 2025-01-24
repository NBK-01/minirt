/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:48:34 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/01/24 13:54:20 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include "../headers/minirt.h"

bool	initialize(char *filename)
{
	t_list	*file;
	t_data	*data;

	file = NULL;
	data = malloc(sizeof(t_data));
	if (!read_file(filename, &file))
		return (false);
	if (!parse_file(&file, data))
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
