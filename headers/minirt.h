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

void	launch_rays(t_data *rt);
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

#endif // !MINIRT>_H
