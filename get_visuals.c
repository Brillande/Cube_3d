/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_visuals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:14:36 by chaikney          #+#    #+#             */
/*   Updated: 2025/04/02 18:27:56 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	*get_texture_from_line(char *side, char *line)
{
	char	*path;
	char	*tmppath;

	if (ft_strncmp(side, line, 2) == 0)
	{
		tmppath = ft_substr(line, 2, ft_strlen(line) - 3);
		path = ft_strtrim(tmppath, "\n \t");
		free(tmppath);
	}
	else
	{
		return (NULL);
	}
	return (path);
}

static void	process_line(t_lib1 *map_data, int fd, char *line)
{
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
}

// NOTE This count *only* works if we are guaranteed
// to receive a non-blank line!
void	parse_visuals(t_lib1 *map_data, int fd)
{
	int		i;
	char	*line;
	char	*tmp;

	i = 0;
	while (i < 6)
	{
		tmp = find_next_line(fd);
		line = ft_strtrim(tmp, " ");
		if (!tmp || tmp[0] == '1')
		{
			if (tmp)
				free(tmp);
			bad_visuals(map_data,
				"the map its not under textures,ceiling and floor", "", fd);
		}
		process_line(map_data, fd, line);
		i++;
		if (line)
			free(line);
		if (tmp)
			free(tmp);
	}
}

void	validate_texture_paths(t_lib1 *map_data, int fd)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!test_path(map_data->texture_paths[i]))
		{
			bad_visuals(map_data, "Inaccessible path",
				map_data->texture_paths[i], fd);
		}
		i++;
	}
}

// Read lines from a file (fd) and store the interesting part.
// Must all fit the order given in spec:
// - 4 textures
// - floor colour
// - ceiling colour
// If any of the retrieved paths are inaccessible, complain and exit.
// NOTE if the colours are invalid, they are still stored. This is a weakness!
void	get_visuals(t_lib1 *map_data, int fd)
{
	map_data->rgb_ceiling = -1;
	map_data->rgb_floor = -1;
	parse_visuals(map_data, fd);
	validate_texture_paths(map_data, fd);
	load_textures(map_data, fd);
	if ((map_data->rgb_ceiling == -1) || (map_data->rgb_floor == -1))
		bad_visuals(map_data, "Colour failure", "", fd);
}
