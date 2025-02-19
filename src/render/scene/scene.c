#include "../../../headers/main.h"
#include "../../../headers/math.h"
#include "../../../headers/minirt.h"

#define AA_SAMPLES 9 // Change to 9 or 16 for higher quality

/*void render_scene(t_data *data)*/
/*{*/
/*	int	x;*/
/*	int	y;*/
/*	t_ray	ray;*/
/*	t_color	color;*/
/*    t_hit closest_hit;*/
/**/
/*	y = -1;*/
/*    while (++y < HEIGHT)*/
/*    {*/
/*		x = -1;*/
/*        while (++x < WIDTH)*/
/*        {*/
/**/
/*			ray = generate_ray(data->camera, x, y);*/
/*            if (find_closest_intersection(ray, data, &closest_hit))*/
/*				color = compute_lighting(data, &closest_hit, &ray);*/
/*            else*/
/*				color = (t_color){0, 0, 0};*/
/*			rt_pixel_put(data->mlx, x, y, (color.r << 16) | (color.g << 8) | color.b);*/
/*        }*/
/*    }*/
/*}*/


static t_color clamp_color(t_color color) {
    if (color.r > 255) color.r = 255;
    if (color.g > 255) color.g = 255;
    if (color.b > 255) color.b = 255;
    return color;
}

int color_to_int(t_color color) {
    return (color.r << 16) | (color.g << 8) | color.b;
}

// 🎯 Apply gamma correction (sRGB color space)
t_color apply_gamma_correction(t_color color) {
    color.r = pow(color.r / 255.0, 1 / 2.2) * 255;
    color.g = pow(color.g / 255.0, 1 / 2.2) * 255;
    color.b = pow(color.b / 255.0, 1 / 2.2) * 255;
    return clamp_color(color);
}

t_color compute_aa_pixel(t_data *data, double x, double y) {
    t_color final_color = {0, 0, 0};
    t_color sample_color = {30,30,30};
    t_ray ray;
	t_hit hit;

    for (int i = 0; i < AA_SAMPLES; i++) {
        double offset_x = ((double)rand() / RAND_MAX - 0.5) * 2.0;
        double offset_y = ((double)rand() / RAND_MAX - 0.5) * 2.0;

        ray = generate_ray(data->camera, x + offset_x, y + offset_y);
        if (find_closest_intersection(ray, data, &hit))
			sample_color = compute_lighting(data, &hit, &ray);

        // Accumulate color
        final_color.r += sample_color.r;
        final_color.g += sample_color.g;
        final_color.b += sample_color.b;
    }

    // Average the colors
    final_color.r /= AA_SAMPLES;
    final_color.g /= AA_SAMPLES;
    final_color.b /= AA_SAMPLES;

    // Apply gamma correction

    return (clamp_color(final_color));
}


void render_scene(t_data *data)
{
    int x, y;

    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
		{
			t_color color = compute_aa_pixel(data, x, y);
			rt_pixel_put(data->mlx, x, y, color_to_int(color));
		}
    }
}
