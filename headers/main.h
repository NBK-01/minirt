#ifndef MAIN_H
# define MAIN_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>
# include "../lib/mlx/mlx.h"
# include <X11/X.h>
# include <math.h>
# include <X11/keysym.h>
# include "../lib/includes/libft.h"

/////////////////////////////////////////
//////////		DEFS		////////////
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

# define MALLOC_ERR RED "minirt: failed allocating: %s\n" RESET
# define MLX_ERR	RED "minirt: mlx failure: %s\n" RESET


#endif // !MAIN_H
