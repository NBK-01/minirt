/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:28:13 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/29 13:56:18 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_is_set(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_is_set(*s1, set))
		s1++;
	i = 0;
	while (s1[i])
		i++;
	i--;
	while (i >= 0 && ft_is_set(s1[i], set))
		i--;
	return (ft_substr(s1, 0, i + 1));
}
// char *ft_strtrim(const char *s1, const char *set)
// {
// 	int i;
// 	int j;
// 	int left;
// 	int right;
// 	char *result;
// 	i = 0;
// 	if (!(set) || !(s1))
// 		return (NULL);
// 	while (s1[i] && ft_charset_contains(s1[i], set))
// 		i++;
// 	left = i;
// 	i = 0;
// 	while (s1[i])
// 		i++;
// 	i--;
// 	while (i >= 0 && ft_charset_contains(s1[i], set))
// 		i--;
// 	right = i + 1;
// 	j = 0;
// 	result = (char *)malloc(sizeof(char) * (right - left + 2));
// 	if (result == NULL)
// 		return (NULL);
// 	while (left < right)
// 	{
// 		result[j++] = s1[left++];
// 	}
// 	result[j] = '\0';
// 	return (result);
// }
// #include <stdio.h>
// int main() {
//     const char *input_str = "   xxx   xxx";
//     const char *charset = " x";
//     char *trimmed_str = ft_strtrim(input_str, charset);
//     if (trimmed_str) {
//         printf("Original string: '%s'\n", input_str);
//         printf("Trimmed string: '%s'\n", trimmed_str);
//         free(trimmed_str); // Freeing allocated memory
//     } else {
//         printf("Memory allocation failed!\n");
//     }
//     return 0;
// }
