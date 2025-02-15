/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 00:00:37 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/02/15 00:08:42 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minirt.h"


bool	check_rgb(char *split)
{
	char	**color_split;
	char	*trimmed_color;
	int		r;	
	int		g;
	int		b;	

	color_split = ft_split(split, ",");
	if (!color_split || !color_split[0] || !color_split[1] || !color_split[2])
	{
		return (ft_putstr_fd(RED "Error: invalid rgb color\n" RESET, 2), false);
	}
	if (color_split[3])
	{
		return (ft_putstr_fd(RED "Error: invalid rgb color\n" RESET, 2), false);
	}
	trimmed_color = ft_strtrim(color_split[2], "\n");
	free(color_split[2]);
	color_split[2] = trimmed_color;
	if (!is_valid_int(color_split[0]) || !is_valid_int(color_split[1]) || !is_valid_int(color_split[2]))
		return (ft_putstr_fd(RED "Error: invalid RGB values\n" RESET, 2), false);
	r = ft_atoi(color_split[0]);
	g = ft_atoi(color_split[1]);
	b = ft_atoi(color_split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (ft_putstr_fd(RED "Error: invalid RGB values\n" RESET, 2), false);
	free(color_split[0]);
	free(color_split[1]);
	free(color_split[2]);
	free(color_split);
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
		return (ft_putstr_fd(RED "Error: invalid orientation vector\n" RESET, 2), false);
	if (vec_split[3])
		return (ft_putstr_fd(RED "Error: invalid orientation vector\n" RESET, 2), false);
	v1 = ft_atof(vec_split[0]);
	v2 = ft_atof(vec_split[1]);
	v3 = ft_atof(vec_split[2]);
	if (!is_valid_double(vec_split[0]) || !is_valid_double(vec_split[1])
		|| !is_valid_double(vec_split[2]) || v1 < -1 || v1 > 1
		|| v2 < -1 || v2 > 1 || v3 < -1 || v3 > 1)
		return (ft_putstr_fd(RED "Error: invalid orientation values\n" RESET, 2), false);
	free(vec_split[0]);
	free(vec_split[1]);
	free(vec_split[2]);
	free(vec_split);
	return (true);
}

bool	check_coordinates(char *split)
{
	char	**coord_split;
	
	coord_split = ft_split(split, ",");
	if (!coord_split || !coord_split[0] || !coord_split[1] || !coord_split[2])
	{
		return (ft_putstr_fd(RED "Error: invalid coordinates\n" RESET, 2), false);
	}
	if (coord_split[3])
	{
		return (ft_putstr_fd(RED "Error: invalid coordinates\n" RESET, 2), false);
	}
	if (!is_valid_double(coord_split[0]) || !is_valid_double(coord_split[1]) || !is_valid_double(coord_split[2]))
		return (ft_putstr_fd(RED "Error: invalid coordinates values\n" RESET, 2), false);
	free(coord_split[0]);
	free(coord_split[1]);
	free(coord_split[2]);
	free(coord_split);
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
