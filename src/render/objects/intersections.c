#include "../../../headers/main.h"
#include "../../../headers/math.h"
#include <stdbool.h>

static int	sphere(t_ray ray, t_sphere sphere, double *t);

bool	intersection(t_ray ray, t_data *data, double *t, t_ident id)
{
	if (id == SP)
		return (0);
		/*return (sphere(ray, (*data->sphere), t));*/
	else if (id == PL)
		return (0); //later later
	else if (id == CY)
		return (0); //later later
	else
		return (ft_putstr_fd("object does not exist", 2), 0);
}

static int	sphere(t_ray ray, t_sphere sphere, double *t)
{
	return (1);
}
