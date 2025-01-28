/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:08:54 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/01/24 14:58:53 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/main.h"
#include "../../headers/minirt.h"

double	ft_atof(const char *str)
{
	double	result;
	double	fraction;
	int		sign;
	int		divisor;

	result = 0.0;
	fraction = 0.0;
	sign = 1;
	divisor = 1;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		fraction = fraction * 10.0 + (*str - '0');
		divisor *= 10;
		str++;
	}
	return (sign * (result + fraction / divisor));
}

void	print_ambient(t_ambient *ambient)
{
	if (ambient == NULL)
	{
		printf("Ambient lighting is not set.\n");
		return ;
	}
	printf("Ambient Lighting:\n");
	printf("  Identifier: %c\n", ambient->ident);
	printf("  Ratio: %f\n", ambient->ratio);
	printf("  Color: R=%d, G=%d, B=%d\n", ambient->color.r, ambient->color.g, ambient->color.b);
}

void	print_camera(t_camera *camera)
{
	if (camera == NULL)
	{
		printf("Camera is not set.\n");
		return ;
	}
	printf("Camera:\n");
	printf("  Identifier: %c\n", camera->ident);
	printf("  Position: x=%f, y=%f, z=%f\n", camera->pos.x, camera->pos.y, camera->pos.z);
	printf("  Orientation: x=%f, y=%f, z=%f\n", camera->vec.x, camera->vec.y, camera->vec.z);
	printf("  Field of View: %d\n", camera->fov);
}

void	print_light(t_light *light)
{
	if (light == NULL)
	{
		printf("Light is not set.\n");
		return ;
	}
	printf("Light:\n");
	printf("  Identifier: %c\n", light->ident);
	printf("  Position: x=%f, y=%f, z=%f\n", light->pos.x, light->pos.y, light->pos.z);
	printf("  Ratio: %f\n", light->ratio);
	printf("  Color: R=%d, G=%d, B=%d\n", light->color.r, light->color.g, light->color.b);
}

void	print_plane(t_plane *plane)
{
	if (plane == NULL)
	{
		printf("Plane is not set.\n");
		return ;
	}
	printf("Plane:\n");
	printf("  Identifier: %s\n", plane->ident);
	printf("  Position: x=%f, y=%f, z=%f\n", plane->pos.x, plane->pos.y, plane->pos.z);
	printf("  Vector: x=%f, y=%f, z=%f\n", plane->vec.x, plane->vec.y, plane->vec.z);
	printf("  Color: R=%d, G=%d, B=%d\n", plane->color.r, plane->color.g, plane->color.b);
}

void	print_sphere(t_sphere *sphere)
{
	if (sphere == NULL)
	{
		printf("Sphere is not set.\n");
		return ;
	}
	printf("Sphere:\n");
	printf("  Identifier: %s\n", sphere->ident);
	printf("  Position: x=%f, y=%f, z=%f\n", sphere->pos.x, sphere->pos.y, sphere->pos.z);
	printf("  Diameter: %f\n", sphere->diameter);
	printf("  Color: R=%d, G=%d, B=%d\n", sphere->color.r, sphere->color.g, sphere->color.b);
}

void	print_cylinder(t_cylinder *cylinder)
{
	if (cylinder == NULL)
	{
		printf("Cylinder is not set.\n");
		return ;
	}
	printf("Cylinder:\n");
	printf("  Identifier: %s\n", cylinder->ident);
	printf("  Position: x=%f, y=%f, z=%f\n", cylinder->pos.x, cylinder->pos.y, cylinder->pos.z);
	printf("  Orientation: x=%f, y=%f, z=%f\n", cylinder->vec.x, cylinder->vec.y, cylinder->vec.z);
	printf("  Diameter: %f\n", cylinder->diameter);
	printf("  Height: %f\n", cylinder->height);
	printf("  Color: R=%d, G=%d, B=%d\n", cylinder->color.r, cylinder->color.g, cylinder->color.b);
}

void	print_data(t_data *data)
{
	print_ambient(data->ambient);
	print_camera(data->camera);
	print_light(data->light);
	/*print_plane(data->plane);*/
	print_sphere(data->objs->type.sp);
	print_sphere(data->objs->next->type.sp);
	/*print_cylinder(data->cylinder);*/
}
