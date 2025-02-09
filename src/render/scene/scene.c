#include "../../../headers/main.h"
#include "../../../headers/math.h"
#include "../../../headers/minirt.h"

void render_scene(t_data *data)
{
	int	x;
	int	y;
	t_ray	ray;
	t_color	color;
    t_hit closest_hit;

	y = -1;
    while (++y < HEIGHT)
    {
		x = -1;
        while (++x < WIDTH)
        {
			ray = generate_ray(data->camera, x, y);
            if (find_closest_intersection(ray, data, &closest_hit))
            {
				color = set_color(closest_hit, data);
                data->mlx->data[y * WIDTH + x] = (color.r << 16) | (color.g << 8) | color.b;
            }
            else
                data->mlx->data[y * WIDTH + x] = 0x000000;
        }
    }
    mlx_put_image_to_window(data->mlx->mlx, data->mlx->window, data->mlx->img, 0, 0);
}

