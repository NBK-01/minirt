#include "../../../headers/main.h"
#include "../../../headers/minirt.h"

t_color	set_color(t_hit hit, t_data *data)
{
	t_color	color;
	double	light;

	light = compute_lighting(hit, *data->light,  data);
	color.r = fmin(255, (hit.color.r * light));
    color.g = fmin(255, (hit.color.g * light));
	color.b = fmin(255, (hit.color.b * light));
	return (color);
}
