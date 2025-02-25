/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_the_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:23:01 by emedina-          #+#    #+#             */
/*   Updated: 2025/02/25 17:43:59 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// Read the map data from an already-open file to the BIG STRUCT
// Is it a blank line? carry on until we get something.
// After first good line, add the lines until the end of the file,
// or next blank line
// ...put it all in map_data->map_content
// NOTE the -1 is to remove a newline that later goes away
// NOTE Do not free line it becomes the base of map_content
// TODO Norm fixes and tidying needed here.
// TODO Work out what needs to be freed if find_next_line fails
void	read_map_from_fd(t_lib1 *map_data, int fd)
{
	char	*line;
	char	*newcontent;

	map_data->how_many_lines = 0;
	line = find_next_line(fd);
	if (!line)
		exit (EXIT_FAILURE);
	map_data->how_many_lines++;
	map_data->how_many_colums = ft_strlen(line) - 1;
	map_data->map_content = line;
	line = get_next_line(fd);
	while ((line) && (line_is_blank(line) == 0))
	{
		map_data->how_many_lines++;
		if (((int) ft_strlen(line) - 1) > map_data->how_many_colums)
			map_data->how_many_colums = (ft_strlen(line) - 1);
		newcontent = ft_strjoin(map_data->map_content, line);
		free(line);
		free(map_data->map_content);
		map_data->map_content = newcontent;
		line = get_next_line(fd);
	}
	if (line)
		free(line);
}

// Read the passed character and return its orientation
// (i.e. compass bearing) to be used for the player's intial view.
// Returns -1 if the character is not valid.
// NOTE Perhaps we should return a float / double? Or do we convert later?
int	get_orientation(char c)
{
	if (c == 'N')
		return (0);
	if (c == 'E')
		return (90);
	if (c == 'S')
		return (180);
	if (c == 'W')
		return (270);
	else
		return (-1);
}

// Read the map contents; set player_coor_x and y as well as orientation.
// NOTE The first coordinate in each case is 0!!
// NOTE Careful about X and Y!
// NOTE We intialise player_faces to -1 as 0 is a valid direction
void	get_start_position(t_lib1 *map_data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	map_data->player_faces = -1;
	while (map_data->map_array[i])
	{
		while (map_data->map_array[i][j] != '\0')
		{
			if (ft_strchr("NEWS", map_data->map_array[i][j]))
			{
				map_data->player_coor_x = i;
				map_data->player_coor_y = j;
				map_data->player_faces
					= get_orientation(map_data->map_array[i][j]);
				return ;
			}
			j++;
		}
		i++;
		j = 0;
	}
}
