/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:43:22 by nkanaan           #+#    #+#             */
/*   Updated: 2025/02/21 15:43:23 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/main.h"
#include "../../../headers/minirt.h"

#define AA_SAMPLES	16

/*void print_progress(int current, int total)*/
/*{*/
/*	int bar_width = 50;*/
/*	float progress = (float)current / total;*/
/*	int pos = (int)(bar_width * progress);*/
/**/
/*	printf("\r[");*/
/*	for (int i = 0; i < bar_width; i++)*/
/*	{*/
/*		if (i < pos)*/
/*			printf("=");*/
/*		else if (i == pos)*/
/*			printf(">");*/
/*		else*/
/*			printf(" ");*/
/*	}*/
/*	printf("] %d%%", (int)(progress * 100));*/
/*	fflush(stdout);*/
/*}*/
/**/
t_color	compute_aa_pixel(t_data *data, double x, double y)
{
	t_color	final_color;
	t_color	sample_color;
	t_ray	ray;
	t_hit	hit;
	int		i;

	final_color = (t_color){0, 0, 0};
	i = -1;
	while (++i < AA_SAMPLES)
	{
		ray = generate_ray(data->camera, x + (rand() / (double)RAND_MAX - 0.5),
				y + (rand() / (double)RAND_MAX - 0.5));
		if (!find_closest_intersection(ray, data, &hit))
			sample_color = ((t_color){20, 20, 20});
		else
			sample_color = compute_lighting(data, &hit, &ray);
		color_add(&final_color, sample_color);
	}
	color_scalar_div(&final_color, AA_SAMPLES);
	return (final_color);
}

int	render_scene(t_data *data)
{
	int		x;
	int		y;
	t_color	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = compute_aa_pixel(data, x, y);
			rt_pixel_put(data->mlx, x, y, color_to_int(color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx->mlx,
		data->mlx->window, data->mlx->img, 0, 0);
	return (1);
}
