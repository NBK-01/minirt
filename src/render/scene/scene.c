#include "../../../headers/main.h"
#include "../../../headers/minirt.h"
#include <stdio.h>

#define AA_SAMPLES 9 // Change to 9 or 16 for higher quality

void print_progress(int current, int total)
{
    int bar_width = 50; // Adjust bar width as needed
    float progress = (float)current / total;
    int pos = (int)(bar_width * progress);

    printf("\r["); // Start bar
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

    fflush(stdout); // Force update
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

/*void render_scene(t_data *data)*/
/*{*/
/*    int x, y;*/
/*    int total_pixels = WIDTH * HEIGHT;*/
/*    int pixel_idx = 0;*/
/*	t_hit	hit;*/
/*	t_ray	ray;*/
/*	t_color	color;*/
/**/
/*    for (y = 0; y < HEIGHT; y++)*/
/*    {*/
/*        for (x = 0; x < WIDTH; x++, pixel_idx++)*/
/*		{*/
/*			t_color color = compute_aa_pixel(data, x, y, pixel_idx, total_pixels);*/
/*			if (find_closest_intersection(ray, data, &hit))*/
/*				color = compute_lighting(data, &hit, &ray);*/
/*			else*/
/*				color = (t_color){20, 20, 20};*/
/*			rt_pixel_put(data->mlx, x, y, color_to_int(color));*/
/*		}*/
/*    }*/
/**/
/*    printf("\nRendering complete!\n"); // Move to new line after bar finishes*/
/*}*/
void render_scene(t_data *data)
{
    int x, y;
    t_ray ray;
    t_hit hit;
    t_color color;

    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            ray = generate_ray(data->camera, x, y);
            if (!find_closest_intersection(ray, data, &hit))
                color = (t_color){20, 20, 20}; // Background color
            else
                color = compute_lighting(data, &hit, &ray);

            rt_pixel_put(data->mlx, x, y, color_to_int(color));
        }
    }
}
