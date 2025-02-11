/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:55:34 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/01/24 14:59:08 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "main.h"

void	render_scene(t_data *data);
bool	valid_args(int ac, char **av);
int		read_file(char *filename, t_list **file);
bool	parse_file(t_list **file, t_data *data);
void	print_ambient(t_ambient *ambient);
void	print_camera(t_camera *camera);
void	print_light(t_light *light);
void	print_sphere(t_sphere *sphere);
void	print_plane(t_plane *plane);
void	print_cylinder(t_cylinder *cylinder);
void	print_data(t_data *data);
double	ft_atof(const char *str);
bool	intersection(t_ray ray, t_data *data, t_hit *hit, t_ident id, int i);
t_pos calculate_ray_direction(int x, int y, t_camera *camera, double aspect_ratio);
t_ray	generate_ray(t_camera *cam, int x, int y);
t_color	set_color(t_hit hit, t_data *data);
double compute_lighting(t_hit hit, t_light light, t_data *data);
int find_closest_intersection(t_ray ray, t_data *data, t_hit *closest_hit);


#endif // !MINIRT>_H
