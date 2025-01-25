/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:32:10 by nkanaan           #+#    #+#             */
/*   Updated: 2024/06/17 10:17:03 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define RESET       "\033[0m"
# define BLACK       "\033[0;30m"
# define RED         "\033[1;31m"
# define GREEN       "\033[0;32m"
# define YELLOW      "\033[0;33m"
# define MAGENTA     "\033[0;35m"
# define CYAN        "\033[0;36m"
# define WHITE       "\033[0;37m"
# define BG_RED     "\033[41m"
# define BG_GREEN   "\033[42m"
# define BG_YELLOW  "\033[43m"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./ft_ctype.h"
# include "./ft_string.h"
# include "./ft_stdlib.h"
# include "./custom.h"
# include "./list.h"

char	*get_next_line(int fd);
char	*ft_append(int fd, char *rem, char *buffer);
char	*ft_next(char *str);

#endif
