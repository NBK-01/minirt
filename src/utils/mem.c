#include "../../headers/minirt.h"
#include "../../headers/main.h"

void	free_objs(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->spheres_count)
		free(data->objects->spheres[i]);
	i = -1;
	while (++i < data->planes_count)
		free(data->objects->planes[i]);
	i = -1;
	while (++i < data->cylinders_count)
		free(data->objects->cylinders[i]);
	if (data->objects->spheres)
		free(data->objects->spheres);
	if (data->objects->cylinders)
		free(data->objects->cylinders);
	if (data->objects->planes)
		free(data->objects->planes);
	free(data->objects);
}

void	free_scene(t_data *data)
{
	free(data->ambient);
	free(data->light);
	free(data->camera);
}
