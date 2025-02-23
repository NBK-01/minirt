/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cyl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:25:03 by excelsior         #+#    #+#             */
/*   Updated: 2025/02/23 19:25:41 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/main.h"
#include "../../headers/math.h"
#include <stdbool.h>

static t_quad	calculate_quadratic_coefficients(t_ray ray,
					t_cylinder cy, double d[2])
{
	t_quad	quad;
	t_pos	co;
	t_pos	a;
	t_pos	b;

	co = vec_operation(ray.origin, cy.pos, SUB);
	a = vec_operation(co, vec_scalar(cy.vec, d[0], MULT), SUB);
	b = vec_operation(ray.dir, vec_scalar(cy.vec, d[1], MULT), SUB);
	quad.a = vec_dot_cross(b, b, DOT).d;
	quad.b = 2.0 * vec_dot_cross(a, b, DOT).d;
	quad.c = vec_dot_cross(a, a, DOT).d
		- (cy.diameter / 2.0 * cy.diameter / 2.0);
	return (quad);
}

static double	check_curved_surface(t_quad quad, double d[2], double height)
{
	double	disc;
	double	curved;
	double	t0;
	double	t1;
	double	s;

	curved = INFINITY;
	disc = quad.b * quad.b - 4 * quad.a * quad.c;
	t0 = (-quad.b - sqrt(disc)) / (2 * quad.a);
	t1 = (-quad.b + sqrt(disc)) / (2 * quad.a);
	if (disc < EPSILON)
		return (INFINITY);
	if (t0 > EPSILON)
	{
		s = d[0] + t0 * d[1];
		if (s >= -height / 2 && s <= height / 2)
			curved = t0;
	}
	if (t1 > EPSILON && t1 < curved)
	{
		s = d[0] + t1 * d[1];
		if (s >= -height / 2 && s <= height / 2)
			curved = t1;
	}
	return (curved);
}

static void	check_cap_top(t_ray ray, t_cylinder cy, double d[2], t_cap *cap)
{
	t_pos	p;
	t_pos	center;
	t_pos	p_to_center;
	double	radius;

	radius = cy.diameter / 2.0;
	if ((cy.height / 2 - d[0]) / d[1] > EPSILON)
	{
		p = vec_operation(ray.origin, vec_scalar(ray.dir,
					(cy.height / 2 - d[0]), MULT), ADD);
		center = vec_operation(cy.pos,
				vec_scalar(cy.vec, cy.height / 2, MULT), ADD);
		p_to_center = vec_operation(p, center, SUB);
		if (vec_dot_cross(p_to_center, p_to_center, DOT).d <= radius
			* radius && (cy.height / 2 - d[0]) < cap->cap)
		{
			cap->cap = (cy.height / 2 - d[0]) / d[1];
			cap->normal_cap = cy.vec;
		}
	}
}

static void	check_cap_intersection(t_ray ray, t_cylinder cy,
				double d[2], t_cap *cap)
{
	double	radius;
	t_pos	p;
	t_pos	center;
	t_pos	p_to_center;

	cap->cap = INFINITY;
	radius = cy.diameter / 2.0;
	if (fabs(d[1]) > EPSILON)
	{
		if ((-d[0] - cy.height / 2) / d[1] > EPSILON)
		{
			p = vec_operation(ray.origin, vec_scalar(ray.dir,
						(-d[0] - cy.height / 2) / d[1], MULT), ADD);
			center = vec_operation(cy.pos,
					vec_scalar(cy.vec, -cy.height / 2, MULT), ADD);
			p_to_center = vec_operation(p, center, SUB);
			if (vec_dot_cross(p_to_center, p_to_center, DOT).d <= radius
				* radius && (-d[0] - cy.height / 2) / d[1] < cap->cap)
			{
				cap->cap = (-d[0] - cy.height / 2) / d[1];
				cap->normal_cap = vec_scalar(cy.vec, -1.0, MULT);
			}
		}
		check_cap_top(ray, cy, d, cap);
	}
}

void	set_hit_info(t_hit *hit, t_ray ray, t_cylinder cy, double d[2])
{
	t_cap	caps;
	double	curved;
	t_quad	quad;

	quad = calculate_quadratic_coefficients(ray, cy, d);
	curved = check_curved_surface(quad, d, cy.height);
	check_cap_intersection(ray, cy, d, &caps);
	hit->t = fmin(curved, caps.cap);
	hit->point = vec_operation(ray.origin,
			vec_scalar(ray.dir, fmin(curved, caps.cap), MULT), ADD);
	if (fmin(curved, caps.cap) == curved)
		hit->normal = vec_normalize(vec_operation(hit->point,
					vec_operation(cy.pos, vec_scalar(cy.vec, d[0]
							+ fmin(curved, caps.cap) * d[1], MULT), ADD), SUB));
	else
		hit->normal = vec_normalize(caps.normal_cap);
	hit->color = cy.color;
}
