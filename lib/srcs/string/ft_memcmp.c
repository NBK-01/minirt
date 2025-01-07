/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:35:52 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/29 13:56:18 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	const unsigned char	*s1_ptr;
	const unsigned char	*s2_ptr;
	size_t				i;

	if (!str1 && !str2 && !n)
		return (0);
	s1_ptr = (const unsigned char *)str1;
	s2_ptr = (const unsigned char *)str2;
	i = 0;
	while (n--)
	{
		if (s1_ptr[i] != s2_ptr[i])
			return (s1_ptr[i] - s2_ptr[i]);
		i++;
	}
	return (0);
}
// #include <stdio.h>
// int main () {
// const char str[] = "dayef Kanaan";
// const char str2[] = "Nayef";
// 	 	char s[] = {-128, 0, 127, 0};
//         char sCpy[] = {-128, 0, 127, 0};
//         char s2[] = {0, 0, 127, 0};
//         char s3[] = {0, 0, 42, 0};
//    		printf("%d", ft_memcmp(s, sCpy, 4));
//    return(0);
// }
