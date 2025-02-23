/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:26:29 by nkanaan           #+#    #+#             */
/*   Updated: 2025/02/23 19:26:30 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minirt.h"

static bool	cyl_helper(int *i, char **split)
{
	double	height;

	if (*i == 1)
		if (!check_coordinates(split[*i]))
			return (false);
	if (*i == 2)
		if (!check_vector(split[*i]))
			return (false);
	if (*i == 3)
		if (!is_valid_double(split[*i]) || ft_atof(split[*i]) < 0)
			return (exit_err("Error: invalid cylinder diameter\n", NULL));
	if (*i == 4)
	{
		height = ft_atof(split[*i]);
		if (!is_valid_double(split[*i]) || height < 0)
			return (exit_err("Error: invalid cylinder height\n", NULL));
	}
	if (*i == 5)
		if (!check_rgb(split[*i]))
			return (false);
	return (true);
}

bool	validate_cylinder(char **split)
{
	char	*trim;
	int		trim_size;
	int		i;

	i = -1;
	trim_size = 0;
	if (split && split[0] && split[1] && split[2]
		&& split[3] && split[4] && split[5] && split[6])
	{
		trim = ft_strtrim(split[6], "\n");
		trim_size = ft_strlen(trim);
		free(trim);
	}
	while (split[++i])
		if (!cyl_helper(&i, split))
			return (false);
	if (trim_size)
		return (exit_err("Error: invalid cylinder config\n", NULL));
	return (true);
}
