/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:08:25 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/02/22 00:13:46 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/main.h"
#include "../../headers/math.h"
#include "../../headers/minirt.h"

bool	intersection(t_ray ray, t_data *data, t_hit *hit, t_ident id, int i)
{
	if (id == SP)
		return (intersect_sphere(ray, *data->objects->spheres[i], hit));
	else if (id == PL)
		return (intersect_plane(ray, *data->objects->planes[i], hit));
	else if (id == CY)
		return (intersect_cylinder(ray, *data->objects->cylinders[i], hit));
	else
		return (ft_putstr_fd("object does not exist", 2), 0);
}

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
	t_pos V = cy.vec;
	t_pos CO = vec_operation(ray.origin, cy.pos, SUB);
	double radius = cy.diameter / 2.0;
	double height = cy.height;
	double dv = vec_dot_cross(CO, V, DOT).d;
	double Dv = vec_dot_cross(ray.dir, V, DOT).d;

	t_pos A = vec_operation(CO, vec_scalar(V, dv, MULT), SUB);
	t_pos B = vec_operation(ray.dir, vec_scalar(V, Dv, MULT), SUB);
	double a = vec_dot_cross(B, B, DOT).d;
	double b = 2.0 * vec_dot_cross(A, B, DOT).d;
	double c = vec_dot_cross(A, A, DOT).d - (radius * radius);

	double disc = b * b - 4 * a * c;
	if (disc < EPSILON)
		return (false);

	double sqrt_disc = sqrt(disc);
	double t0 = (-b - sqrt_disc) / (2 * a);
	double t1 = (-b + sqrt_disc) / (2 * a);

	double t_curved = INFINITY;
	if (t0 > EPSILON) {
		double s = dv + t0 * Dv;
		if (s >= -height / 2 && s <= height / 2)
			t_curved = t0;
	}
	if (t1 > EPSILON && t1 < t_curved) {
		double s = dv + t1 * Dv;
		if (s >= -height / 2 && s <= height / 2)
			t_curved = t1;
	}

	double t_cap = INFINITY;
	t_pos normal_cap;
	t_pos cap_center;

	if (fabs(Dv) > EPSILON)
	{
		double t_bottom = (-dv - height / 2) / Dv;
		if (t_bottom > EPSILON) {
			t_pos P = vec_operation(ray.origin, vec_scalar(ray.dir, t_bottom, MULT), ADD);
			cap_center = vec_operation(cy.pos, vec_scalar(V, -height / 2, MULT), ADD);
			t_pos P_to_center = vec_operation(P, cap_center, SUB);
			if (vec_dot_cross(P_to_center, P_to_center, DOT).d <= radius * radius && t_bottom < t_cap) {
				t_cap = t_bottom;
				normal_cap = vec_scalar(V, -1.0, MULT);
			}
		}

		double t_top = (height / 2 - dv) / Dv;
		if (t_top > EPSILON) {
			t_pos P = vec_operation(ray.origin, vec_scalar(ray.dir, t_top, MULT), ADD);
			cap_center = vec_operation(cy.pos, vec_scalar(V, height / 2, MULT), ADD);
			t_pos P_to_center = vec_operation(P, cap_center, SUB);
			if (vec_dot_cross(P_to_center, P_to_center, DOT).d <= radius * radius && t_top < t_cap) {
				t_cap = t_top;
				normal_cap = V;
			}
		}
	}
	double t_min = fmin(t_curved, t_cap);
	if (t_min >= INFINITY)
		return (false);

	hit->t = t_min;
	hit->point = vec_operation(ray.origin, vec_scalar(ray.dir, t_min, MULT), ADD);

	if (t_min == t_curved) {
		double s = dv + t_min * Dv;
		t_pos C_proj = vec_operation(cy.pos, vec_scalar(V, s, MULT), ADD);
		hit->normal = vec_normalize(vec_operation(hit->point, C_proj, SUB));
	} else {
		hit->normal = vec_normalize(normal_cap);
	}

	hit->color = cy.color;
	return (true);
}

int	find_closest_intersection(t_ray ray, t_data *data, t_hit *closest_hit)
{
	t_hit	temp_hit;
	int		hit_anything;
	int		i;

	closest_hit->t = INFINITY;
	hit_anything = 0;
	i = -1;
	while (++i < data->spheres_count)
	{
		if (intersection(ray, data, &temp_hit, SP, i)
			&& temp_hit.t < closest_hit->t)
		{
			*closest_hit = temp_hit;
			hit_anything = 1;
		}
	}
	i = -1;
	while (++i < data->planes_count)
	{
		if (intersection(ray, data, &temp_hit, PL, i)
			&& temp_hit.t < closest_hit->t)
		{
			*closest_hit = temp_hit;
			hit_anything = 1;
		}
	}
	i = -1;
	while (++i < data->cylinders_count)
	{
		if (intersection(ray, data, &temp_hit, CY, i)
			&& temp_hit.t < closest_hit->t)
		{
			*closest_hit = temp_hit;
			hit_anything = 1;
		}
	}
	return (hit_anything);
}
