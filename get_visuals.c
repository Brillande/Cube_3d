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
/* static char	*get_texture(char *side, int fd) */
/* { */
/* 	char	*path; */
/* 	char	*tmppath; */
/* 	char	*line; */

/* 	line = find_next_line(fd); */
/* 	if (ft_strncmp(side, line, 2) == 0) */
/* 	{ */
/* 		tmppath = ft_substr(line, 2, ft_strlen(line) - 3); */
/* 		free(line); */
/* 		path = ft_strtrim(tmppath, "\n \t"); */
/* 		free(tmppath); */
/* 	} */
/* 	else */
/* 	{ */
/* 		free (line); */
/* 		return (NULL); */
/* 	} */
/* 	return (path); */
/* } */

static char	*get_texture_from_line(char *side, char *line)
{
	char	*path;
	char	*tmppath;

	if (ft_strncmp(side, line, 2) == 0)
	{
		tmppath = ft_substr(line, 2, ft_strlen(line) - 3);
	//	free(line);
		path = ft_strtrim(tmppath, "\n \t");
		free(tmppath);
	}
	else
	{
//		free (line);
		return (NULL);
	}
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
// FIXME We must be able to read these 6 parts in any order
// TODO Make this NORMed
void	get_visuals(t_lib1 *map_data, int fd)
{
	int	i;
	char	*line;

	i = 0;
	map_data->rgb_ceiling = -1;
	map_data->rgb_floor = -1;
	while ((i <  6))
	{
		line = find_next_line(fd);
		if (ft_strncmp(line, "NO", 2) == 0)
			map_data->texture_paths[NORTH] = get_texture_from_line("NO", line);
		else if (ft_strncmp(line, "SO", 2) == 0)
			map_data->texture_paths[SOUTH] = get_texture_from_line("SO", line);
		else if (ft_strncmp(line, "WE", 2) == 0)
			map_data->texture_paths[WEST] = get_texture_from_line("WE", line);
		else if (ft_strncmp(line, "EA", 2) == 0)
			map_data->texture_paths[EAST] = get_texture_from_line("EA", line);
		else if (ft_strncmp(line, "F", 1) == 0)
			map_data->rgb_floor = get_colour_array_from_line(fd, 'F', line);
		else if (ft_strncmp(line, "C", 1) == 0)
			map_data->rgb_ceiling = get_colour_array_from_line(fd, 'C', line);
		i++;
		if (line)
			free(line);
	}
	i = 0;
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
	if ((map_data->rgb_ceiling == -1) || (map_data->rgb_floor == -1))
		bad_visuals(map_data, "Colour failure", "", fd);
//	read_colours_from_line(map_data, fd);
}
