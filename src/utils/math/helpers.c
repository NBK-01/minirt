#include "../../../headers/math.h"
#include "../../../headers/main.h"

double	quadratic(double a, double b, double c)
{
	double	discriminant;
	double	t1;
	double	t2;

	discriminant = b * b - 4.0 * a * c;
	if (discriminant > 0)
	{
		t1 = (-b - sqrt(discriminant)) / (2.0 * a);
		t2 = (-b + sqrt(discriminant)) / (2.0 * a);
		if (t1 > EPSILON)
			return (t1);
		else if (t2 > EPSILON)
			return (t2);
		else
			return (0);
	}
	return (0);
}
