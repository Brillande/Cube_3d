#include "cube_3d.h"
#include <fcntl.h>
#include <sys/stat.h>

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

// Checks the path is executable, a regular file and executable by the user.
// Return 0 if the path can't be used
// Return 1 if the path can be used.
int	test_path(char *path)
{
	struct stat	pstat;

	if (stat(path, &pstat) == -1)
		return (0);
//	ft_printf("Testing path: %s\n", path);	// HACK for debugging
	if ((access(path, R_OK) == 0)
		&& S_ISREG(pstat.st_mode))
		return (1);
	else
		return (0);
}

// Takes the value from argv[1], checks it's valid and...
// Adds the full (relative) path for the map to the data struct->fullpath
// TODO Remove hardcoding of maps_directory (move to .h or something)
// NOTE Fullpath gets freed in the clear_data function on failure.
void	join_the_fullpath(t_lib1 *map_data, char *map_name)
{
	char	*map_name_with_extension;
	char	*maps_directory;

	map_name_with_extension = check_extension(map_name);
	if (map_name_with_extension != NULL)
	{
		maps_directory = "maps/";
		map_data->fullpath = ft_strjoin(maps_directory,
				map_name_with_extension);
		if (map_data->fullpath == NULL)
		{
			perror("Error\n al asignar memoria\n");
			exit(EXIT_FAILURE);
		}
	}
}

// Check that the filename ends in .cub.
// If yes, return the string; if no, exit the program.
char	*check_extension(char *map_extension)
{
	int	leng;

	leng = 0;
	leng = ft_strlen(map_extension);
	if (map_extension[leng - 1] == 'b' && map_extension[leng - 2] == 'u'
		&& map_extension[leng - 3] == 'c' && map_extension[leng - 4] == '.')
	{
		return (map_extension);
	}
	else
	{
		perror("Error\nLa extension no es .cub\n");
		exit(EXIT_FAILURE);
	}
}
