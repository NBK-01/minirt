/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:31:15 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/02/22 00:17:12 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/main.h"
#include "../../headers/minirt.h"

static bool	valid_ext(char *str)
{
	size_t	len;
	bool	ret;

	len = ft_strlen(str);
	if (len < 4)
		ret = false;
	ret = (str[len - 3] == '.' && ft_strncmp(str + len - 3, ".rt", 3) == 0);
	return (ret);
}

bool	valid_args(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		return (ft_putstr_fd(RED "Error: usage: <./minirt> <filename>\n" RESET,
				2), false);
	if (!valid_ext(av[1]))
		return (exit_err("Error: invalid file extension: must be .rt\n", NULL));
	fd = ft_open(av[1]);
	if (!fd)
		return (close(fd), false);
	close(fd);
	return (true);
}

double	parse_number(const char **str)
{
	double	result;
	double	fraction;
	int		seen_dot;

	result = 0.0;
	seen_dot = 0;
	fraction = 1.0;
	while (ft_isdigit(**str) || **str == '.')
	{
		if (**str == '.')
		{
			if (seen_dot)
				break ;
			seen_dot = 1;
		}
		else
		{
			if (seen_dot)
				fraction /= 10.0;
			result = result * 10.0 + (**str - '0');
		}
		(*str)++;
	}
	return (result * fraction);
}

double	ft_strtod(const char *str, char **endptr)
{
	double	result;
	int		sign;

	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = parse_number(&str);
	if (endptr)
		*endptr = (char *)str;
	return (sign * result);
}

bool	is_valid_double(const char *str)
{
	char	*endptr;

	ft_strtod(str, &endptr);
	return (*endptr == '\0');
}
