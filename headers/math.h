#ifndef MATH_H
# define MATH_H

# include "./main.h"

typedef enum  e_op
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

typedef union u_result {
    double d;
    t_pos v;
} u_result;

/*this is a helper function that can take any operation and 
 * apply it to a vector and a scalar -> a scalar op on vectors 
 * applies the scalar and op on each component of the vector.*/
t_pos	vec_scalar(t_pos vec, float scalar, t_op op);

////// -------------- DOT PRODUCT -------------- ////////
/*calculates the dot producty of two vectors, vec1 and vec2
 * which is vecA . vecB = mag(vecA) x mag(vecB) X cos(angle)*/

////// -------------- CROSS PRODUCT -------------- ////////
/*calculates the cross product of two vectors, vec1 and vec2. 
 * this will return a new vector that is (perp) to both vec1 and vec2.*/
u_result	vec_dot_cross(t_pos vec1, t_pos vec2, t_op op);

/*this will calculate the magnitude of a vector. (or length) 
 * then normalize which will return the unit vector of the given vector.*/
t_pos	vec_normalize(t_pos vec);
/*return the cos or sin of the given angle between vec1 and vec2.*/
double	vec_angle(double angle, t_op op);

t_pos	vec_operation(t_pos vec1, t_pos vec2, t_op op);

#endif // !VECTORS_H
