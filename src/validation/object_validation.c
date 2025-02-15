/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 23:51:31 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/02/15 08:54:13 by mmuhaise         ###   ########.fr       */
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
			return (ft_putstr_fd(RED "Error: invalid ambient ratio\n" RESET, 2), false);
		ratio = ft_atof(split[1]);
		if (ratio < 0.0 || ratio > 1.0)
			return (ft_putstr_fd(RED "Error: invalid ambient ratio\n" RESET, 2), false);
		if (!check_rgb(split[2]))
			return (false);
	}
	else
		return (ft_putstr_fd(RED "Error: invalid ambient config\n" RESET, 2), false);
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
			return (ft_putstr_fd(RED "Error: invalid camera FOV\n" RESET, 2), false);
		free(trimmed_fov);
	}
	else
		return (ft_putstr_fd(RED "Error: invalid camera config\n" RESET, 2), false);
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
			return (ft_putstr_fd(RED "Error: invalid light brightness\n" RESET, 2), false);
	}
	else
		return (ft_putstr_fd(RED "Error: invalid light config\n" RESET, 2), false);
	free(trimmed_brightness);
	return (true);
}

bool	validate_sphere(char **split)
{
	double	diameter;
	char	*trim;
	int		trim_size;

	trim = ft_strtrim(split[4], "\n");
	trim_size = ft_strlen(trim);
	free(trim);
	if (split[1] && split[2] && split[3]
		&& !trim_size)
	{
		if (!check_coordinates(split[1]))
			return (false);
		diameter = ft_atof(split[2]);
		if (!is_valid_double(split[2]) || diameter < 0)
			return (ft_putstr_fd(RED "Error: invalid sphere diameter\n" RESET, 2), false);
		if (!check_rgb(split[3]))
			return (false);
	}
	else
		return (ft_putstr_fd(RED "Error: invalid sphere config\n" RESET, 2), false);
	return (true);
}

bool	validate_plane(char **split)
{
	char	*trim;
	int		trim_size;

	trim = ft_strtrim(split[4], "\n");
	trim_size = ft_strlen(trim);
	free(trim);
	if (split[1] && split[2] && split[3]
		&& !trim_size)
	{
		if (!check_coordinates(split[1]))
			return (false);
		if (!check_vector(split[2]))
			return (false);
		if (!check_rgb(split[3]))
			return (false);
	}
	else
		return (ft_putstr_fd(RED "Error: invalid plane config\n" RESET, 2), false);
	return (true);
}

bool	validate_cylinder(char **split)
{
	double	diameter;
	double	height;
	char	*trim;
	int		trim_size;

	trim = ft_strtrim(split[6], "\n");
	trim_size = ft_strlen(trim);
	free(trim);
	if (split[1] && split[2] && split[3] && split[4]
		&& split[5] && !trim_size)
	{
		if (!check_coordinates(split[1]))
			return (false);
		if (!check_vector(split[2]))
			return (false);
		diameter = ft_atof(split[3]);
		if (!is_valid_double(split[3]) || diameter < 0)
			return (ft_putstr_fd(RED "Error: invalid cylinder diameter\n" RESET, 2), false);
		height = ft_atof(split[4]);
		if (!is_valid_double(split[4]) || height < 0)
			return (ft_putstr_fd(RED "Error: invalid cylinder height\n" RESET, 2), false);
		if (!check_rgb(split[5]))
			return (false);
	}
	else
		return (ft_putstr_fd(RED "Error: invalid plane config\n" RESET, 2), false);
	return (true);
}

bool	validate_file(t_list **file)
{
	t_list	*tmp;
	char	**split;
	bool	has_ambient;
	bool	has_camera;
	bool	has_light;

	has_ambient = false;
	has_camera = false;
	has_light = false;
	tmp = (*file);
	while (tmp)
	{
		split = ft_split(tmp->content, " \t");
		if (!check_config(split[0]))
			return (ft_putstr_fd(RED "Error: unkown configs\n" RESET, 2), false);
		if (split[0] && (!ft_strcmp(split[0], "A") || !ft_strcmp(split[0], "C")
				|| !ft_strcmp(split[0], "L") || !ft_strcmp(split[0], "A\n")
				|| !ft_strcmp(split[0], "C\n") || !ft_strcmp(split[0], "L\n")))
		{
			if (!ft_strcmp(split[0], "A") || !ft_strcmp(split[0], "A\n"))
			{
				has_ambient = true;
				if (!validate_ambient(split))
					return (false);
			}
			if (!ft_strcmp(split[0], "C") || !ft_strcmp(split[0], "C\n"))
			{
				has_camera = true;
				if (!validate_camera(split))
					return (false);
			}
			if (!ft_strcmp(split[0], "L") || !ft_strcmp(split[0], "L\n"))
			{
				has_light = true;
				if (!validate_light(split))
					return (false);
			}
		}
		if (split[0] && (!ft_strcmp(split[0], "sp") || !ft_strcmp(split[0], "sp\n")))
		{
			if (!validate_sphere(split))
			return (false);
		}
		if (split[0] && (!ft_strcmp(split[0], "pl") || !ft_strcmp(split[0], "pl\n")))
		{
			if (!validate_plane(split))
			return (false);
		}
		if (split[0] && (!ft_strcmp(split[0], "cy") || !ft_strcmp(split[0], "cy\n")))
		{
			if (!validate_cylinder(split))
			return (false);
		}
		free_split(split);
		tmp = tmp->next;
	}
	if (!has_ambient || !has_camera || !has_light)
		return (ft_putstr_fd(RED "Error: file must contain 'A', 'C', and 'L'\n" RESET, 2), false);
	return (true);
}
