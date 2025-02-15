
#include "../../../headers/minirt.h"
#include "../../../headers/main.h"
#include "../../../headers/math.h"

double vec_length(t_pos v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

double compute_lighting(t_hit hit, t_light light, t_data *data)
{
    double intensity = data->ambient->ratio;

    // Compute the direction from the intersection point to the light
    t_pos light_dir = vec_normalize(vec_operation(light.pos, hit.point, SUB));

    // Calculate diffuse lighting (basic Lambertian reflection)
    double diffuse = fmax(0, vec_dot_cross(hit.normal, light_dir, DOT).d);

    // Create a shadow ray from the intersection point to the light source
    t_ray shadow_ray = {
        vec_operation(hit.point, vec_scalar(hit.normal, EPSILON, ADD), ADD),  // Slightly offset to avoid self-intersection
        light_dir
    };

    t_hit shadow_hit;
    if (find_closest_intersection(shadow_ray, data, &shadow_hit))
    {
        // Check if the intersection is between the hit point and the light source (in shadow)
        double light_distance = vec_length(vec_operation(light.pos, hit.point, SUB));
        if (shadow_hit.t < light_distance && shadow_hit.t > EPSILON) // The hit is between the point and the light
        {
            return intensity * 0.3; // Reduce light intensity for shadows (darken the point)
        }
    }

    // If no objects were hit, apply the diffuse lighting and ambient light
    intensity += diffuse * light.ratio;

    // Ensure intensity is clamped between 0 and 1
    return fmin(1.0, intensity);
}
