
#include "../../../headers/minirt.h"
#include "../../../headers/main.h"
#include "../../../headers/math.h"

double compute_lighting(t_hit hit, t_light light, t_data *data)
{
    double intensity = data->ambient->ratio;
    t_pos light_dir = vec_normalize(vec_operation(light.pos, hit.point, SUB));
    double diffuse = fmax(0, vec_dot_cross(hit.normal, light_dir, DOT).d);

    t_ray shadow_ray = { vec_operation(hit.point, vec_scalar(hit.normal, EPSILON, ADD), ADD), light_dir };
    t_hit shadow_hit;
    if (find_closest_intersection(shadow_ray, data, &shadow_hit) && shadow_hit.t > EPSILON)
        return fmax(data->ambient->ratio, intensity * 0.5);

    intensity += diffuse * light.ratio;
    return fmin(1.0, intensity);
}
