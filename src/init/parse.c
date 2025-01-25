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
#include "../../headers/math.h"
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
t_ray generate_ray(int x, int y, t_camera *camera) {
    // Adjust the ray to cast from the camera through the scene
    // Example for simple orthographic projection
    double screen_x = (x - WIDTH / 2.0) / (WIDTH / 2.0);
    double screen_y = (y - HEIGHT / 2.0) / (HEIGHT / 2.0);
    
    // The camera is looking down the negative Z axis (could adjust for perspective)
    t_pos ray_direction = {screen_x, screen_y, -1};

    // Normalize the direction vector
    ray_direction = vec_normalize(ray_direction);

    // Create a ray from the camera's position in the direction
    t_ray ray = {camera->pos, ray_direction};
    return ray;
}

int ray_intersects_sphere(t_ray ray, t_sphere sphere, double *t) {
    t_pos oc = vec_operation(ray.origin, sphere.pos, SUB);
    u_result a = vec_dot_cross(ray.dir, ray.dir, DOT);
    u_result b = vec_dot_cross(oc, ray.dir, DOT);
    u_result c = vec_dot_cross(oc, oc, DOT);
	double d_b = b.d * 2.0;
	double c_d = c.d - (sphere.diameter * sphere.diameter / 4.0);
    double discriminant = d_b * d_b - 4.0 * a.d * c_d;

    if (discriminant > 0) {
        *t = (-b.d - sqrt(discriminant)) / (2.0 * a.d); // Closest intersection
        return 1;
    }
    return 0;
}

int ray_intersects_plane(t_ray ray, t_plane plane, double *t) {
	u_result a = vec_dot_cross(plane.vec, ray.dir, DOT);
    double denom = a.d;
    if (denom == 0) {
        return 0; // Ray is parallel to the plane
    }
    t_pos diff = vec_operation(plane.pos, ray.origin, SUB);
	u_result b = vec_dot_cross(diff, plane.vec, DOT);
    *t = b.d / denom;
    return *t >= 0; // Ensure intersection is in the right direction
}

int ray_intersects_cylinder(t_ray ray, t_cylinder cylinder, double *t) {
    // Vector from ray origin to the cylinder's base center
    t_pos oc = vec_operation(ray.origin, cylinder.pos, SUB);
    
    // The cylinder axis vector (normalized)
    t_pos axis = vec_normalize(cylinder.vec);
    
    // Adjust the ray's origin and direction for cylinder's local space
    t_pos ray_dir_proj = vec_operation(ray.dir, axis, SUB); // Project the ray direction
    t_pos ray_origin_proj = vec_operation(oc, axis, SUB); // Project the ray origin

	u_result a = vec_dot_cross(ray_dir_proj, ray_dir_proj, DOT);
	u_result b = vec_dot_cross(ray_origin_proj, ray_dir_proj, DOT);
	double b1 = b.d * 2.0;
	u_result c = vec_dot_cross(ray_origin_proj, ray_origin_proj, DOT);
    double c1 = c.d - (cylinder.diameter / 2.0) * (cylinder.diameter / 2.0);
    double discriminant = b1 * b1 - 4.0 * a.d * c1;

    if (discriminant > 0) {
        *t = (-b1 - sqrt(discriminant)) / (2.0 * a.d);
        return 1; // Intersection exists
    }
    
    return 0; // No intersection
}

t_color calculate_lighting(t_pos intersection, t_light light, t_sphere sphere) {
    t_pos normal = vec_normalize(vec_operation(intersection, sphere.pos, SUB)); // Normal at intersection
    t_pos light_dir = vec_normalize(vec_operation(light.pos, intersection, SUB)); // Light direction
    
    // Simple diffuse shading (Lambertian shading)
	u_result dot = vec_dot_cross(normal, light_dir, DOT);
    double intensity = fmax(dot.d, 0.0); // Diffuse term
    int r = (int)(sphere.color.r * intensity * light.ratio);
    int g = (int)(sphere.color.g * intensity * light.ratio);
    int b = (int)(sphere.color.b * intensity * light.ratio);
    
    return (t_color){r, g, b}; // Return the calculated color
}

void render_scene(t_mlx *mlx, t_data *data) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
			t_ray ray = generate_ray(x, y, data->camera); // Generate a ray for this pixel
            double t = 0;
            int color = 0;

			t_sphere sphere = (t_sphere){.pos = data->plane->pos, .diameter = data->sphere->diameter, .color = data->sphere->color};
            // Check for intersections with the sphere
            if (ray_intersects_sphere(ray, sphere, &t)) {
                color = (255 << 16); // Example color for intersection with sphere (red)
            }
            // Check for intersections with the plane
            else if (ray_intersects_plane(ray, (*data->plane), &t)) {
                color = (0 << 16) | (255 << 8); // Example color for intersection with plane (green)
            }
            // Check for intersections with the cylinder
            else if (ray_intersects_cylinder(ray, (*data->cylinder), &t)) {
                color = (0 << 8); // Example color for intersection with cylinder (blue)
            }
            else {
                color = 0x000000; // Background color (black if no intersection)
            }
			mlx_pixel_put(mlx->mlx, mlx->window, x, y, color); // Draw pixel
        }
    }
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
    t_mlx mlx;

	mlx.mlx = mlx_init();
    mlx.window = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "MiniRT Ray Tracing");
    mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
    mlx.data = (int *)mlx_get_data_addr(mlx.img, &(int){32}, &(int){WIDTH * 4}, &(int){0});
	/*print_data(data);*/
	render_scene(&mlx, data);
    mlx_loop(mlx.mlx);
	return (true);
}
