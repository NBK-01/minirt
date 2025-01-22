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

typedef enum e_ident
{
	SP, //sphere	
	PL, //plane
	CY, //cylinder
	L,	//light
	C,	//camera
	A,	//ambient lighting
}	t_ident;

/*saves space and time to store all the 
 * object's color values as RGB*/
typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

/*objects come with coordinates to place them 
 * in a given scene, t_pos stores these coordinates*/
typedef struct s_pos
{
	float	x;
	float	y;
	float	z;
}	t_pos;

typedef struct s_sphere
{
	char	*ident;
	t_pos	pos;
	t_color	color;
	float	diameter;
}	t_sphere;

typedef struct s_plane
{
	char	*ident;
	t_pos	pos;
	t_color	color;
	t_pos	vec;
}	t_plane;

typedef struct s_cylinder
{
	char	*ident;
	t_pos	pos;
	t_color	color;
	t_pos	vec;
	float	diameter;
	float	height;
}	t_cylinder;

typedef struct s_data
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
}	t_data;

#endif // !MAIN_H
