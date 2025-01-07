/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:44:02 by nkanaan           #+#    #+#             */
/*   Updated: 2024/06/11 09:44:04 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_string.h"

void	*ft_memset(void *dst, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)dst;
	while (n > 0)
	{
		str[n - 1] = c;
		n--;
	}
	return (dst);
}
