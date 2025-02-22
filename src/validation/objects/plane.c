#include "../../../headers/minirt.h"

static bool	plane_helper(int *i, char **split)
{
	if (*i == 1)
		if (!check_coordinates(split[*i]))
			return (false);
	if (*i == 2)
		if (!check_vector(split[*i]))
			return (false);
	if (*i == 3)
		if (!check_rgb(split[*i]))
			return (false);
	return (true);
}

bool	validate_plane(char **split)
{
	char	*trim;
	int		trim_size;
	int		i;

	i = -1;
	trim_size = 0;
	if (split && split[0] && split[1] && split[2] && split[3] && split[4])
	{
		trim = ft_strtrim(split[4], "\n");
		trim_size = ft_strlen(trim);
		free(trim);
	}
	while (split[++i])
		if (!plane_helper(&i, split))
			return (false);
	if (trim_size)
		return (exit_err("Error: invalid plane config\n", NULL));
	return (true);
}
