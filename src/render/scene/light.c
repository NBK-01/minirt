
#include "../../../headers/minirt.h"
#include "../../../headers/main.h"
#include "../../../headers/math.h"
#define SHADOW_BIAS 0.001
#define SHADOW_SAMPLES 10

t_pos	normalize(t_pos v)
{
	float	len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return ((t_pos){v.x / len, v.y / len, v.z / len});
}

bool	trace_shadows(t_data *data, t_pos hit_point)
{
    t_ray	shadow_ray;
    t_hit	shadow_hit;
    t_pos	light_dir;
    double	light_distance;

    if (!data->light)
        return (false);
    light_dir = vec_operation(data->light->pos, hit_point, SUB);
    light_distance = sqrt(light_dir.x * light_dir.x + light_dir.y * light_dir.y + light_dir.z * light_dir.z);
    light_dir = vec_normalize(light_dir);
    shadow_ray.origin = vec_operation(hit_point, vec_scalar(light_dir, EPSILON, MULT), ADD);
    shadow_ray.dir = light_dir;
    for (int i = 0; i < data->spheres_count; i++)
    {
        if (intersect_sphere(shadow_ray, *data->objects->spheres[i], &shadow_hit) && shadow_hit.t > 0 && shadow_hit.t < light_distance)
            return true;
    }
	for (int i = 0; i < data->planes_count; i++)
    {
        if (intersect_plane(shadow_ray, *data->objects->planes[i], &shadow_hit) && shadow_hit.t > 0 && shadow_hit.t < light_distance)
            return true;
    }
	for (int i = 0; i < data->cylinders_count; i++)
    {
        if (intersect_cylinder(shadow_ray, *data->objects->cylinders[i], &shadow_hit) && shadow_hit.t > 0 && shadow_hit.t < light_distance)
            return true;
    }
    return false;
}

double	calc_specular(t_hit *hit, t_pos light_dir, t_ray *ray,
					 double dot_nl, t_data	*data)
{
	t_pos	reflect_dir;
	t_pos	view_dir;
	double	specular_factor;
	double	specular_intensity;

	reflect_dir = vec_operation(vec_scalar(hit->normal, 2.0 * dot_nl, MULT), light_dir, SUB);
	view_dir = vec_operation(ray->origin, hit->point, SUB);
	view_dir = vec_normalize(view_dir);
	specular_factor = pow(fmax(vec_dot_cross(view_dir, reflect_dir, DOT).d, 0.0), 48);
	specular_intensity = data->light->ratio * specular_factor;
	return (specular_intensity);
}

t_color	compute_lighting(t_data *data, t_hit *hit, t_ray *ray)
{
    t_color	final_color;
    t_pos	light_dir;
    double	dot_nl;

    final_color.r = hit->color.r * data->ambient->ratio;
    final_color.g = hit->color.g * data->ambient->ratio;
    final_color.b = hit->color.b * data->ambient->ratio;

    if (!data->light)
        return (final_color);
    light_dir = vec_operation(data->light->pos, hit->point, SUB);
    light_dir = vec_normalize(light_dir);
    if (trace_shadows(data, hit->point))
        return (final_color);
    dot_nl = vec_dot_cross(hit->normal, light_dir, DOT).d;
    if (dot_nl > 0)
    {
        final_color.r += hit->color.r * data->light->ratio * dot_nl;
        final_color.g += hit->color.g * data->light->ratio * dot_nl;
        final_color.b += hit->color.b * data->light->ratio * dot_nl;
    }

    if (hit->reflectivity > 0)
    {
        final_color.r += 255 * calc_specular(hit, light_dir, ray, dot_nl, data);
        final_color.g += 255 * calc_specular(hit, light_dir, ray, dot_nl, data);
        final_color.b += 255 * calc_specular(hit, light_dir, ray, dot_nl, data);
    }
	final_color = clamp_color(final_color);
    return (final_color);
}

