#include "../../headers/main.h"

void	rt_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size_line + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

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
		free(data->objects->spheres[i]);
	free(data->objects->spheres);
	free(data->objects->cylinders);
	free(data->objects->planes);
	free(data->objects);
}

void	free_scene(t_data *data)
{
	free(data->ambient);
	free(data->light);
	free(data->camera);
	
}

int	on_destroy(t_data *data)
{
	mlx_destroy_image(data->mlx->mlx, data->mlx->img);
	mlx_destroy_window(data->mlx->mlx, data->mlx->window);
	mlx_destroy_display(data->mlx->mlx);
	free_scene(data);
	free_objs(data);
	free(data->mlx->mlx);
	free(data->mlx);
	free(data);
	exit(0);
	return (0);
}

int	close_window(int keycode, t_data *data)
{
	if (keycode == 65307)
    {
		on_destroy(data);
		exit(0);
    }
    return (0);
}
