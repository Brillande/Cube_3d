#include "cube_3d.h"
#include "libft/libft.h"

// open file
// read lines until we have NEWS -- a file path
// Floor colour
// Ceiling colour -- must be 3 colours type
// After that we skip blank lines until we reach the map
// ...then switch context.

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

// Lifted from the documentation
// https://harm-smits.github.io/42docs/libs/minilibx/colors.html
// "Since each byte contains 2^8 = 256 values (1 byte = 8 bits),
// and RGB values range from 0 to 255, we can perfectly fit
// a integer (as an int is 4 bytes).
// In order to set the values programatically we use bitshifting."
static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

// Extract a texture path from a line
// Check the side matches the start of the line
// move past the texture, everything after that key is path
// (may need trimmed)
// Check path is valid.
// return NULL if not
static char	*get_texture(char *side, int fd)
{
    char	*path;
    char	*line;

	line = find_next_line(fd);
   if (ft_strncmp(side, line, 2) == 0)
    {
		// NOTE -2 for the starting code, -1 to remove the newline
        path = ft_substr(line, 2, ft_strlen(line) - 3);
    }
    free (line);
    return (path);
}

// Process a floor / colour line
// Make sure it has the F / C key
// (return NULL if not present)
// split the rest on commas?
// Then, atoi them
// Does atoi skip over the intitial letters? Can we make it?
// HACK THere is no allocation of memory for colours, does that break it?
// FIXME Must free the parts array before returning.
// FIXME This will be too long for norm
// FIXME Too many variables
// TODO Will need to harden this against bad input.
static int	get_colours(int fd, char key)
{
    int	i;
    char	*line;
    char	**parts;
    int	r;
    int	g;
    int	b;
	char	*tmp;

    i = 0;
	line = find_next_line(fd);
	parts = ft_split(line, ',');
    free (line);
	/* if (!parts[3]) */
	/* 	return (-1); */
    while (parts[0][i] != key)
    {
        if (parts[0][i++] == '\0')
            return (-1);
    }
	tmp = ft_substr(parts[0], 2, ft_strlen(parts[0]) - 2);
    r = ft_atoi(tmp);
	free(tmp);
    g = ft_atoi(parts[1]);
    b = ft_atoi(parts[2]);
	ft_printf("Colour read\t%i\t%i\t%i\n", r, g, b);	// HACK for debugging
	// FIXME This frees evertything but is so FRAGILE
	free(parts[0]);
	free(parts[1]);
	free(parts[2]);
	free(parts[3]);
	free(parts);
    return (create_trgb(0, r, g, b));
}

// read each line from a file (fd?) and make sure it fits the
// order given in spec
// NOTE see what join_the_full_path does / returns
// FIXED get_next_line is not in the libft we have here :|
// TODO get_texture does not use the paths returned, or attempt to load them.
void	get_visuals(t_lib1 *map_data, int fd)
{
    map_data->texture_paths[0] = get_texture("NO", fd);
    map_data->texture_paths[1] = get_texture("SO", fd);
    map_data->texture_paths[2] = get_texture("WE", fd);
    map_data->texture_paths[3] = get_texture("EA", fd);
    map_data->rgb_floor = get_colours(fd, 'F');
    map_data->rgb_ceiling = get_colours(fd, 'C');
}
