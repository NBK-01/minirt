/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:36:25 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/29 13:56:18 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char			*ptr;
	unsigned char			chr;
	size_t					i;

	ptr = (unsigned char *)s;
	chr = (unsigned char)c;
	i = 0;
	while (n > i)
	{
		if (ptr[i] == chr)
			return (&ptr[i]);
		i++;
	}
	return (NULL);
}
// #include <stdio.h>
// int main () {
//    const char str[] = "Nayef Kanaan";
//    const char ch = 'K';
//    char *ret;

//    ret = ft_memchr(str, ch, ft_strlen(str));

//    printf("%s", ret);

//    return(0);
// }