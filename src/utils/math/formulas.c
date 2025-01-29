#include <math.h>

double	quadratic(double a, double d, double c)
{
	double	discriminant;
	double	t1;
	double	t2;

	discriminant = d * d - 4.0 * a * c;
	if (discriminant > 0)
	{
		t1 = (-d - sqrt(discriminant)) / (2.0 * a);
		t2 = (-d + sqrt(discriminant)) / (2.0 * a);
		if (t1 > 0)
			return (t1);
		else if (t2 > 0)
			return (t2);
	}
	return (0);
}
