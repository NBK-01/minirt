/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:55:34 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/02/21 13:20:08 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "main.h"


bool	validate_sphere(char **split);
bool	validate_plane(char **split);
bool	validate_cylinder(char **split);
int		close_window(int keycode, t_data *data);
long	ft_strtol(const char *str, char **endptr, int base);
void	parse_light(char **split, t_data *data);
void	parse_camera(char **split, t_data *data);
t_pos	parse_pos(char *split);
void	parse_ambient(char **split, t_data *data);
t_color	parse_color(char *split);
void	parse_plane(char **split, t_data *data);
void	parse_cylinder(char **split, t_data *data);
void	parse_sphere(char **split, t_data *data);
int		read_file(char *filename, t_list **file);
t_color	clamp_color(t_color color);
void	free_objs(t_data *data);
void	free_scene(t_data *data);
t_color	apply_gamma_correction(t_color color);
int		on_destroy(t_data *data);
void	color_add(t_color *color, t_color other);
int		color_to_int(t_color color);
void	color_scalar_div(t_color *color, int scalar);
bool	intersect_sphere(t_ray ray, t_sphere sphere, t_hit *hit);
bool	intersect_plane(t_ray ray, t_plane plane, t_hit *hit);
bool	intersect_cylinder(t_ray ray, t_cylinder cy, t_hit *hit);
void	rt_pixel_put(t_mlx *data, int x, int y, int color);
int		render_scene(t_data *data);
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
t_pos	calculate_ray_direction(int x, int y,
			t_camera *camera, double aspect_ratio);
t_ray	generate_ray(t_camera *cam, int x, int y);
t_color	set_color(t_hit hit, t_data *data);
t_color	compute_lighting(t_data *data, t_hit *hit, t_ray *ray);
int		find_closest_intersection(t_ray ray, t_data *data, t_hit *closest_hit);
bool	is_valid_int(const char *str);
bool	is_valid_double(const char *str);
bool	validate_file(t_list **file);
int		check_config(char *str);
bool	check_coordinates(char *split);
bool	check_vector(char *split);
bool	check_rgb(char *split);
void	free_split(char **split);
bool	exit_err(char *msg, char **split);
bool	validate_light(char **split);
bool	validate_camera(char **split);
bool	validate_ambient(char **split);
void	init_mlx(t_data *data);

#endif // !MINIRT>_H
