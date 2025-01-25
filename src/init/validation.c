/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:31:15 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/01/24 12:31:32 by mmuhaise         ###   ########.fr       */
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
		return (ft_putstr_fd(RED "Error: usage: <./minirt> <filename>\n" RESET, 2), false);
	if (!valid_ext(av[1]))
		return (ft_putstr_fd(RED "Error: invalid file extension: must be .rt\n" RESET, 2), false);
	fd = ft_open(av[1]);
	if (!fd)
		return (close(fd), false);
	close(fd);
	return (true);
}
