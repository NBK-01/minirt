#include "../../headers/main.h"
#include "../../headers/minirt.h"

void	parse_line(char **split)
{
	if (!ft_strcmp(split[0], "sp"))
		printf("sphere\n");
	if (!ft_strcmp(split[0], "pl"))
		printf("plane\n");
	if (!ft_strcmp(split[0], "cy"))
		printf("cylinder\n");
}

static void	set_line(char *line, t_list **file)
{
	t_list	*new;

	new = ft_lstnew(line);
	ft_lstadd_back(file, new);
}

int read_file(char *filename, t_list **file)
{
	int		fd;
	char	*line;

	fd = ft_open(filename);
	line = get_next_line(fd);
	if (!line)
		return (ft_putstr_fd(RED "Error: empty file :() \n" RESET, 2), 0);
	while (line)
	{
		set_line(line, file);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

bool	parse_file(t_list **file)
{
	t_list	*tmp;
	char	**split;

	tmp = (*file);
	while (tmp)
	{
		split = ft_split(tmp->content, " \t");
		if (!split)
			return (ft_putstr_fd(RED "Error: failed to split line\n" RESET, 2), false);
		parse_line(split);
		tmp = tmp->next;
	}
	return (true);
}
