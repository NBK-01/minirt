/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:08:25 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/02/23 19:25:43 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/main.h"
#include "../../headers/math.h"
#include "../../headers/minirt.h"
#include <math.h>
#include <stdbool.h>

bool	intersect_plane(t_ray ray, t_plane plane, t_hit *hit)
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
	hit->point = vec_operation(ray.origin,
			vec_scalar(ray.dir, hit->t, MULT), ADD);
	hit->normal = vec_normalize(plane.vec);
	hit->color = plane.color;
	return (true);
}

bool	intersect_sphere(t_ray ray, t_sphere sphere, t_hit *hit)
{
	t_quad	quad;

	quad.oc = vec_operation(ray.origin, sphere.pos, SUB);
	quad.rad = sphere.diameter * 0.5;
	quad.a = vec_dot_cross(ray.dir, ray.dir, DOT).d;
	quad.b = 2.0 * vec_dot_cross(quad.oc, ray.dir, DOT).d;
	quad.c = vec_dot_cross(quad.oc, quad.oc, DOT).d - (quad.rad * quad.rad);
	hit->t = quadratic(quad.a, quad.b, quad.c);
	if (hit->t == 0)
	{
		hit->color = (t_color){0, 0, 0};
		return (false);
	}
	hit->point = vec_operation(ray.origin,
			vec_scalar(ray.dir, hit->t, MULT), ADD);
	hit->normal = vec_normalize(vec_operation(hit->point, sphere.pos, SUB));
	hit->color = sphere.color;
	return (true);
}

bool	intersect_cylinder(t_ray ray, t_cylinder cy, t_hit *hit)
{
	double	d[2];

	d[0] = vec_dot_cross(vec_operation(ray.origin, cy.pos, SUB), cy.vec, DOT).d;
	d[1] = vec_dot_cross(ray.dir, cy.vec, DOT).d;
	set_hit_info(hit, ray, cy, d);
	return (true);
}

static void	check_hit(t_data *data, t_hit temp_hit,
				t_hit **closest_hit, t_ray ray)
{
	int	i;

	i = -1;
	while (++i < data->cylinders_count)
	{
		if (intersect_cylinder(ray, *data->objects->cylinders[i], &temp_hit)
			&& temp_hit.t < (*closest_hit)->t)
		{
			**closest_hit = temp_hit;
			(*closest_hit)->hit = 1;
		}
	}
	i = -1;
	while (++i < data->planes_count)
	{
		if (intersect_plane(ray, *data->objects->planes[i], &temp_hit)
			&& temp_hit.t < (*closest_hit)->t)
		{
			**closest_hit = temp_hit;
			(*closest_hit)->hit = 1;
		}
	}
}

int	find_closest_intersection(t_ray ray, t_data *data, t_hit *closest_hit)
{
	t_hit	temp_hit;
	int		i;

	closest_hit->t = INFINITY;
	closest_hit->hit = 0;
	i = -1;
	while (++i < data->spheres_count)
	{
		if (intersect_sphere(ray, *data->objects->spheres[i], &temp_hit)
			&& temp_hit.t < closest_hit->t)
		{
			*closest_hit = temp_hit;
			closest_hit->hit = 1;
		}
	}
	check_hit(data, temp_hit, &closest_hit, ray);
	return (closest_hit->hit);
}
