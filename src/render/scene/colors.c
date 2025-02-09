#include "../../../headers/main.h"
#include "../../../headers/minirt.h"

t_color	set_color(t_hit hit, t_data *data)
{
	t_color	color;

	color.r = fmin(255, (hit.color.r * compute_lighting(hit, *data->light, data)));
    color.g = fmin(255, (hit.color.g * compute_lighting(hit, *data->light, data)));
	color.b = fmin(255, (hit.color.b * compute_lighting(hit, *data->light, data)));
	return (color);
}
