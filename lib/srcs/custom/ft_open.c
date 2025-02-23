/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:43:11 by nkanaan           #+#    #+#             */
/*   Updated: 2025/02/23 19:43:12 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdio.h>

int	ft_open(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd(RED "Error: failed to open file\n" RESET, 2), 0);
	if (read(fd, NULL, 0) < 0)
		return (ft_putstr_fd(RED "Error: failed to read file\n" RESET, 2), 0);
	return (fd);
}
