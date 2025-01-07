/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:33:02 by nkanaan           #+#    #+#             */
/*   Updated: 2024/06/13 15:28:24 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	char			*dest_ptr;
	const char		*src_ptr;

	src_ptr = (const char *)src;
	dest_ptr = (char *)dst;
	i = 0;
	while (i < n)
	{
		dest_ptr[i] = src_ptr[i];
		if (dest_ptr[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
// #include <stdio.h>
// int main() {
//     char str1[] = "coucou";
//     char str2[100];
// 	ft_memset(str2, 'A', 100);
//     char *ptr;
//     size_t n = 0;
//     ptr = ft_memccpy(str2, str1, 0, n);
// 	printf("%s\n", str2);
//     return 0;
// }
