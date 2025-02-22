/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:51:48 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/02/21 11:52:11 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/main.h"
#include "../../../headers/minirt.h"

t_color	clamp_color(t_color color)
{
	if (color.r > 255)
		color.r = 255;
	if (color.g > 255)
		color.g = 255;
	if (color.b > 255)
		color.b = 255;
	return (color);
}

int	color_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void	color_add(t_color *color, t_color other)
{
	color->r += other.r;
	color->g += other.g;
	color->b += other.b;
}

void	color_scalar_div(t_color *color, int scalar)
{
	color->r /= scalar;
	color->g /= scalar;
	color->b /= scalar;
}

void	apply_ambient(t_color *final_color, t_hit *hit, double ratio)
{
	final_color->r = hit->color.r * ratio;
	final_color->g = hit->color.g * ratio;
	final_color->b = hit->color.b * ratio;
}
