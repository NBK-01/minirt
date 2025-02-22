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
#define CURVED 0        // Index for curved surface hits
#define CAP1 1          // Index for bottom cap hits
#define CAP2 2          // Index for top cap hits
#define MIN 3           // Index for minimum valid hit

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


static t_quadratic	get_cylinder_quad(t_pos co, t_pos v, t_pos dir, t_cylinder cy)
{
    t_quadratic  q;
    const double radius = cy.diameter / 2.0;
    t_pos        a;
    t_pos        b;

    a = vec_operation(co, vec_scalar(v, vec_dot_cross(co, v, DOT).d, SUB);
    b = vec_operation(dir, vec_scalar(v, vec_dot_cross(dir, v, DOT).d, SUB);
    q.a = vec_dot_cross(b, b, DOT).d;
    q.b = 2.0 * vec_dot_cross(a, b, DOT).d;
    q.c = vec_dot_cross(a, a, DOT).d - (radius * radius);
    return (q);
}

static double	check_curved_hit(t_solution s, t_cylinder cy, double dv, double Dv)
{
    double t;
    double s_val;

    t = INFINITY;
    if (s.t0 > EPSILON)
    {
        s_val = dv + s.t0 * Dv;
        if (s_val >= -cy.height/2 && s_val <= cy.height/2)
            t = s.t0;
    }
    if (s.t1 > EPSILON && s.t1 < t)
    {
        s_val = dv + s.t1 * Dv;
        if (s_val >= -cy.height/2 && s_val <= cy.height/2)
            t = s.t1;
    }
    return (t);
}

static void	check_caps(t_ray ray, t_cylinder cy, double dv_Dv[2], double t_cap[2])
{
    const double h = cy.height;
    t_pos        centers[2] = {
        vec_operation(cy.pos, vec_scalar(cy.vec, -h/2, MULT), ADD),
        vec_operation(cy.pos, vec_scalar(cy.vec, h/2, MULT), ADD)
    };
    double      t;
    t_pos       p;

    for (int i = 0; i < 2; i++)
    {
        t = (i * h - h/2 - dv_Dv[0]) / dv_Dv[1];
        if (t <= EPSILON)
            continue;
        p = vec_operation(ray.origin, vec_scalar(ray.dir, t, MULT), ADD);
        if (vec_dot_cross(vec_operation(p, centers[i], SUB), 
            vec_operation(p, centers[i], SUB), DOT).d <= pow(cy.diameter/2, 2))
            t_cap[i] = t;
    }
}

bool	intersect_cylinder(t_ray ray, t_cylinder cy, t_hit *hit)
{
    const t_pos  co = vec_operation(ray.origin, cy.pos, SUB);
    const double dv = vec_dot_cross(co, cy.vec, DOT).d;
    const double Dv = vec_dot_cross(ray.dir, cy.vec, DOT).d;
    t_quadratic  q = get_cylinder_quad(co, cy.vec, ray.dir, cy);
    t_solution   s = solve_quadratic(q.a, q.b, q.c);
    double       t[3];

    t[CURVED] = check_curved_hit(s, cy, dv, Dv);
    t[CAP1] = INFINITY;
    t[CAP2] = INFINITY;
    check_caps(ray, cy, (double[2]){dv, Dv}, &t[CAP1]);
    t[MIN] = fmin(fmin(t[CURVED], t[CAP1]), t[CAP2]);
    if (t[MIN] >= INFINITY)
        return (false);
    hit->t = t[MIN];
    hit->point = vec_operation(ray.origin, vec_scalar(ray.dir, t[MIN], MULT), ADD);
    hit->normal = (t[MIN] == t[CURVED]) ? 
        vec_normalize(vec_operation(hit->point, 
            vec_operation(cy.pos, vec_scalar(cy.vec, dv + t[MIN]*Dv, MULT), ADD), SUB)) :
        vec_normalize(vec_scalar(cy.vec, (t[MIN] == t[CAP1]) ? -1 : 1, MULT));
    hit->color = cy.color;
    return (true);
}

static bool	check_hit(t_data *data, t_hit temp_hit, t_hit *closest_hit, t_ray ray)
{
	int	i;

	i = -1;
	while (++i < data->cylinders_count)
	{
		if (intersect_cylinder(ray, *data->objects->cylinders[i], &temp_hit)
			&& temp_hit.t < closest_hit->t)
		{
			*closest_hit = temp_hit;
			return (true);
		}
	}
	i = -1;
	while (++i < data->planes_count)
	{
		if (intersect_plane(ray, *data->objects->planes[i], &temp_hit)
			&& temp_hit.t < closest_hit->t)
		{
			*closest_hit = temp_hit;
			return (true);
		}
	}
	return (false);
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
		if (intersect_sphere(ray, *data->objects->spheres[i], &temp_hit)
			&& temp_hit.t < closest_hit->t)
		{
			*closest_hit = temp_hit;
			hit_anything = 1;
		}
	}
	if (check_hit(data, temp_hit, closest_hit, ray))
		hit_anything = 1;
	return (hit_anything);
}
