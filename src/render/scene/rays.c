
#include "../../../headers/minirt.h"
#include "../../../headers/math.h"
#include "../../../headers/main.h"

t_ray generate_ray(t_camera *camera, int x, int y, int width, int height) {
    t_ray ray;
    float aspect_ratio = (float)width / (float)height;
    float fov_scale = tan((camera->fov * M_PI / 180.0) / 2.0);

    float px = (2.0 * ((x + 0.5) / width) - 1.0) * aspect_ratio * fov_scale;
    float py = (1.0 - 2.0 * ((y + 0.5) / height)) * fov_scale;

    ray.origin = camera->pos;
    ray.dir = vec_normalize((t_pos){px, py, -1.0});

    return ray;
}

bool intersect_sphere(t_ray ray, t_sphere sphere, double *t) {
    t_pos oc = vec_operation(ray.origin, sphere.pos, SUB);
    double a = vec_dot_cross(ray.dir, ray.dir, DOT).d;
    double b = 2.0 * vec_dot_cross(oc, ray.dir, DOT).d;
    double c = vec_dot_cross(oc, oc, DOT).d - (sphere.diameter / 2.0) * (sphere.diameter / 2.0);
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;

    double t0 = (-b - sqrt(discriminant)) / (2.0 * a);
    double t1 = (-b + sqrt(discriminant)) / (2.0 * a);

    *t = (t0 < t1) ? t0 : t1;
    return true;
}

bool intersect_plane(t_ray ray, t_plane plane, double *t) {
    double denom = vec_dot_cross(plane.vec, ray.dir, DOT).d;
    if (fabs(denom) > 1e-6) {
        t_pos p0 = vec_operation(plane.pos, ray.origin, SUB);
        *t = vec_dot_cross(p0, plane.vec, DOT).d / denom;
        return (*t >= 0);
    }
    return false;
}

bool intersect_cylinder(t_ray ray, t_cylinder cylinder, double *t) {
    t_pos oc = vec_operation(ray.origin, cylinder.pos, SUB);
    double a = vec_dot_cross(ray.dir, ray.dir, DOT).d - pow(vec_dot_cross(ray.dir, cylinder.vec, DOT).d, 2);
    double b = 2.0 * (vec_dot_cross(ray.dir, oc, DOT).d - vec_dot_cross(ray.dir, cylinder.vec, DOT).d * vec_dot_cross(oc, cylinder.vec, DOT).d);
    double c = vec_dot_cross(oc, oc, DOT).d - pow(vec_dot_cross(oc, cylinder.vec, DOT).d, 2) - pow(cylinder.diameter / 2.0, 2);
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;

    double t0 = (-b - sqrt(discriminant)) / (2.0 * a);
    double t1 = (-b + sqrt(discriminant)) / (2.0 * a);

    *t = (t0 < t1) ? t0 : t1;
    return true;
}

t_color apply_ambient(t_color color, t_ambient ambient) {
    t_color result;
    result.r = color.r * ambient.ratio;
    result.g = color.g * ambient.ratio;
    result.b = color.b * ambient.ratio;
    return result;
}

t_color apply_diffuse(t_color color, t_light light, t_pos normal, t_pos light_dir) {
    double diff = fmax(vec_dot_cross(normal, light_dir, DOT).d, 0.0);
    t_color result;
    result.r = color.r * diff * light.ratio;
    result.g = color.g * diff * light.ratio;
    result.b = color.b * diff * light.ratio;
    return result;
}

bool is_shadow(t_pos point, t_light light, t_data *data) {
    t_ray shadow_ray;
    shadow_ray.origin = point;
    shadow_ray.dir = vec_normalize(vec_operation(light.pos, point, SUB));

    double t;
        if (intersect_sphere(shadow_ray, *data->sphere, &t) && t > 0.001)
            return true;
        /*if (intersect_plane(shadow_ray, *data->plane, &t) && t > 0.001)*/
            /*return true;*/
        /*if (intersect_cylinder(shadow_ray, *data->cylinder, &t) && t > 0.001)*/
            /*return true;*/
    return false;
}

void render_scene(t_data *data) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            t_ray ray = generate_ray(data->camera, x, y, WIDTH, HEIGHT);
            t_color color = {0, 0, 0};
            double t_min = INFINITY;
            t_inter closest_inter = {0};

            // Check for intersections with all objects
                double t;
                if (intersect_sphere(ray, *data->sphere, &t) && t < t_min) {
                    t_min = t;
                    closest_inter.type = SP;
                    closest_inter.sp = *data->sphere;
                    closest_inter.dist = t;
                    closest_inter.point = vec_operation(ray.origin, vec_scalar(ray.dir, t, MULT), ADD);
                    closest_inter.normal = vec_normalize(vec_operation(closest_inter.point, data->sphere->pos, SUB));
                    closest_inter.c = data->sphere->color;
            }
            // Repeat for planes and cylinders...

            if (t_min < INFINITY) {
                color = apply_ambient(closest_inter.c, *data->ambient);
                if (!is_shadow(closest_inter.point, *data->light, data)) {
                    t_pos light_dir = vec_normalize(vec_operation(data->light->pos, closest_inter.point, SUB));
                    color = apply_diffuse(color, *data->light, closest_inter.normal, light_dir);
                }
            }

            // Set pixel color in the image buffer
            data->mlx->data[y * WIDTH + x] = (color.r << 16) | (color.g << 8) | color.b;
        }
    }
}
