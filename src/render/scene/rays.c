
#include "../../../headers/math.h"
#include "../../../headers/main.h"
#include "../../../headers/minirt.h"


t_pos calculate_ray_direction(int x, int y, t_camera *camera, double aspect_ratio)
{
    double px = (2 * ((x + 0.5) / (double)WIDTH) - 1) * tan(camera->fov * 0.5 * M_PI / 180) * aspect_ratio;
    double py = (1 - 2 * ((y + 0.5) / (double)HEIGHT)) * tan(camera->fov * 0.5 * M_PI / 180);

    t_pos forward = vec_normalize(camera->vec);
    t_pos right = vec_normalize(vec_dot_cross((t_pos){0, 1, 0}, forward, CROSS).v);
    t_pos up = vec_dot_cross(forward, right, CROSS).v;

    t_pos ray_dir = vec_operation(
        vec_operation(vec_scalar(right, px, MULT), vec_scalar(up, py, MULT), ADD),
        forward, ADD
    );
    return vec_normalize(ray_dir);
}

t_ray	generate_ray(t_camera *cam, int x, int y)
{
	t_ray	ray;
	double	aspect_ratio;

	aspect_ratio = (double)WIDTH / HEIGHT;
	ray.origin = cam->pos;
	ray.dir = calculate_ray_direction(x, y, cam, aspect_ratio);
	return (ray);
}


