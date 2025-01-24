/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:30:56 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/01/24 14:58:29 by mmuhaise         ###   ########.fr       */
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
	light->color = parse_color(split[3]); //TO REVISE NOT REQUIRED
	data->light = light;
}

void	parse_plane(char **split, t_data *data)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	plane->ident = ft_strdup("pl");
	plane->pos = parse_pos(split[1]);
	plane->vec = parse_pos(split[2]);
	plane->color = parse_color(split[3]);
	data->plane = plane;
}

void	parse_sphere(char **split, t_data *data)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	sphere->ident = ft_strdup("sp");
	sphere->pos = parse_pos(split[1]);
	sphere->diameter = ft_atof(split[2]);
	sphere->color = parse_color(split[3]);
	data->sphere = sphere;
}

void	parse_cylinder(char **split, t_data *data)
{
	t_cylinder	*cyl;

	cyl = malloc(sizeof(t_cylinder));
	cyl->ident = ft_strdup("cy");
	cyl->pos = parse_pos(split[1]);
	cyl->vec = parse_pos(split[2]);
	cyl->diameter = ft_atof(split[3]);
	cyl->height = ft_atof(split[4]);
	cyl->color = parse_color(split[5]);
	data->cylinder = cyl;
}

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

static void	set_line(char *line, t_list **file)
{
	t_list	*new;

	new = ft_lstnew(line);
	ft_lstadd_back(file, new);
}

int	read_file(char *filename, t_list **file)
{
	int		fd;
	char	*line;

	fd = ft_open(filename);
	line = get_next_line(fd);
	if (!line)
		return (ft_putstr_fd(RED "Error: empty file :() \n" RESET, 2), 0);
	while (line)
	{
		set_line(line, file);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

bool	parse_file(t_list **file, t_data *data)
{
	t_list	*tmp;
	char	**split;

	tmp = (*file);
	while (tmp)
	{
		split = ft_split(tmp->content, " \t");
		if (!split)
			return (ft_putstr_fd(RED "Error: failed to split line\n" RESET, 2), false);
		parse_line(split, data);
		tmp = tmp->next;
	}
	print_data(data);
	return (true);
}
