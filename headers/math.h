/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:04:22 by mmuhaise          #+#    #+#             */
/*   Updated: 2025/02/21 12:59:56 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# include "./main.h"

typedef enum e_op
{
	ADD,
	SUB,
	MULT,
	DIV,
	COS,
	SIN,
	DOT,
	CROSS,
}	t_op;

typedef struct s_quad
{
	double	a;
	double	b;
	double	c;
	double	rad;
	t_pos	oc;
}	t_quad;

typedef union u_result
{
	double	d;
	t_pos	v;
}	t_result;

/*this is a helper function that can take any operation and 
 * apply it to a vector and a scalar -> a scalar op on vectors 
 * applies the scalar and op on each component of the vector.*/
t_pos		vec_scalar(t_pos vec, float scalar, t_op op);
double		quadratic(double a, double d, double c);

////// -------------- DOT PRODUCT -------------- ////////
/*calculates the dot producty of two vectors, vec1 and vec2
 * which is vecA . vecB = mag(vecA) x mag(vecB) X cos(angle)*/

////// -------------- CROSS PRODUCT -------------- ////////
/*calculates the cross product of two vectors, vec1 and vec2. 
 * this will return a new vector that is (perp) to both vec1 and vec2.*/
t_result	vec_dot_cross(t_pos vec1, t_pos vec2, t_op op);

/*this will calculate the magnitude of a vector. (or length) 
 * then normalize which will return the unit vector of the given vector.*/
t_pos		vec_normalize(t_pos vec);
/*return the cos or sin of the given angle between vec1 and vec2.*/
double		vec_angle(double angle, t_op op);

t_pos		vec_operation(t_pos vec1, t_pos vec2, t_op op);
t_pos		normalize(t_pos v);

#endif // !VECTORS_H
