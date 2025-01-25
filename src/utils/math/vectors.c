#include "../../../headers/math.h"

u_result	vec_dot_cross(t_pos vec1, t_pos vec2, t_op op)
{
	t_pos	result;
	u_result	res;

	res = (u_result){0};
	if (op == DOT)
	{
		res.d = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
		return (res);
	}
	else if (op == CROSS)
	{
		result.x = vec1.y * vec2.z - vec1.z * vec2.y;
		result.y = vec1.z * vec2.x - vec1.x * vec2.z;
		result.z = vec1.x * vec2.y - vec1.y * vec2.x;
		res.v = result;
		return (res);
	}
	return (res);
}

double	vec_angle(double angle, t_op op)
{
	if (op == COS)
		return (cos(angle));
	else if (op == SIN)
		return (sin(angle));
	return (0);
}

t_pos	vec_normalize(t_pos vec)
{
	double	mag;

	mag = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	if (mag == 0)
		return (vec);
	vec.x /= mag;
	vec.y /= mag;
	vec.z /= mag;
	return (vec);
}

t_pos	vec_operation(t_pos vec1, t_pos vec2, t_op op)
{
	t_pos	result;

	if (op == ADD)
	{
		result.x = vec1.x + vec2.x;
		result.y = vec1.y + vec2.y;
		result.z = vec1.z + vec2.z;
	}
	else if (op == SUB)
	{
		result.x = vec1.x - vec2.x;
		result.y = vec1.y - vec2.y;
		result.z = vec1.z - vec2.z;
	}
	return (result);
}

t_pos	vec_scalar(t_pos vec, float scalar, t_op op)
{
	if (op == ADD)
	{
		vec.x += scalar;
		vec.y += scalar;
		vec.z += scalar;
	}
	else if (op == SUB)
	{
		vec.x -= scalar;
		vec.y -= scalar;
		vec.z -= scalar;
	}
	else if (op == MULT)
	{
		vec.x *= scalar;
		vec.y *= scalar;
		vec.z *= scalar;
	}
	else if (op == DIV)
	{
		vec.x /= scalar;
		vec.y /= scalar;
		vec.z /= scalar;
	}
	return (vec);
}
