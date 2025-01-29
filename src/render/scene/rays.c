
#include "../../../headers/minirt.h"
#include "../../../headers/math.h"
#include "../../../headers/main.h"

t_pos	make_v_dir(t_data *rt, double i, double j);
t_ray	make_ray(t_data *rt, t_pos v_dir);

double	quadratic(double a, double d, double c)
{
	double	discriminant;
	double	t1;
	double	t2;

	discriminant = d * d - 4.0 * a * c;
	if (discriminant > 0)
	{
		t1 = (-d - sqrt(discriminant)) / (2.0 * a);
		t2 = (-d + sqrt(discriminant)) / (2.0 * a);
		if (t1 > 0)
			return (t1);
		else if (t2 > 0)
			return (t2);
	}
	return (0);
}

double	dist(const t_pos p1, const t_pos p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + \
	pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2)));
}

t_inter	*intersect_plane(t_ray *ray, t_plane *plane)
{
	t_inter	*inter;
	double	t;
	double	denom;

	inter = ft_calloc(1, sizeof(t_inter));
	plane->vec = vec_normalize(plane->vec);
	denom = vec_dot_cross(plane->vec, ray->dir, DOT).d;
	if (fabs(denom) < 1e-6)
	{
		inter->dist = INFINITY;
		return (inter);
	}
	t = vec_dot_cross(vec_operation(plane->pos, ray->origin, SUB), plane->pos, DOT).d / denom;
	if (t < 1e-4)
	{
		inter->dist = INFINITY;
		return (inter);
	}
	inter->type = PL;
	inter->pl = *plane;
	inter->dist = t;
	inter->point = vec_operation(ray->origin, vec_scalar(ray->dir, t, MULT), ADD);
	inter->point = vec_operation(inter->point, vec_scalar(inter->normal, 1e-4, MULT), ADD);
	inter->normal = plane->vec;
	return (inter);
}

t_inter	*intersect_sphere(t_ray *ray, t_sphere *sphere, int i)
{
	t_inter	*inter;
	t_pos	oc;
	double	t;

	inter = ft_calloc(1, sizeof(t_inter));
	oc = vec_operation(ray->origin, sphere->pos, SUB);
	t = quadratic(vec_dot_cross(ray->dir, ray->dir, DOT).d, 2.0 * \
	vec_dot_cross(oc, ray->dir, DOT).d, vec_dot_cross(oc, oc, DOT).d - ((sphere->diameter * sphere->diameter) / 4));
	if (t < 0)
	{
		inter->dist = INFINITY;
		return (inter);
	}
	inter->type = SP;
	inter->i = i;
	inter->sp = *sphere;
	inter->dist = t;
	inter->point = vec_operation(ray->origin, vec_scalar(ray->dir, t, MULT), ADD);
	inter->normal = vec_normalize(vec_operation(inter->point, sphere->pos, SUB));
	return (inter);
}

int	is_closest(t_inter *closest, t_inter *temp)
{
	if (temp->dist == INFINITY && closest->dist)
		return (0);
	if (temp->dist < closest->dist)
		return (1);
	return (0);
}

t_inter	*closest_inter(t_data *rt, t_ray *ray)
{
	t_inter		*closest;
	t_inter		*temp;
	int			i;

	i = 0;
	closest = ft_calloc(1, sizeof(t_inter));
	closest->dist = INFINITY;
	while (rt->sphere[i])
	{
		temp = intersect_sphere(ray, rt->sphere[i], i);
		if (closest && temp->dist > 0 && is_closest(closest, temp))
			free(closest);
		if (closest && temp->dist > 0 && is_closest(closest, temp))
			closest = temp;
		else
			free(temp);
		i++;
	}
	if (closest && temp->dist > 0 && is_closest(closest, temp))
		closest = temp;
	return (closest);
}

t_color	ambiance_color(t_color color, t_ambient amb)
{
	t_color	ambient_color;

	ambient_color.r = color.r * amb.color.r * amb.ratio / 255.0;
	ambient_color.g = color.g * amb.color.g * amb.ratio / 255.0;
	ambient_color.b = color.b * amb.color.b * amb.ratio / 255.0;
	return (ambient_color);
}

t_color	shadow_color(t_color color, double shadow_intensity)
{
	t_color	shadow_color;

	shadow_color.r = color.r * shadow_intensity;
	shadow_color.g = color.g * shadow_intensity;
	shadow_color.b = color.b * shadow_intensity;
	return (shadow_color);
}

t_color	diffuse_color(t_inter *inter, t_light *light, t_color color)
{
	t_color	diffuse_color;
	t_pos	light_dir;
	double	dot_product;
	double	diffuse_factor;

	light_dir = vec_normalize(vec_operation(light->pos, inter->point, SUB));
	dot_product = vec_dot_cross(inter->normal, light_dir, DOT).d;
	diffuse_factor = fmax(0.0, dot_product) * light->ratio;
	diffuse_color.r = fmin(inter->c.r * diffuse_factor, 255.0);
	diffuse_color.g = fmin(inter->c.g * diffuse_factor, 255.0);
	diffuse_color.b = fmin(inter->c.b * diffuse_factor, 255.0);
	color.r = fmin(color.r + diffuse_color.r, 255.0);
	color.g = fmin(color.g + diffuse_color.g, 255.0);
	color.b = fmin(color.b + diffuse_color.b, 255.0);
	return (color);
}

double	dst(t_pos *p1, t_pos *p2)
{
	double	dx;
	double	dy;
	double	dz;

	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	dz = p2->z - p1->z;
	return (sqrt(dx * dx + dy * dy + dz * dz));
}

t_color	get_color(t_inter *inter)
{
	t_color	background;

	background.r = 0;
	background.g = 0;
	background.b = 0;
	if (inter->type == SP)
		inter->c = inter->sp.color;
	else
		inter->c = background;
	return (inter->c);
}

void	saving_space(double *max_distance, t_inter	**closest_intersection, \
t_inter	*intersection, bool *is_in_shadow)
{
	*max_distance = intersection->dist;
	if (*closest_intersection)
		free(*closest_intersection);
	*closest_intersection = intersection;
	*is_in_shadow = true;
}

bool	inter_obj(t_data *rt, t_ray *ray, double max)
{
	t_inter		*close;
	t_inter		*inter;
	bool		is_in_shadow;
	int			i;

	close = ft_calloc(1, sizeof(t_inter));
	is_in_shadow = false;
	i = 0;
	while (rt->sphere[i])
	{
		if (i != 0)
		{
			inter = NULL;
			inter = intersect_sphere(ray, rt->sphere[i], i);
			if (inter && inter->dist > 1e-4 && inter->dist < max)
				saving_space(&max, &close, inter, &is_in_shadow);
			else
			{
				if (inter)
					free(inter);
			}
		}
		i++;
	}
	if (close)
		ray->inter = close;
	return (is_in_shadow);
}


t_color	lights_shadows(t_data *rt, t_inter *inter, t_color color)
{
	t_ray	to_light;
	t_color	final_color;
	bool	shad;

	final_color = ambiance_color(color, (*rt->ambient));
	to_light.origin = inter->point;
	to_light.dir = vec_normalize(vec_operation(rt->light->pos, inter->point, SUB));
	shad = inter_obj(rt, &to_light, dst(&to_light.origin, &rt->light->pos));
	if (!shad)
		final_color = diffuse_color(inter, rt->light, final_color);
	if (shad)
		final_color = shadow_color(final_color, 1);
	return (final_color);
}

/* creates all of the rays */
void	launch_rays(t_data *rt)
{
	double	x;
	double	y;
	t_ray	ray;
	t_color	final_color;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			ray = make_ray(rt, make_v_dir(rt, x, y));
			ray.inter = closest_inter(rt, &ray);
			final_color = get_color(ray.inter);
			final_color = lights_shadows(rt, ray.inter, final_color);
			mlx_pixel_put(rt->mlx->mlx, rt->mlx->window, x, y, (final_color.r << 16 | final_color.g << 8 | final_color.b));
		}
	}
}

t_ray	make_ray(t_data *rt, t_pos dir)
{
	t_ray	ray;

	ray.origin = rt->camera->pos;
	ray.dir = dir;
	return (ray);
}

t_pos	make_v_dir(t_data *rt, double x, double y)
{
	t_pos	v_dir;
	double	a;
	double	b;
	double	c;
	int		max;

	a = x + 0.5 - (WIDTH) * 0.5;
	b = y + 0.5 - (HEIGHT) * 0.5;
	if (WIDTH > HEIGHT)
		max = WIDTH;
	else
		max = HEIGHT;
	c = max / (2 * tan((rt->camera->fov * 0.5) * M_PI / 180.0));
	v_dir.x = 1 * a + 0 * b + 0 * c;
	v_dir.y = 0 * a + 1 * b + 0 * c;
	v_dir.z = 0 * a + 0 * b + 1 * c;
	return (vec_normalize(v_dir));
}
