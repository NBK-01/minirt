/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:11:07 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/29 13:56:20 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	char			*dest_ptr;
	const char		*src_ptr;

	dest_ptr = s1;
	src_ptr = s2;
	if (n)
	{
		while (n > 0)
		{
			*dest_ptr++ = *src_ptr++;
			n--;
		}
	}
	return (s1);
}
// #include <stdio.h>
// int main()
// {
//     char str1[] = "Hello";
//     char str2[] = "World";
//     // Copies contents of str2 to str1
//     ft_memcpy(str1, str2, sizeof(str2));
//     printf("%s\n", str1);
//     return 0;
// }
