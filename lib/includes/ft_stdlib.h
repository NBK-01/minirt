/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdlib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbk <nbk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:23:45 by nbk               #+#    #+#             */
/*   Updated: 2024/09/09 03:43:13 by nbk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDLIB_H
# define FT_STDLIB_H
# include "./libft.h"

int			ft_atoi(const char *str);
__int128	ft_atoll(const char *str);
void		*ft_calloc(size_t count, size_t size);

#endif
