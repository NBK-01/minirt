/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:34:10 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/29 13:56:18 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	j;
	size_t	k;

	j = 0;
	if (!*needle || (NULL == haystack && !len))
		return ((char *)haystack);
	while (*(haystack + j) && j < len)
	{
		k = 0;
		while (*(haystack + j + k) == *(needle + k) && (k + j) < len)
		{
			if (0 == *(needle + k + 1))
				return ((char *)haystack + j);
			++k;
		}
		++j;
	}
	return (NULL);
}
