/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:31:04 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/01/24 14:55:49 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define WIDTH		1200
# define HEIGHT		900

typedef enum e_ident
{
	SP, //sphere	
	PL, //plane
	CY, //cylinder
	L,	//light
	C,	//camera
	A,	//ambient lighting
}	t_ident;

/*RGB, no more no less*/
typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

/*objects come with coordinates to place them 
 * in a given scene, t_pos stores these coordinates*/
typedef struct s_pos
{
	float	x;
	float	y;
	float	z;
}	t_pos;

typedef struct s_ambient
{
	char	ident;
	float	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	char	ident;
	t_pos	pos;
	t_pos	vec;
	int		fov;
}	t_camera;





typedef struct s_light
{
	char	ident;
	t_pos	pos;
	float	ratio;
	t_color	color; // not used in mando -- will keep as white or remove. we'll find out :)
}	t_light;

typedef struct s_mlx {
    void *mlx;
    void *window;
    void *img;
    int *data;
} t_mlx;

typedef struct s_sphere
{
	char	*ident;
	t_pos	pos;
	float	diameter;
	t_color	color;
}	t_sphere;

union u_figures
{
	t_sphere	sp;
};

typedef struct s_plane
{
	char	*ident;
	t_pos	pos;
	t_pos	vec;
	t_color	color;
}	t_plane;

typedef struct s_inter
{
	int				i;
	enum e_ident	type;
	t_sphere		sp;
	t_plane			pl;
	double			dist;
	t_pos			point;
	t_pos			normal;
	t_color			c;
}	t_inter;

typedef struct s_ray
{
	t_pos	origin;
	t_pos	dir;
	t_inter	*inter;
}	t_ray; ;


typedef struct s_cylinder
{
	char	*ident;
	t_pos	pos;
	t_pos	vec;
	float	diameter;
	float	height;
	t_color	color;
}	t_cylinder;


typedef struct s_data
{
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_sphere	**sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_mlx		*mlx;
}	t_data;

#endif // !MAIN_H
