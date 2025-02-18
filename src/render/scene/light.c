
#include "../../../headers/minirt.h"
#include "../../../headers/main.h"
#include "../../../headers/math.h"

#define SHADOW_BIAS 0.001   // Prevent self-shadowing
#define SHADOW_SAMPLES 10   // Number of rays for soft shadows


// Utility function to normalize a vector
t_pos normalize(t_pos v) {
    float len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return (t_pos){v.x / len, v.y / len, v.z / len};
}


// Function to check if an object is in shadow
bool trace_shadows(t_data *data, t_pos hit_point)
{
    t_ray shadow_ray;
    t_hit shadow_hit;
    t_pos light_dir;
    double light_distance;

    if (!data->light)
        return false; // No light in the scene, no shadows

    // Compute direction from hit point to light source
    light_dir = vec_operation(data->light->pos, hit_point, SUB);
    light_distance = sqrt(light_dir.x * light_dir.x + light_dir.y * light_dir.y + light_dir.z * light_dir.z);
    light_dir = vec_normalize(light_dir);

    // Create a shadow ray
    shadow_ray.origin = vec_operation(hit_point, vec_scalar(light_dir, EPSILON, MULT), ADD);
    shadow_ray.dir = light_dir;

    // Check for intersections along the shadow ray
    for (int i = 0; i < data->spheres_count; i++)
    {
        if (intersect_sphere(shadow_ray, *data->objects->spheres[i], &shadow_hit) && shadow_hit.t > 0 && shadow_hit.t < light_distance)
            return true; // There is an object between the hit point and the light source
    }
	for (int i = 0; i < data->planes_count; i++)
    {
        if (intersect_plane(shadow_ray, *data->objects->planes[i], &shadow_hit) && shadow_hit.t > 0 && shadow_hit.t < light_distance)
            return true; // There is an object between the hit point and the light source
    }
	for (int i = 0; i < data->cylinders_count; i++)
    {
        if (intersect_cylinder(shadow_ray, *data->objects->cylinders[i], &shadow_hit) && shadow_hit.t > 0 && shadow_hit.t < light_distance)
            return true; // There is an object between the hit point and the light source
    }

    return false; // No object blocking the light
}

t_color compute_lighting(t_data *data, t_hit *hit, t_ray *ray)
{
    t_color final_color;
    double ambient_intensity = AMBIENT;
    double diffuse_intensity = 0.0;
    double specular_intensity = 0.0;
    t_pos light_dir;
    double dot_nl;

    // Start with ambient lighting
    final_color.r = hit->color.r * ambient_intensity;
    final_color.g = hit->color.g * ambient_intensity;
    final_color.b = hit->color.b * ambient_intensity;

    if (!data->light)
        return final_color; // No light in scene, only ambient lighting applies

    // Compute light direction
    light_dir = vec_operation(data->light->pos, hit->point, SUB);
    light_dir = vec_normalize(light_dir);

    // Check if in shadow
    if (trace_shadows(data, hit->point))
        return final_color; // If in shadow, return ambient only

    // Compute diffuse lighting
    dot_nl = vec_dot_cross(hit->normal, light_dir, DOT).d;
    if (dot_nl > 0)
    {
        diffuse_intensity = data->light->ratio * dot_nl;
        final_color.r += hit->color.r * diffuse_intensity;
        final_color.g += hit->color.g * diffuse_intensity;
        final_color.b += hit->color.b * diffuse_intensity;
    }

    // Compute specular lighting
    if (hit->reflectivity > 0)
    {
        t_pos reflect_dir, view_dir;
        double specular_factor;

        reflect_dir = vec_operation(vec_scalar(hit->normal, 2.0 * dot_nl, MULT), light_dir, SUB);
        view_dir = vec_operation(ray->origin, hit->point, SUB);
        view_dir = vec_normalize(view_dir);
        specular_factor = pow(fmax(vec_dot_cross(view_dir, reflect_dir, DOT).d, 0.0), 32); // Shininess = 32

        specular_intensity = data->light->ratio * specular_factor;
        final_color.r += 255 * specular_intensity;
        final_color.g += 255 * specular_intensity;
        final_color.b += 255 * specular_intensity;
    }

    // Clamp colors to max 255
    final_color.r = fmin(final_color.r, 255);
    final_color.g = fmin(final_color.g, 255);
    final_color.b = fmin(final_color.b, 255);

    return final_color;
}

