#include "cub3D.h"

// Reads lines from file descriptor fd.
// - when the next (non-blank) line is found, split it at commas
// - Look for the key char (i.e. F or C)
// -- we will skip over / allow leading spaces
// - If found, send the array to be turned into colours.
// - If NOT found, free the split array and return -1
// NOTE In happy case, parts array is freed in return function.
// TODO Check we have parts array with 3(?) members
int	get_colours(int fd, char key)
{
	int		i;
	int		j;
	char	*line;
	char	**parts;

	i = 0;
	line = find_next_line(fd);
	parts = ft_split(line, ',');
	free (line);
	while (parts[0][i] != key)
	{
		if (parts[0][i++] == '\0')
		{
			j = 0;
			while (parts[j] != (void *)0)
				free (parts[j++]);
			free (parts);
			return (-1);
		}
	}
	return (get_colours_from_array(parts));
}

// Receive a string array of 3 integers representing red green and blue
// Return a single integer composed of those values.
// TODO Will need to harden this against bad input.
// - less than 2 parts?
// - atoi returns something that is not a (valid) number?
// Does atoi skip over the intitial letters? Can we make it?
// FIXME Segfaults with less than 3 parts to the array.
int	get_colours_from_array(char **parts)
{
	int		r;
	int		g;
	int		b;
	char	*tmp;
	int		i;

	i = 0;
	if (parts[3] != (void *) 0)
	{
		printf("this line is not in the correct format\n");
		while (parts[i])
			free(parts[i++]);
		free (parts);
		return (-1);
	}
	tmp = ft_substr(parts[0], 2, ft_strlen(parts[0]) - 2);
	r = ft_atoi(tmp);
	free(tmp);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	while (parts[i])
		free(parts[i++]);
	free(parts);
	return (create_trgb(0, r, g, b));
}

// Lifted from the documentation
// https://harm-smits.github.io/42docs/libs/minilibx/colors.html
// "Since each byte contains 2^8 = 256 values (1 byte = 8 bits),
// and RGB values range from 0 to 255, we can perfectly fit
// a integer (as an int is 4 bytes).
// In order to set the values programatically we use bitshifting."
int	create_trgb(int t, int r, int g, int b)
// Wrapper function for safely collecting the 2 colours from an open fd.
// FIXME Catch ALL colour-reading failures.
void	read_colours(t_lib1 *data, int fd)
{
	return (t << 24 | r << 16 | g << 8 | b);
	data->rgb_floor = get_colours(fd, 'F');
	data->rgb_ceiling = get_colours(fd, 'C');
	if ((data->rgb_floor == -1) || (data->rgb_ceiling == -1))
		bad_visuals(data, "Colour failure", "");
}
