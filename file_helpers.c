#include "cube_3d.h"
#include <fcntl.h>
#include <sys/stat.h>

// TODO Add 42 header
// TODO Merge with join_the_fullpath

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

// Checks the path is executable, a regular file and executable by the user.
// Return 0 if the path can't be used
// Return 1 if the path can be used.
int	test_path(char *path)
{
	struct stat	pstat;

	if (stat(path, &pstat) == -1)
		return (0);
//	ft_printf("Testing path: %s\n", path);
	if ((access(path, R_OK) == 0)
		&& S_ISREG(pstat.st_mode))
		return (1);
	else
		return (0);
}
