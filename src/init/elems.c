/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elems.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:25:58 by nkanaan           #+#    #+#             */
/*   Updated: 2025/02/23 19:26:11 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/main.h"
#include "../../headers/minirt.h"

t_color	parse_color(char *split)
{
	char	**tmp;
	t_color	color;

	tmp = ft_split(split, ",");
	color.r = ft_atoi(tmp[0]);
	color.g = ft_atoi(tmp[1]);
	color.b = ft_atoi(tmp[2]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp);
	return (color);
}

void	parse_ambient(char **split, t_data *data)
{
	t_ambient	*ambient;

	ambient = malloc(sizeof(t_ambient));
	ambient->ident = 'A';
	ambient->ratio = ft_atof(split[1]);
	ambient->color = parse_color(split[2]);
	data->ambient = ambient;
}

t_pos	parse_pos(char *split)
{
	char	**tmp;
	t_pos	pos;

	tmp = ft_split(split, ",");
	pos.x = ft_atof(tmp[0]);
	pos.y = ft_atof(tmp[1]);
	pos.z = ft_atof(tmp[2]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp);
	return (pos);
}

void	parse_camera(char **split, t_data *data)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	camera->ident = 'C';
	camera->pos = parse_pos(split[1]);
	camera->vec = parse_pos(split[2]);
	camera->fov = ft_atoi(split[3]);
	data->camera = camera;
}

void	parse_light(char **split, t_data *data)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	light->ident = 'L';
	light->pos = parse_pos(split[1]);
	light->ratio = ft_atof(split[2]);
	data->light = light;
}
