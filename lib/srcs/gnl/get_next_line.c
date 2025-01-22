#include "../../includes/libft.h"

char	*get_next_line(int fd)
{
	static char	*rem;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(rem);
		free(buffer);
		rem = NULL;
		buffer = NULL;
	}
	if (!buffer)
		return (NULL);
	line = ft_append(fd, rem, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	rem = ft_next(line);
	return (line);
}

char	*ft_next(char *str)
{
	char	*rem;
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (!str[i])
		return (0);
	rem = ft_substr(str, i + 1, ft_strlen(str) - i);
	if (*rem == 0)
	{
		free(rem);
		rem = NULL;
	}
	str[i + 1] = 0;
	return (rem);
}

char	*ft_append(int fd, char *rem, char *buffer)
{
	ssize_t	bytes_read;
	char	*str;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{	
			free(rem);
			return (0);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = 0;
		if (!rem)
			rem = ft_strdup("");
		str = rem;
		rem = ft_strjoin(str, buffer);
		free(str);
		str = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (rem);
}
