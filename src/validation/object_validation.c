/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 23:51:31 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/02/24 11:40:28 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minirt.h"

static bool	validate_elems(char **split, bool *has_ambient, bool *has_light,
				bool *has_camera)
{
	if (!ft_strcmp(split[0], "A") || !ft_strcmp(split[0], "A\n"))
	{
		*has_ambient = true;
		if (!validate_ambient(split))
			return (free_split(split), false);
	}
	if (!ft_strcmp(split[0], "C") || !ft_strcmp(split[0], "C\n"))
	{
		*has_camera = true;
		if (!validate_camera(split))
			return (free_split(split), false);
	}
	if (!ft_strcmp(split[0], "L") || !ft_strcmp(split[0], "L\n"))
	{
		*has_light = true;
		if (!validate_light(split))
			return (free_split(split), false);
	}
	return (true);
}

static bool	validate_objects(char **split)
{
	if (split[0] && (!ft_strcmp(split[0], "sp")
			|| !ft_strcmp(split[0], "sp\n")))
	{
		if (!validate_sphere(split))
			return (free_split(split), false);
	}
	if (split[0] && (!ft_strcmp(split[0], "pl")
			|| !ft_strcmp(split[0], "pl\n")))
	{
		if (!validate_plane(split))
			return (free_split(split), false);
	}
	if (split[0] && (!ft_strcmp(split[0], "cy")
			|| !ft_strcmp(split[0], "cy\n")))
	{
		if (!validate_cylinder(split))
			return (free_split(split), false);
	}
	return (true);
}

static bool	valid_elem_helper(char **split, bool *has_ambient, bool *has_light,
				bool *has_camera)
{
	if (!check_config(split[0]))
		return (free_split(split),
			ft_putstr_fd(RED "Error: unkown configs\n" RESET, 2), false);
	if (split[0] && (!ft_strcmp(split[0], "A") || !ft_strcmp(split[0], "C")
			|| !ft_strcmp(split[0], "L") || !ft_strcmp(split[0], "A\n")
			|| !ft_strcmp(split[0], "C\n") || !ft_strcmp(split[0], "L\n")))
		if (!validate_elems(split, has_ambient, has_light, has_camera))
			return (false);
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
		if (!valid_elem_helper(split, &has_ambient, &has_light, &has_camera))
			return (ft_lstclear(file), false);
		if (!validate_objects(split))
			return (ft_lstclear(file), false);
		free_split(split);
		tmp = tmp->next;
	}
	if (!has_ambient || !has_camera || !has_light)
		return (exit_err("Error: file must contain 'A', 'C', and 'L'\n", NULL));
	return (true);
}
