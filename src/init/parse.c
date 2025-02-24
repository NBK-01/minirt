/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:30:56 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/02/24 11:43:36 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/main.h"
#include "../../headers/math.h"
#include "../../headers/minirt.h"
#include <stdio.h>

void	parse_line(char **split, t_data *data)
{
	if (!ft_strcmp(split[0], "A"))
		parse_ambient(split, data);
	if (!ft_strcmp(split[0], "C"))
		parse_camera(split, data);
	if (!ft_strcmp(split[0], "L"))
		parse_light(split, data);
	if (!ft_strcmp(split[0], "sp"))
		parse_sphere(split, data);
	if (!ft_strcmp(split[0], "pl"))
		parse_plane(split, data);
	if (!ft_strcmp(split[0], "cy"))
		parse_cylinder(split, data);
}

void	init_data(t_data *data)
{
	data->objs_count = 0;
	data->planes_count = 0;
	data->spheres_count = 0;
	data->cylinders_count = 0;
	data->objects = malloc(sizeof(t_objects));
	if (!data->objects)
	{
		ft_putstr_fd(RED "Error: failed to malloc objects\n" RESET, 2);
		return ;
	}
}

static void	alloc_containers(t_list	**file, t_data	*data)
{
	char	**split;
	t_list	*tmp;

	tmp = (*file);
	while (tmp)
	{
		split = ft_split(tmp->content, " \t");
		if (!ft_strcmp(split[0], "sp"))
			data->spheres_count++;
		if (!ft_strcmp(split[0], "pl"))
			data->planes_count++;
		if (!ft_strcmp(split[0], "cy"))
			data->cylinders_count++;
		free_split(split);
		tmp = tmp->next;
	}
	data->objects->spheres = malloc(data->spheres_count * sizeof(t_sphere ));
	data->objects->planes = malloc(data->planes_count * sizeof(t_plane ));
	data->objects->cylinders = malloc(data->spheres_count * sizeof(t_cylinder ));
	data->spheres_count = 0;
	data->planes_count = 0;
	data->cylinders_count = 0;
}

bool	parse_file(t_list **file, t_data *data)
{
	t_list	*tmp;
	char	**split;

	tmp = (*file);
	init_data(data);
	alloc_containers(file, data);
	while (tmp)
	{
		split = ft_split(tmp->content, " \t");
		if (!split)
			return (ft_putstr_fd(RED "Error: failed to split line\n" RESET,
					2), false);
		parse_line(split, data);
		free_split(split);
		tmp = tmp->next;
	}
	ft_lstclear(file);
	init_mlx(data);
	return (true);
}
