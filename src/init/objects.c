/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:26:00 by nkanaan           #+#    #+#             */
/*   Updated: 2025/02/23 19:26:11 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/main.h"
#include "../../headers/minirt.h"

void	parse_plane(char **split, t_data *data)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	plane->pos = parse_pos(split[1]);
	plane->vec = parse_pos(split[2]);
	plane->color = parse_color(split[3]);
	data->objects->planes[data->planes_count] = plane;
	data->planes_count++;
	data->objs_count++;
}

void	parse_sphere(char **split, t_data *data)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	sphere->pos = parse_pos(split[1]);
	sphere->diameter = ft_atof(split[2]);
	sphere->color = parse_color(split[3]);
	data->objects->spheres[data->spheres_count] = sphere;
	data->spheres_count++;
	data->objs_count++;
}

void	parse_cylinder(char **split, t_data *data)
{
	t_cylinder	*cyl;

	cyl = malloc(sizeof(t_cylinder));
	cyl->pos = parse_pos(split[1]);
	cyl->vec = parse_pos(split[2]);
	cyl->diameter = ft_atof(split[3]);
	cyl->height = ft_atof(split[4]);
	cyl->color = parse_color(split[5]);
	data->objects->cylinders[data->cylinders_count] = cyl;
	data->cylinders_count++;
	data->objs_count++;
}
