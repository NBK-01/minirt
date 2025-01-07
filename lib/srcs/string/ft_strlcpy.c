/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbk <nbk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:34:05 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/09 03:45:57 by nbk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	src_len;

	i = 0;
	j = 0;
	src_len = ft_strlen(src);
	if (!(dst) || !(src) || dstsize == 0)
		return (src_len);
	while (src[j] && dstsize - 1)
	{
		dst[i++] = src[j++];
		--dstsize;
	}
	dst[i] = '\0';
	return (src_len);
}
