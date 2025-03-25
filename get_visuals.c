/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_visuals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:14:36 by chaikney          #+#    #+#             */
/*   Updated: 2025/03/19 14:06:32 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Lifted from the documentation
// https://harm-smits.github.io/42docs/libs/minilibx/colors.html
// "Since each byte contains 2^8 = 256 values (1 byte = 8 bits),
// and RGB values range from 0 to 255, we can perfectly fit
// a integer (as an int is 4 bytes).
// In order to set the values programatically we use bitshifting."
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

// Extract a texture path from a line
// Check the side matches the start of the line
// move past the texture, everything after that key is path
// (may need trimmed)
// Check path is valid.
// return NULL if not
// NOTE In substr: -2 for the starting code, -1 to remove the newline
static char	*get_texture(char *side, int fd)
{
	char	*path;
	char	*tmppath;
	char	*line;

	line = find_next_line(fd);
	if (ft_strncmp(side, line, 2) == 0)
	{
		tmppath = ft_substr(line, 2, ft_strlen(line) - 3);
		path = ft_strtrim(tmppath, "\n \t");
		free(tmppath);
	}
	free (line);
	return (path);
}

// Receive a string array of 3 integers representing red green and blue
// Return a single integer composed of those values.
// TODO Will need to harden this against bad input.
// - less than 2 parts?
// - atoi returns something that is not a (valid) number?
static int	get_colours_from_array(char **parts)
{
	int		r;
	int		g;
	int		b;
	char	*tmp;
	int		i;

	tmp = ft_substr(parts[0], 2, ft_strlen(parts[0]) - 2);
	r = ft_atoi(tmp);
	free(tmp);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
	return (create_trgb(0, r, g, b));
}

// Reads lines from file descriptor fd.
// - when the next (non-blank) line is found, split it at commas
// - Look for the key char (i.e. F or C)
// -- we will skip over / allow leading spaces
// - If found, send the array to be turned into colours.
// - If NOT found, free the split array and return -1
// Does atoi skip over the intitial letters? Can we make it?
// NOTE In happy case, parts array is freed in return function.
// TODO A valid parts array would have _ members?
static int	get_colours(int fd, char key)
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

// Read lines from a file (fd) and store the interesting part.
// Must all fit the order given in spec:
// - 4 textures
// - floor colour
// - ceiling colour
// If any of the retrieved paths are inaccessible, complain and exit.
// NOTE if the colours are invalid, they are still stored. This is a weakness!
// FIXME Catch colour-reading failures.
// FIXME Too many lines in get_visuals()
void	get_visuals(t_lib1 *map_data, int fd)
{
	int	i;

	i = 0;
	map_data->texture_paths[NORTH] = get_texture("NO", fd);
	map_data->texture_paths[SOUTH] = get_texture("SO", fd);
	map_data->texture_paths[WEST] = get_texture("WE", fd);
	map_data->texture_paths[EAST] = get_texture("EA", fd);
	while (i < 4)
	{
		if (!test_path(map_data->texture_paths[i]))
		{
			bad_visuals(map_data, "Inaccessible path",
				map_data->texture_paths[i]);
		}
		map_data->texture[i] = mlx_load_png(map_data->texture_paths[i]);
		if (!map_data->texture[i])
		{
			bad_visuals(map_data, "Texture not in PNG format",
				map_data->texture_paths[i]);
		}
		i++;
	}
	map_data->rgb_floor = get_colours(fd, 'F');
	map_data->rgb_ceiling = get_colours(fd, 'C');
	if ((map_data->rgb_floor == -1) || (map_data->rgb_ceiling == -1))
		bad_visuals(map_data, "Colour failure", "");
}
