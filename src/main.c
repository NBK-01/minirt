/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:48:34 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/02/10 13:25:48 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include "../headers/minirt.h"

double ft_strtod(const char *str, char **endptr)
{
	double result = 0.0;
	double fraction = 1.0;
	int sign = 1;
	int seen_dot = 0;

	if (str == NULL)
	{
		if (endptr)
			*endptr = (char *)str;
		return 0.0;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str) || *str == '.')
	{
		if (*str == '.')
		{
			if (seen_dot)
				break;
			seen_dot = 1;
		}
		else
		{
			if (seen_dot)
				fraction /= 10.0;
			result = result * 10.0 + (*str - '0');
		}
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return sign * result * fraction;
}

long ft_strtol(const char *str, char **endptr, int base)
{
	long result = 0;
	int sign = 1;

	if (str == NULL)
	{
		if (endptr)
			*endptr = (char *)str;
		return 0;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		int digit = *str - '0';
		if (digit >= base)
			break;
		result = result * base + digit;
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return sign * result;
}

bool	is_valid_double(const char *str)
{
	char *endptr;
	ft_strtod(str, &endptr);
	return (*endptr == '\0');
}

bool	is_valid_int(const char *str)
{
	char *endptr;
	ft_strtol(str, &endptr, 10);
	return (*endptr == '\0');
}

bool    check_rgb(char *split)
{
	char **color_split = ft_split(split, ",");
	if (!color_split || !color_split[0] || !color_split[1] || !color_split[2])
	{
		return (ft_putstr_fd(RED "Error: invalid rgb color\n" RESET, 2), false);
	}
	if (color_split[3])
	{   
		return (ft_putstr_fd(RED "Error: invalid rgb color\n" RESET, 2), false);
	}
	char *trimmed_color = ft_strtrim(color_split[2], "\n");
	free(color_split[2]);
	color_split[2] = trimmed_color;
	if (!is_valid_int(color_split[0]) || !is_valid_int(color_split[1]) || !is_valid_int(color_split[2]))
		return (ft_putstr_fd(RED "Error: invalid RGB values\n" RESET, 2), false);
	int r = ft_atoi(color_split[0]);
	int g = ft_atoi(color_split[1]);
	int b = ft_atoi(color_split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (ft_putstr_fd(RED "Error: invalid RGB values\n" RESET, 2), false);
	free(color_split[0]);
	free(color_split[1]);
	free(color_split[2]);
	free(color_split);
	return (true);
}

bool	check_vector(char *split)
{
	char **vec_split = ft_split(split, ",");
	if (!vec_split || !vec_split[0] || !vec_split[1] || !vec_split[2])
	{
		return (ft_putstr_fd(RED "Error: invalid orientation vector\n" RESET, 2), false);
	}
	if (vec_split[3])
	{
		return (ft_putstr_fd(RED "Error: invalid orientation vector\n" RESET, 2), false);
	}
	double v1 = ft_atof(vec_split[0]);
	double v2 = ft_atof(vec_split[1]);
	double v3 = ft_atof(vec_split[2]);
	if (!is_valid_double(vec_split[0]) || !is_valid_double(vec_split[1]) || !is_valid_double(vec_split[2])
		|| v1 < -1 || v1 > 1 || v2 < -1 || v2 > 1 || v3 < -1 || v3 > 1 )
		return (ft_putstr_fd(RED "Error: invalid orientation values\n" RESET, 2), false);
	free(vec_split[0]);
	free(vec_split[1]);
	free(vec_split[2]);
	free(vec_split);
	return (true);
}

bool	check_coordinates(char *split)
{
	char **coord_split = ft_split(split, ",");
	if (!coord_split || !coord_split[0] || !coord_split[1] || !coord_split[2])
	{
		return (ft_putstr_fd(RED "Error: invalid coordinates\n" RESET, 2), false);
	}
	if (coord_split[3])
	{
		return (ft_putstr_fd(RED "Error: invalid coordinates\n" RESET, 2), false);
	}
	if (!is_valid_double(coord_split[0]) || !is_valid_double(coord_split[1]) || !is_valid_double(coord_split[2]))
		return (ft_putstr_fd(RED "Error: invalid coordinates values\n" RESET, 2), false);
	free(coord_split[0]);
	free(coord_split[1]);
	free(coord_split[2]);
	free(coord_split);
	return (true);
}

int  check_config(char *str)
{
	const char *arr[] = {"A", "C", "L", "sp", "cy", "pl", "breakme"};
	int i = 0;

	if (!ft_strcmp(str, "\n"))
		return (1);
	while (i < 6)
	{
		if (!ft_strcmp(str, arr[i]))
			break ;
		i++;
	}
	if (i > 5)
		return 0;
	return 1;
}

bool	validate_ambient(char **split)
{
	if (split[1] && split[2] && !ft_strlen(ft_strtrim(split[3], "\n")))
	{
		if (!is_valid_double(split[1]))
			return (ft_putstr_fd(RED "Error: invalid ambient ratio\n" RESET, 2), false);
		double ratio = ft_atof(split[1]);
		if (ratio < 0.0 || ratio > 1.0)
			return (ft_putstr_fd(RED "Error: invalid ambient ratio\n" RESET, 2), false);
		if (!check_rgb(split[2]))
			return (false);
	}
	else
		return (ft_putstr_fd(RED "Error: invalid ambient config\n" RESET, 2), false);
	return (true);
}

bool	validate_camera(char **split)
{
	if (split[1] && split[2] && split[3] && !ft_strlen(ft_strtrim(split[4], "\n")))
	{
		if (!check_coordinates(split[1]))
			return (false);
		if (!check_vector(split[2]))
			return (false);
		char *trimmed_fov = ft_strtrim(split[3], "\n");
		int fov = ft_atoi(trimmed_fov);
		if (!is_valid_int(trimmed_fov) || fov < 0 || fov > 180)
			return (ft_putstr_fd(RED "Error: invalid camera FOV\n" RESET, 2), false);
		free(trimmed_fov);
	}
	else
		return (ft_putstr_fd(RED "Error: invalid camera config\n" RESET, 2), false);
	return (true);
}

bool	validate_light(char **split)
{
	if (split[1] && split[2] && !ft_strlen(ft_strtrim(split[3], "\n")))
	{
		if (!check_coordinates(split[1]))
			return (false);
		char *trimmed_brightness = ft_strtrim(split[2], "\n");
		double brightness = ft_atof(trimmed_brightness);
		if (!is_valid_double(trimmed_brightness) || brightness < 0 || brightness > 1)
			return (ft_putstr_fd(RED "Error: invalid light brightness\n" RESET, 2), false);
	}
	else
		return (ft_putstr_fd(RED "Error: invalid light config\n" RESET, 2), false);
	return (true);
}

bool	validate_sphere(char **split)
{
	if (split[1] && split[2] && split[3] && !ft_strlen(ft_strtrim(split[4], "\n")))
	{
		if (!check_coordinates(split[1]))
			return (false);
		double diameter = ft_atof(split[2]);
		if (!is_valid_double(split[2]) || diameter < 0)
			return (ft_putstr_fd(RED "Error: invalid sphere diameter\n" RESET, 2), false);
		if (!check_rgb(split[3]))
			return (false);
	}
	else
		return (ft_putstr_fd(RED "Error: invalid sphere config\n" RESET, 2), false);
	return (true);
}

bool	validate_plane(char **split)
{
	if (split[1] && split[2] && split[3] && !ft_strlen(ft_strtrim(split[4], "\n")))
	{
		if (!check_coordinates(split[1]))
			return (false);
		if (!check_vector(split[2]))
			return (false);
		if (!check_rgb(split[3]))
			return (false);
	}
	else
		return (ft_putstr_fd(RED "Error: invalid plane config\n" RESET, 2), false);
	return (true);
}

bool	validate_cylinder(char **split)
{
	if (split[1] && split[2] && split[3] && split[4] && split[5] && !ft_strlen(ft_strtrim(split[6], "\n")))
	{
		if (!check_coordinates(split[1]))
			return (false);
		if (!check_vector(split[2]))
			return (false);
		double diameter = ft_atof(split[3]);
		if (!is_valid_double(split[3]) || diameter < 0)
			return (ft_putstr_fd(RED "Error: invalid cylinder diameter\n" RESET, 2), false);
		double height = ft_atof(split[4]);
		if (!is_valid_double(split[4]) || height < 0)
			return (ft_putstr_fd(RED "Error: invalid cylinder height\n" RESET, 2), false);
		if (!check_rgb(split[5]))
			return (false);
	}
	else
		return (ft_putstr_fd(RED "Error: invalid plane config\n" RESET, 2), false);
	return (true);
}

bool	validate_file(t_list **file)
{
	t_list	*tmp;
	char	**split;
	bool	has_ambient = false;
	bool	has_camera = false;
	bool	has_light = false;

	tmp = (*file);
	while (tmp)
	{
		split = ft_split(tmp->content, " \t");
		if (!check_config(split[0]))
			return (ft_putstr_fd(RED "Error: unkown configs\n" RESET, 2), false);
		if (split[0] && (!ft_strcmp(split[0], "A") || !ft_strcmp(split[0], "C")
				|| !ft_strcmp(split[0], "L") || !ft_strcmp(split[0], "A\n")
				|| !ft_strcmp(split[0], "C\n") || !ft_strcmp(split[0], "L\n")))
		{
			if (!ft_strcmp(split[0], "A") || !ft_strcmp(split[0], "A\n"))
			{
				has_ambient = true;
				if (!validate_ambient(split))
					return (false);
			}
			if (!ft_strcmp(split[0], "C") || !ft_strcmp(split[0], "C\n"))
			{
				has_camera = true;
				if (!validate_camera(split))
					return false;
			}
			if (!ft_strcmp(split[0], "L") || !ft_strcmp(split[0], "L\n"))
			{
				has_light = true;
				if (!validate_light(split))
					return (false);
			}
		}
		if (split[0] && (!ft_strcmp(split[0], "sp") || !ft_strcmp(split[0], "sp\n")))
		{
			if (!validate_sphere(split))
				return (false);
		}
		if (split[0] && (!ft_strcmp(split[0], "pl") || !ft_strcmp(split[0], "pl\n")))
		{
			if (!validate_plane(split))
				return (false);
		}
		if (split[0] && (!ft_strcmp(split[0], "cy") || !ft_strcmp(split[0], "cy\n")))
		{
			if (!validate_cylinder(split))
				return (false);
		}
		free(split);
		tmp = tmp->next;
	}
	if (!has_ambient || !has_camera || !has_light)
		return (ft_putstr_fd(RED "Error: file must contain 'A', 'C', and 'L'\n" RESET, 2), false);
	return (true);
}

bool	initialize(char *filename)
{
	t_list	*file;
	t_data	*data;

	file = NULL;
	data = malloc(sizeof(t_data));
	(void)data;
	if (!read_file(filename, &file))
		return (false);
	if (!validate_file(&file))
		return (false);
	if (!parse_file(&file, data))
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	if (!valid_args(ac, av))
		exit(EXIT_FAILURE);
	if (!initialize(av[1]))
		exit(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
