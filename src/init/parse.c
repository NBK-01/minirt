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
	(void)data;
	/*data->plane = plane;*/
}

void	parse_sphere(char **split, t_objects *obj)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	sphere->ident = ft_strdup("sp");
	sphere->pos = parse_pos(split[1]);
	sphere->diameter = ft_atof(split[2]);
	sphere->color = parse_color(split[3]);
	obj->type.sp = sphere;
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
	(void)data;
	/*data->cylinder = cyl;*/
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
		parse_sphere(split, data->objs);
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
	printf("Ray origin: (%f, %f, %f), Ray direction: (%f, %f, %f)\n", 
        camera->pos.x, camera->pos.y, camera->pos.z, 
        ray.dir.x, ray.dir.y, ray.dir.z);
    return ray;
}

/*int ray_intersects_sphere(t_ray ray, t_sphere sphere, double *t) {*/
/*    t_pos oc = vec_operation(ray.origin, sphere.pos, SUB);*/
/*    u_result a = vec_dot_cross(ray.dir, ray.dir, DOT);*/
/*    u_result b = vec_dot_cross(oc, ray.dir, DOT);*/
/*    u_result c = vec_dot_cross(oc, oc, DOT);*/
/*	double d_b = b.d * 2.0;*/
/*	double c_d = c.d - (sphere.diameter * sphere.diameter / 4.0);*/
/*    double discriminant = d_b * d_b - 4.0 * a.d * c_d;*/
/**/
/*    if (discriminant > 0) {*/
/*        *t = (-b.d - sqrt(discriminant)) / (2.0 * a.d); // Closest intersection*/
/*        return 1;*/
/*    }*/
/*    return 0;*/
/*}*/
/*int ray_intersects_sphere(t_ray ray, t_sphere sphere, double *t) {*/
/*    t_pos oc = vec_operation(ray.origin, sphere.pos, SUB);*/
/*    u_result a = vec_dot_cross(ray.dir, ray.dir, DOT);*/
/*    u_result b = vec_dot_cross(oc, ray.dir, DOT);*/
/*    u_result c = vec_dot_cross(oc, oc, DOT);*/
/**/
/*    // Print values*/
/*    printf("Ray origin: (%f, %f, %f), Ray direction: (%f, %f, %f)\n", */
/*            ray.origin.x, ray.origin.y, ray.origin.z, */
/*            ray.dir.x, ray.dir.y, ray.dir.z);*/
/*    printf("Sphere position: (%f, %f, %f), Diameter: %f\n", */
/*            sphere.pos.x, sphere.pos.y, sphere.pos.z, sphere.diameter);*/
/*    printf("a: %f, b: %f, c: %f\n", a.d, b.d, c.d);*/
/**/
/*    double d_b = b.d * 2.0;*/
/*    double c_d = c.d - (sphere.diameter * sphere.diameter / 4.0);*/
/*    double discriminant = d_b * d_b - 4.0 * a.d * c_d;*/
/**/
/*    printf("Discriminant: %f\n", discriminant);*/
/*    printf("Intersection at t = %f\n", *t);*/
/**/
/*    if (discriminant > 0) {*/
/*        *t = (-b.d - sqrt(discriminant)) / (2.0 * a.d); // Closest intersection*/
/*        printf("Intersection at t = %f\n", *t);*/
/*        return 1;*/
/*    }*/
/*    return 0;*/
/*}*/

int ray_intersects_sphere(t_ray ray, t_sphere sphere, double *t) {
    // Calculate vector from ray origin to sphere center
    t_pos oc = vec_operation(ray.origin, sphere.pos, SUB);

    // Calculate the coefficients of the quadratic equation
    double a = vec_dot_cross(ray.dir, ray.dir, DOT).d;  // Should always be 1 if the ray direction is normalized
    double b = 2.0 * vec_dot_cross(oc, ray.dir, DOT).d;
    double c = vec_dot_cross(oc, oc, DOT).d - (sphere.diameter * sphere.diameter / 4);

    // Calculate the discriminant
    double discriminant = b * b - 4.0 * a * c;

	printf("HELLOOOO %f\n\n", discriminant);
    // If the discriminant is positive, there are intersections
    if (discriminant > 0) {
        // Compute the two solutions (roots) of the quadratic equation
        double sqrt_discriminant = sqrt(discriminant);
        double t1 = (-b - sqrt_discriminant) / (2.0 * a);
        double t2 = (-b + sqrt_discriminant) / (2.0 * a);

        // We return the closest intersection point (positive t)
        if (t1 > 0) {
            *t = t1;
        } else if (t2 > 0) {
            *t = t2;
        } else {
            return 0;  // Both intersections are behind the ray origin
        }

        return 1;  // Intersection found
    }

    return 0;  // No intersection
}

t_color calculate_lighting(t_pos intersection, t_light light, t_sphere sphere, t_data *data) {
    t_pos normal = vec_normalize(vec_operation(intersection, sphere.pos, SUB)); // Normal at intersection
    t_pos light_dir = vec_normalize(vec_operation(light.pos, intersection, SUB)); // Light direction
    
    // Simple diffuse shading (Lambertian shading)
    u_result dot = vec_dot_cross(normal, light_dir, DOT);
    double intensity = fmax(dot.d, 0.0); // Diffuse term
    
    // Now check for shadows: Cast a ray from the intersection point to the light
    t_ray shadow_ray = {intersection, light_dir};
    double t_shadow = 0;
    int is_in_shadow = 0;

    // Check if the shadow ray intersects any object (simplified for spheres)
    if (ray_intersects_sphere(shadow_ray, (*data->objs->type.sp), &t_shadow) && t_shadow > 0.001) {
        is_in_shadow = 1; // The point is in shadow
    }

    // If the point is not in shadow, apply the light intensity
    if (is_in_shadow) {
        intensity = 0.2; // Fully in shadow, no diffuse light
    }

    int r = (int)(sphere.color.r * intensity * light.ratio);
    int g = (int)(sphere.color.g * intensity * light.ratio);
    int b = (int)(sphere.color.b * intensity * light.ratio);
    
    return (t_color){r, g, b}; // Return the calculated color
}

t_pos reflect(t_pos incident, t_pos normal) {
    double dot = vec_dot_cross(incident, normal, DOT).d;
    return vec_operation(incident, vec_scalar(normal, 2.0 * dot, MULT), SUB);
}

t_color calculate_reflection(t_ray ray, t_pos intersection, t_pos normal, t_light light, t_sphere sphere, t_data *data, int depth) {
    // Base case: If recursion depth is too high, stop
    if (depth > 5) {
        return (t_color){0, 0, 0}; // Black if too many reflections
    }

    // Calculate reflection vector
    t_pos reflect_dir = reflect(ray.dir, normal);

    // Create reflection ray
    t_ray reflection_ray = {intersection, reflect_dir};

    // Find intersection with scene (for reflection)
    double t_reflection = 0;
    t_sphere reflected_sphere = sphere; // Simplified for one sphere in this example
    if (ray_intersects_sphere(reflection_ray, reflected_sphere, &t_reflection) && t_reflection > 0.001) {
        // If intersection found, calculate the color from the reflection
        t_pos reflection_intersection = vec_operation(ray.origin, vec_scalar(ray.dir, t_reflection, MULT), ADD);
        /*t_pos reflected_normal = vec_normalize(vec_operation(reflection_intersection, reflected_sphere.pos, SUB));*/

        // Compute lighting for the reflection
        t_color reflected_color = calculate_lighting(reflection_intersection, light, reflected_sphere, data);
        
        // Combine reflected color with the original color
        return reflected_color; // Modify as needed to blend reflection with original color
    }

    return (t_color){0, 0, 0}; // Return black if no reflection intersection
}



void render_scene(t_mlx *mlx, t_data *data) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            t_ray ray = generate_ray(x, y, data->camera); // Generate a ray for this pixel
            double t = 0;
            t_color color = {50, 50, 50};

			while (data->objs)
			{
            if (ray_intersects_sphere(ray, (*data->objs->type.sp), &t)) {
				printf("Intersection detected at t = %f\n", t);
                t_pos intersection = vec_operation(ray.origin, vec_scalar(ray.dir, t, MULT), ADD);
                t_pos normal = vec_normalize(vec_operation(intersection, (data->objs->type.sp)->pos, SUB));

                color = calculate_lighting(intersection, (*data->light), (*data->objs->type.sp), data);

                if (0.3 > 0.0) {
                    t_color reflection_color = calculate_reflection(ray, intersection, normal, (*data->light), (*data->objs->type.sp), data, 0);

                    color.r = fmin(color.r + reflection_color.r * 0.3, 255);
                    color.g = fmin(color.g + reflection_color.g * 0.3, 255);
                    color.b = fmin(color.b + reflection_color.b * 0.3, 255);
                }
            }
			data->objs = data->objs->next;
			}
			mlx_pixel_put(mlx->mlx, mlx->window, x, y, (color.r << 16) | (color.g << 8) | color.b); // Red color for testing
        }
    }
}

t_objects	*lstnew(char *content)
{
	t_objects	*node;

	node = ft_calloc(1, sizeof(t_objects));
	(void)content;
	return (node);
}

t_objects	*lstlast(t_objects *lst)
{
	t_objects	*temp;

	temp = lst;
	if (!temp)
		return (NULL);
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}


void	lstadd_back(t_objects **lst, t_objects *new)
{
	t_objects	*end;

	if (lst == NULL)
		return ;
	while (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	end = lstlast(*lst);
	end->next = new;
}

bool	parse_file(t_list **file, t_data *data)
{
	t_list	*tmp;
	char	**split;
	t_objects	*current;

	tmp = (*file);
	data->objs = ft_calloc(1, sizeof(t_objects));
	current = data->objs; // Initialize current to the first object

while (tmp)
{
    split = ft_split(tmp->content, " \t");
    if (!split)
        return (ft_putstr_fd(RED "Error: failed to split line\n" RESET, 2), false);
    
    parse_line(split, data);  // Assuming parse_line updates data->objs

    if (tmp->next)  // If there's another item in the list
    {
        current->next = lstnew(NULL);  // Create a new node for the next object
        current = current->next;  // Move current to the next node
    }

    tmp = tmp->next;  // Move to the next element in the list
}
	/*remvoe later*/
	/*t_mlx mlx;*/

	/*mlx.mlx = mlx_init();*/
	/*mlx.window = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "MiniRT Ray Tracing");*/
	/*mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);*/
	/*mlx.data = (int *)mlx_get_data_addr(mlx.img, &(int){32}, &(int){WIDTH * 4}, &(int){0});*/
	print_data(data);
	/*render_scene(&mlx, data);*/
	/*mlx_loop(mlx.mlx);*/
	return (true);
}
