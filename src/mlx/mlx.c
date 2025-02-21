#include "../../headers/main.h"
#include "../../headers/minirt.h"

void	rt_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size_line + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_mlx(t_data *data)
{
	data->mlx = malloc(sizeof(t_mlx));
	data->mlx->mlx = mlx_init();
	data->mlx->window = mlx_new_window(data->mlx->mlx, WIDTH, HEIGHT, "miniRT");
	data->mlx->img = mlx_new_image(data->mlx->mlx, WIDTH, HEIGHT);
	data->mlx->addr = mlx_get_data_addr(data->mlx->img, &data->mlx->bpp,
			&data->mlx->size_line, &data->mlx->endian);
	mlx_key_hook(data->mlx->window, close_window, data);
	render_scene(data);
	mlx_hook(data->mlx->window, DestroyNotify, StructureNotifyMask,
		&on_destroy, data);
	mlx_loop(data->mlx->mlx);
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
