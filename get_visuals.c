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

// Read lines from a file (fd) and store the interesting part.
// Must all fit the order given in spec:
// - 4 textures
// - floor colour
// - ceiling colour
// If any of the retrieved paths are inaccessible, complain and exit.
// NOTE if the colours are invalid, they are still stored. This is a weakness!
// TODO Consider calling read_colours() in the outer function.
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
				map_data->texture_paths[i], fd);
		}
		map_data->texture[i] = mlx_load_png(map_data->texture_paths[i]);
		if (!map_data->texture[i])
		{
			bad_visuals(map_data, "Texture not in PNG format",
				map_data->texture_paths[i], fd);
		}
		i++;
	}
	read_colours(map_data, fd);
}
