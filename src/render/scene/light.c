/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:29:22 by nkanaan           #+#    #+#             */
/*   Updated: 2025/02/21 15:29:23 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minirt.h"
#include "../../../headers/main.h"
#include "../../../headers/math.h"

static bool	shadow_intersect(t_data	*data, t_hit *shadow_hit,
		double light_distance, t_ray shadow_ray)
{
	int	i;

	i = -1;
	while (++i < data->spheres_count)
	{
		if (intersect_sphere(shadow_ray, *data->objects->spheres[i], shadow_hit)
			&& shadow_hit->t > 0 && shadow_hit->t < light_distance)
			return (true);
	}
	i = -1;
	while (++i < data->planes_count)
	{
		if (intersect_plane(shadow_ray, *data->objects->planes[i], shadow_hit)
			&& shadow_hit->t > 0 && shadow_hit->t < light_distance)
			return (true);
	}
	i = -1;
	while (++i < data->cylinders_count)
	{
		if (intersect_cylinder(shadow_ray,
				*data->objects->cylinders[i], shadow_hit)
			&& shadow_hit->t > 0 && shadow_hit->t < light_distance)
			return (true);
	}
	return (false);
}

bool	trace_shadows(t_data *data, t_pos hit_point)
{
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	t_pos	light_dir;
	double	light_distance;
	bool	ret;

	if (!data->light)
		return (false);
	light_dir = vec_operation(data->light->pos, hit_point, SUB);
	light_distance = sqrt(light_dir.x * light_dir.x + light_dir.y
			* light_dir.y + light_dir.z * light_dir.z);
	light_dir = vec_normalize(light_dir);
	shadow_ray.origin = vec_operation(hit_point,
			vec_scalar(light_dir, EPSILON, MULT), ADD);
	shadow_ray.dir = light_dir;
	ret = shadow_intersect(data, &shadow_hit, light_distance, shadow_ray);
	return (ret);
}

double	calc_specular(t_hit *hit, t_pos light_dir, t_ray *ray,
			t_data *data)
{
	t_pos	reflect_dir;
	t_pos	view_dir;
	double	specular_factor;
	double	specular_intensity;
	double	dot_nl;

	dot_nl = vec_dot_cross(hit->normal, light_dir, DOT).d;
	reflect_dir = vec_operation(vec_scalar(hit->normal,
				2.0 * dot_nl, MULT), light_dir, SUB);
	view_dir = vec_operation(ray->origin, hit->point, SUB);
	view_dir = vec_normalize(view_dir);
	specular_factor = pow(fmax(vec_dot_cross(view_dir,
					reflect_dir, DOT).d, 0.0), 32);
	specular_intensity = data->light->ratio * specular_factor;
	return (specular_intensity);
}

void	calc_diffusion(t_data *data, double dot_nl,
		t_color *final_color, t_hit *hit)
{
	double	diffuse_intensity;

	if (dot_nl > 0)
	{
		diffuse_intensity = data->light->ratio * dot_nl;
		final_color->r += hit->color.r * diffuse_intensity;
		final_color->g += hit->color.g * diffuse_intensity;
		final_color->b += hit->color.b * diffuse_intensity;
	}
}

t_color	compute_lighting(t_data *data, t_hit *hit, t_ray *ray)
{
	t_color	final_color;
	double	specular_intensity;
	t_pos	light_dir;
	double	dot_nl;

	specular_intensity = 0.0;
	hit->reflectivity = 100;
	apply_ambient(&final_color, hit, data->ambient->ratio);
	light_dir = vec_operation(data->light->pos, hit->point, SUB);
	light_dir = vec_normalize(light_dir);
	if (trace_shadows(data, hit->point))
		return (final_color);
	dot_nl = vec_dot_cross(hit->normal, light_dir, DOT).d;
	calc_diffusion(data, dot_nl, &final_color, hit);
	if (hit->reflectivity > 0)
	{
		specular_intensity = calc_specular(hit, light_dir, ray, data);
		final_color.r += 255 * specular_intensity;
		final_color.g += 255 * specular_intensity;
		final_color.b += 255 * specular_intensity;
	}
	final_color.r = fmin(final_color.r, 255);
	final_color.g = fmin(final_color.g, 255);
	final_color.b = fmin(final_color.b, 255);
	return (final_color);
}
