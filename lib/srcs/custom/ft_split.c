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


int	ft_is_sep(char x, const char *separators)
{
	while (*separators)
	{
		if (x == *separators)
			return (1);
		separators++;
	}
	if (x == '\0')
		return (1);
	return (0);
}


int	ft_word_count(char const *str, const char *separators)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (ft_is_sep(str[i + 1], separators)
			&& !(ft_is_sep(str[i], separators)))
			count++;
		i++;
	}
	return (count);
}

void	ft_print(char *dest, char const *src, const char *separators)
{
	int	i;

	i = 0;
	while (!(ft_is_sep(src[i], separators)))  // Now using separators string
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	ft_print_split(char **res, char const *str, const char *separators)
{
	int	i;
	int	j;
	int	token;

	i = 0;
	token = 0;
	while (str[i] != '\0')
	{
		if (ft_is_sep(str[i], separators))
			i++;
		else
		{
			j = 0;
			while (!(ft_is_sep(str[i + j], separators)))
				j++;
			res[token] = (char *)malloc(sizeof(char) * (j + 1));
			ft_print(res[token], str + i, separators);
			i += j;
			token++;
		}
	}
}


char	**ft_split(char const *s, const char *separators)
{
	char	**res;
	int		count;

	count = ft_word_count(s, separators);
	res = (char **)malloc(sizeof(char *) * (count + 1));
	res[count] = 0;
	ft_print_split(res, s, separators);
	return (res);
}
