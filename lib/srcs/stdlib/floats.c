#include "../../includes/libft.h"

void	strol_helper(int *sign, const char **str)
{
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			*sign = -1;
		str++;
	}
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	long	result;
	int		sign;
	int		digit;

	result = 0;
	sign = 1;
	if (str == NULL)
	{
		if (endptr)
			*endptr = (char *)str;
		return (0);
	}
	strol_helper(&sign, &str);
	while (ft_isdigit(*str))
	{
		digit = *str - '0';
		if (digit >= base)
			break ;
		result = result * base + digit;
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return (sign * result);
}
