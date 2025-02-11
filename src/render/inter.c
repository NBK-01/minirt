#include "../../headers/main.h"
#include "../../headers/math.h"
#include "../../headers/minirt.h"
#include <stdbool.h>

static bool	intersect_sphere(t_ray ray, t_sphere sphere, t_hit *hit);
static bool	intersect_plane(t_ray ray, t_plane plane, t_hit *hit);

bool	intersection(t_ray ray, t_data *data, t_hit *hit, t_ident id, int i)
{
	if (id == SP)
		return (intersect_sphere(ray, *data->objects->spheres[i], hit)); // TO REVISE
	else if (id == PL)
		return (intersect_plane(ray, *data->objects->planes[i], hit)); // TO REVISE
	else if (id == CY)
		return (0); //later later
	else
		return (ft_putstr_fd("object does not exist", 2), 0);
}

static bool	intersect_plane(t_ray ray, t_plane plane, t_hit *hit)
{
	double	denom;
    t_pos	diff;


    denom = vec_dot_cross(plane.vec, ray.dir, DOT).d;
    if (fabs(denom) < 1e-6)
	{
        return (false);
	}
	diff = vec_operation(plane.pos, ray.origin, SUB);
    hit->t = vec_dot_cross(diff, plane.vec, DOT).d / denom;
    if (hit->t < EPSILON)
        return (false);
    hit->point = vec_operation(ray.origin, vec_scalar(ray.dir, hit->t, MULT), ADD);
    hit->normal = vec_normalize(plane.vec);
    hit->color = plane.color;
    return (true);
}

static bool	intersect_sphere(t_ray ray, t_sphere sphere, t_hit *hit)
{
	t_quad	quad;

	quad.oc = vec_operation(ray.origin, sphere.pos, SUB);
	quad.rad = sphere.diameter * 0.5;
    quad.a = vec_dot_cross(ray.dir, ray.dir, DOT).d;
    quad.b = 2.0 * vec_dot_cross(quad.oc, ray.dir, DOT).d;
    quad.c = vec_dot_cross(quad.oc, quad.oc, DOT).d - (quad.rad * quad.rad);
	hit->t = quadratic(quad.a, quad.b, quad.c);
    if (hit->t == 0)
        return (false);
    hit->point = vec_operation(ray.origin, vec_scalar(ray.dir, hit->t, MULT), ADD);
    hit->normal = vec_normalize(vec_operation(hit->point, sphere.pos, SUB));
    hit->color = sphere.color;
    return (true);
}

int find_closest_intersection(t_ray ray, t_data *data, t_hit *closest_hit)
{
    t_hit temp_hit;
    closest_hit->t = INFINITY;
    int hit_anything = 0;
	int i = -1;

	while (++i < data->spheres_count)
	{
		if (intersection(ray, data, &temp_hit, SP, i) && temp_hit.t < closest_hit->t)
		{
			*closest_hit = temp_hit;
			hit_anything = 1;
		}
	}
	i = -1;
	while (++i < data->planes_count)
	{
		if (intersection(ray, data, &temp_hit, PL, i) && temp_hit.t < closest_hit->t)
		{
			*closest_hit = temp_hit;
			hit_anything = 1;
		}
	}
    return (hit_anything);
}

