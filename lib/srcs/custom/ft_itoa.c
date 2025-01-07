/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbk <nbk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:28:37 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/03 15:01:14 by nbk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static size_t	get_len(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		++i;
	while (n)
	{
		n /= 10;
		++i;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	len;

	len = get_len(n);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (n == 0)
		res[0] = '0';
	else if (n < 0)
		res[0] = '-';
	while (n)
	{
		if (n < 0)
			res[--len] = (~(n % 10) + 1) + '0';
		else
			res[--len] = (n % 10) + '0';
		n = n / 10;
	}
	return (res);
}
