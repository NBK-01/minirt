#include "../../../headers/main.h"
#include "../../../headers/minirt.h"

#define AA_SAMPLES	9
/*#define	MULTI_THREAD 0*/

/*PRINT PROGRESS UTIL FUNC (TEMPO)*/
void print_progress(int current, int total)
{
    int bar_width = 50;
    float progress = (float)current / total;
    int pos = (int)(bar_width * progress);

    printf("\r[");
    for (int i = 0; i < bar_width; i++)
    {
        if (i < pos)
            printf("=");
        else if (i == pos)
            printf(">");
        else
            printf(" ");
    }
    printf("] %d%%", (int)(progress * 100));
    fflush(stdout);
}


t_color compute_aa_pixel(t_data *data, double x, double y, int pixel_idx, int total_pixels)
{
    t_color	final_color = {0,0,0};
    t_color	sample_color;
    t_ray	ray;
	t_hit	hit;
	int		i;

	i = -1;
	while (++i < AA_SAMPLES)
	{
		double x_offset = (rand() / (double)RAND_MAX - 0.5);
		double y_offset = (rand() / (double)RAND_MAX - 0.5);
		ray = generate_ray(data->camera, x + x_offset, y + y_offset);
		if (!find_closest_intersection(ray, data, &hit))
			sample_color = ((t_color){20, 20, 20});
		else
			sample_color = compute_lighting(data, &hit, &ray);
		color_add(&final_color, sample_color);
	}
	color_scalar_div(&final_color, AA_SAMPLES);
	if (pixel_idx % 100 == 0)
        print_progress(pixel_idx, total_pixels);
    return (clamp_color(final_color));
}

/*int	render_scene(t_data *data)*/
/*{*/
/*	int		pixel_idx = 0;*/
/*	int		total = WIDTH * HEIGHT;*/
/*	int		x;*/
/*	int		y;*/
/**/
/*	for (y = 0; y < HEIGHT; y++)*/
/*	{*/
/*		for (x = 0; x < WIDTH; x++)*/
/*		{*/
/*			t_color color = compute_aa_pixel(data, x, y, pixel_idx, total);*/
/*			rt_pixel_put(data->mlx, x, y, color_to_int(color));*/
/*		}*/
/*	}*/
/**/
/*	return (1);*/
/*}*/

int render_scene(t_data *data)
{
    t_ray ray;
    t_hit hit;
    t_color color;
	int		y;
	int		x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = generate_ray(data->camera, x, y);
			if (!find_closest_intersection(ray, data, &hit))
				color = (t_color){0,0,0};
			else
				color = compute_lighting(data, &hit, &ray);
			rt_pixel_put(data->mlx, x, y, color_to_int(color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->window, data->mlx->img, 0, 0);
	return (0);
}
