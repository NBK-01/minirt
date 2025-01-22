#ifndef MINIRT_H
#define MINIRT_H

#include "main.h"

bool	valid_args(int ac, char **av);
int		read_file(char *filename, t_list **file);
bool	parse_file(t_list **file);

#endif // !MINIRT>_H
