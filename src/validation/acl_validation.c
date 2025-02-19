/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acl_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 08:54:40 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/02/19 08:55:02 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minirt.h"

bool	validate_ambient(char **split)
{
	double	ratio;
	char	*trimmed;
	int		trim_size;

	trimmed = ft_strtrim(split[3], "\n");
	trim_size = ft_strlen(trimmed);
	free(trimmed);
	if (split[1] && split[2] && !trim_size)
	{
		if (!is_valid_double(split[1]))
			return (exit_err("Error: invalid ambient ratio\n", NULL));
		ratio = ft_atof(split[1]);
		if (ratio < 0.0 || ratio > 1.0)
			return (exit_err("Error: invalid ambient ratio\n", NULL));
		if (!check_rgb(split[2]))
			return (false);
	}
	else
		return (exit_err("Error: invalid ambient config\n", NULL));
	return (true);
}

bool	validate_camera(char **split)
{
	char	*trimmed_fov;
	int		fov;
	int		trim_size;

	trimmed_fov = ft_strtrim(split[4], "\n");
	trim_size = ft_strlen(trimmed_fov);
	free(trimmed_fov);
	if (split[1] && split[2] && split[3] && !trim_size)
	{
		if (!check_coordinates(split[1]))
			return (false);
		if (!check_vector(split[2]))
			return (false);
		trimmed_fov = ft_strtrim(split[3], "\n");
		fov = ft_atoi(trimmed_fov);
		if (!is_valid_int(trimmed_fov) || fov < 0 || fov > 180)
			return (exit_err("Error: invalid camera FOV\n", NULL));
		free(trimmed_fov);
	}
	else
		return (exit_err("Error: invalid camera config\n", NULL));
	return (true);
}

bool	validate_light(char **split)
{
	char	*trimmed_brightness;
	double	brightness;
	int		trim_size;

	trimmed_brightness = ft_strtrim(split[3], "\n");
	trim_size = ft_strlen(trimmed_brightness);
	free(trimmed_brightness);
	if (split[1] && split[2] && !trim_size)
	{
		if (!check_coordinates(split[1]))
			return (false);
		trimmed_brightness = ft_strtrim(split[2], "\n");
		brightness = ft_atof(trimmed_brightness);
		if (!is_valid_double(trimmed_brightness)
			|| brightness < 0 || brightness > 1)
			return (exit_err("Error: invalid light brightness\n", NULL));
	}
	else
		return (exit_err("Error: invalid light config\n", NULL));
	free(trimmed_brightness);
	return (true);
}
