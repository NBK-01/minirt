/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:27:53 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/16 13:38:24 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdarg.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	char	*res;

	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		res[i++] = *s1++;
	while (s2 && *s2)
		res[i++] = *s2++;
	res[i] = '\0';
	return (res);
}

static size_t	total_length(int count, va_list args)
{
	int			i;
	size_t		len;
	const char	*str;

	i = -1;
	len = 0;
	while (++i < count)
	{
		str = va_arg(args, const char *);
		if (str)
			len += ft_strlen(str);
	}
	return (len);
}

char	*ft_strjoin_n(int count, ...)
{
	char		*result;
	char		*ptr;
	const char	*str;
	int			i;
	va_list		args;

	if (count <= 0)
		return (NULL);
	va_start(args, count);
	i = total_length(count, args);
	va_end(args);
	result = (char *)malloc(i + 1);
	va_start(args, count);
	ptr = result;
	i = -1;
	while (++i < count)
	{
		str = va_arg(args, const char *);
		if (str)
			while (*str)
				*ptr++ = *str++;
	}
	va_end(args);
	*ptr = '\0';
	return (result);
}
