/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:08:54 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/02/21 13:16:02 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/main.h"
#include "../../headers/minirt.h"

void	skip_ws(const char **str, int *sign)
{
	while (**str == ' ' || ((*(*str)) >= 9 && **str <= 13))
		(*str)++;
	if (**str == '-')
		(*sign) = -1;
	if (**str == '-' || **str == '+')
		(*str)++;
}

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
	skip_ws(&str, &sign);
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

static void	set_line(char *line, t_list **file)
{
	t_list	*new;

	new = ft_lstnew(line);
	ft_lstadd_back(file, new);
}

int	read_file(char *filename, t_list **file)
{
	int		fd;
	char	*line;

	fd = ft_open(filename);
	line = get_next_line(fd);
	if (!line)
		return (ft_putstr_fd(RED "Error: empty file :() \n" RESET, 2), 0);
	while (line)
	{
		set_line(line, file);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
