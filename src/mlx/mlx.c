#include "../../headers/main.h"

void	rt_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size_line + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int	close_window(int keycode, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
    if (keycode == 53)
    {
        mlx_destroy_window(param, mlx->window);
        exit(0);
    }
    return (0);
}
