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

t_color	apply_gamma_correction(t_color color)
{
	color.r = pow(color.r / 255.0, 1 / 2.2) * 255;
	color.g = pow(color.g / 255.0, 1 / 2.2) * 255;
	color.b = pow(color.b / 255.0, 1 / 2.2) * 255;
	return (clamp_color(color));
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
