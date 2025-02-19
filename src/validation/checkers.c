/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 00:00:37 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/02/19 08:34:13 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minirt.h"

bool	exit_err(char *msg, char **split)
{
	if (split)
		free_split(split);
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(RESET, 2);
	return (false);
}


bool	check_rgb(char *split)
{
	char	**color_split;
	char	*trimmed_color;
	int		r;	
	int		g;
	int		b;	

	color_split = ft_split(split, ",");
	if (!color_split || !color_split[0] || !color_split[1] || !color_split[2])
		return (exit_err("Error: invalid rgb color\n", color_split));
	if (color_split[3])
		return (exit_err("Error: invalid rgb color\n", color_split));
	trimmed_color = ft_strtrim(color_split[2], "\n");
	free(color_split[2]);
	color_split[2] = trimmed_color;
	if (!is_valid_int(color_split[0]) || !is_valid_int(color_split[1])
		|| !is_valid_int(color_split[2]))
		return (exit_err("Error: invalid RGB values\n", color_split));
	r = ft_atoi(color_split[0]);
	g = ft_atoi(color_split[1]);
	b = ft_atoi(color_split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (exit_err("Error: invalid RGB values\n", color_split));
	free_split(color_split);
	return (true);
}

bool	check_vector(char *split)
{
	char	**vec_split;
	double	v1;	
	double	v2;
	double	v3;	

	vec_split = ft_split(split, ",");
	if (!vec_split || !vec_split[0] || !vec_split[1] || !vec_split[2])
		return (exit_err("Error: invalid orientation vector\n", vec_split));
	if (vec_split[3])
		return (exit_err("Error: invalid orientation vector\n", vec_split));
	v1 = ft_atof(vec_split[0]);
	v2 = ft_atof(vec_split[1]);
	v3 = ft_atof(vec_split[2]);
	if (!is_valid_double(vec_split[0]) || !is_valid_double(vec_split[1])
		|| !is_valid_double(vec_split[2]) || v1 < -1 || v1 > 1
		|| v2 < -1 || v2 > 1 || v3 < -1 || v3 > 1)
		return (exit_err("Error: invalid orientation values\n", vec_split));
	free_split(vec_split);
	return (true);
}

bool	check_coordinates(char *split)
{
	char	**coord_split;

	coord_split = ft_split(split, ",");
	if (!coord_split || !coord_split[0] || !coord_split[1] || !coord_split[2])
		return (exit_err("Error: invalid coordinates\n", coord_split));
	if (coord_split[3])
		return (exit_err("Error: invalid coordinates\n", coord_split));
	if (!is_valid_double(coord_split[0]) || !is_valid_double(coord_split[1])
		|| !is_valid_double(coord_split[2]))
		return (exit_err("Error: invalid coordinate values\n", coord_split));
	free_split(coord_split);
	return (true);
}

int	check_config(char *str)
{
	char	*arr[] = {"A", "C", "L", "sp", "cy", "pl", "breakme"};
	int		i;

	i = 0;
	if (!ft_strcmp(str, "\n"))
		return (1);
	while (i < 6)
	{
		if (!ft_strcmp(str, arr[i]))
			break ;
		i++;
	}
	if (i > 5)
		return (0);
	return (1);
}
