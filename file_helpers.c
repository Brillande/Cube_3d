#include "cube_3d.h"

// TODO Add 42 header

// Skip forward over the blank lines and return the next with content.
char	*find_next_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while ((line) && (line_is_blank(line) == 1))
	{
		free (line);
		line = get_next_line(fd);
	}
	return (line);
}

// Return 1 if the line only contains spaces.
// 0 if there is some other kind character
int	line_is_blank(char *line)
{
	int	i;

	i = 0;
	while ((line) && (line[i] != '\0'))
	{
		if (ft_isprint(line[i++]))
			return (0);
	}
	return (1);
}
