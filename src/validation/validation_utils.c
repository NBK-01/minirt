/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:31:15 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/02/14 22:16:12 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/main.h"

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
		return (ft_putstr_fd(RED "Error: invalid file extension: must be .rt\n" RESET,
				2), false);
	fd = ft_open(av[1]);
	if (!fd)
		return (close(fd), false);
	close(fd);
	return (true);
}

double	ft_strtod(const char *str, char **endptr)
{
	double	result;
	double	fraction;
	int		sign;
	int		seen_dot;

	result = 0.0;
	fraction = 1.0;
	sign = 1;
	seen_dot = 0;
	if (str == NULL)
	{
		if (endptr)
			*endptr = (char *)str;
		return (0.0);
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
				break ;
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
	return (sign * result * fraction);
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	long	result;
	int		sign;
	int		digit;

	result = 0;
	sign = 1;
	if (str == NULL)
	{
		if (endptr)
			*endptr = (char *)str;
		return (0);
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		digit = *str - '0';
		if (digit >= base)
			break ;
		result = result * base + digit;
		str++;
	}
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

bool	is_valid_int(const char *str)
{
	char	*endptr;

	ft_strtol(str, &endptr, 10);
	return (*endptr == '\0');
}
