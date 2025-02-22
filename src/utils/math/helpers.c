/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:12:50 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/02/21 13:12:50 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/math.h"
#include "../../../headers/main.h"

double	quadratic(double a, double b, double c)
{
	double	discriminant;
	double	t1;
	double	t2;

	discriminant = b * b - 4.0 * a * c;
	if (discriminant > 0)
	{
		t1 = (-b - sqrt(discriminant)) / (2.0 * a);
		t2 = (-b + sqrt(discriminant)) / (2.0 * a);
		if (t1 > EPSILON)
			return (t1);
		else if (t2 > EPSILON)
			return (t2);
		else
			return (0);
	}
	return (0);
}

t_pos	normalize(t_pos v)
{
	float	len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return ((t_pos){v.x / len, v.y / len, v.z / len});
}
