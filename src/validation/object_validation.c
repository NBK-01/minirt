/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 23:51:31 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/02/19 09:12:50 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minirt.h"

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
			return (exit_err("Error: invalid sphere diameter\n", NULL));
		if (!check_rgb(split[3]))
			return (false);
	}
	else
		return (exit_err("Error: invalid sphere config\n", NULL));
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
		return (exit_err("Error: invalid plane config\n", NULL));
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
			return (exit_err("Error: invalid cylinder diameter\n", NULL));
		height = ft_atof(split[4]);
		if (!is_valid_double(split[4]) || height < 0)
			return (exit_err("Error: invalid cylinder height\n", NULL));
		if (!check_rgb(split[5]))
			return (false);
	}
	else
		return (exit_err("Error: invalid plane config\n", NULL));
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
					return (free_split(split), false);
			}
			if (!ft_strcmp(split[0], "C") || !ft_strcmp(split[0], "C\n"))
			{
				has_camera = true;
				if (!validate_camera(split))
					return (free_split(split), false);
			}
			if (!ft_strcmp(split[0], "L") || !ft_strcmp(split[0], "L\n"))
			{
				has_light = true;
				if (!validate_light(split))
					return (free_split(split), false);
			}
		}
		if (split[0] && (!ft_strcmp(split[0], "sp") || !ft_strcmp(split[0], "sp\n")))
		{
			if (!validate_sphere(split))
				return (free_split(split), false);
		}
		if (split[0] && (!ft_strcmp(split[0], "pl") || !ft_strcmp(split[0], "pl\n")))
		{
			if (!validate_plane(split))
				return (free_split(split), false);
		}
		if (split[0] && (!ft_strcmp(split[0], "cy") || !ft_strcmp(split[0], "cy\n")))
		{
			if (!validate_cylinder(split))
				return (free_split(split), false);
		}
		free_split(split);
		tmp = tmp->next;
	}
	if (!has_ambient || !has_camera || !has_light)
		return (ft_putstr_fd(RED "Error: file must contain 'A', 'C', and 'L'\n" RESET, 2), false);
	return (true);
}
