/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:39:10 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/29 13:56:18 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_is_sep(char x, char c)
{
	if (x == c)
		return (1);
	if (x == '\0')
		return (1);
	else
		return (0);
}

int	ft_word_count(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (ft_is_sep(str[i + 1], c)
			&& !(ft_is_sep(str[i], c)))
			count++;
		i++;
	}
	return (count);
}

void	ft_print(char *dest, char const *src, char c)
{
	int	i;

	i = 0;
	while (!(ft_is_sep(src[i], c)))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	ft_print_split(char **res, char const *str, char c)
{
	int	i;
	int	j;
	int	token;

	i = 0;
	token = 0;
	while (str[i] != '\0')
	{
		if (ft_is_sep(str[i], c))
			i++;
		else
		{
			j = 0;
			while (!(ft_is_sep(str[i + j], c)))
				j++;
			res[token] = (char *)malloc(sizeof(char) * (j + 1));
			ft_print(res[token], str + i, c);
			i += j;
			token++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		count;

	count = ft_word_count(s, c);
	res = (char **)malloc(sizeof(char *) * (count + 1));
	res[count] = 0;
	ft_print_split(res, s, c);
	return (res);
}
