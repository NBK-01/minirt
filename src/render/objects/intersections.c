#include "../../../headers/main.h"
#include "../../../headers/math.h"
#include <stdbool.h>

static int	sphere(t_ray ray, t_sphere sphere, double *t);

bool	intersection(t_ray ray, t_data *data, double *t, t_ident id)
{
	if (id == SP)
		return (sphere(ray, (*data->sphere), t));
	else if (id == PL)
		return (0); //later later
	else if (id == CY)
		return (0);
	else
		return (ft_putstr_fd("object does not exist", 2), 0);
}

static int	sphere(t_ray ray, t_sphere sphere, double *t)
{
	t_pos	oc;
	double	a;
	double	b;
	double	c;
	double	disc;

	oc = vec_operation(ray.origin, sphere.pos, SUB);
    a = vec_dot_cross(ray.dir, ray.dir, DOT).d;
    b = 2.0 * vec_dot_cross(oc, ray.dir, DOT).d;
    c = vec_dot_cross(oc, oc, DOT).d - (sphere.diameter * sphere.diameter / 4);
    disc = b * b - 4.0 * a * c;

    if (disc > 0)
	{
		if (((-b - sqrt(disc) / (2.0 * a))) > 0)
            *t = (-b - sqrt(disc)) / (2.0 * a);
		else if ((-b + sqrt(disc) / (2.0 * a)) > 0)
            *t = (-b + sqrt(disc)) / (2.0 * a);
		else
			return (0);
        return (1);
    }
    return (0);
}

static int	plane(t_ray ray, t_sphere sphere, double *t)
{

}

