/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:28:50 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/29 13:56:18 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// char my_func(unsigned int i, char c) {
//     // example function that capitalizes every even indexed character
//     if (i % 2 == 0) {
//         return c - 32;
//     }
//     return c;
// }
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char					*res;
	unsigned int			i;

	i = 0;
	if (!s)
		return (NULL);
	res = malloc(ft_strlen(s) + 1);
	if (!(res))
		return (NULL);
	if (!f)
	{
		ft_strlcpy(res, s, ft_strlen(s) + 1);
		return (res);
	}
	while (s[i])
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
// #include <stdio.h>
// int	main(int argc, char **argv)
// {
// 	char 	*s;
// 	char	(*f)(unsigned int, char);	
// 	f = my_func;
// 	s = "hello";	
// 	printf("%s\n", ft_strmapi(s, f));
// }
