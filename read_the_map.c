/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_the_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:23:01 by emedina-          #+#    #+#             */
/*   Updated: 2024/11/27 17:38:47 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// Read the map data from an already-open file to the BIG STRUCT
// Is it a blank line? carry on until we get something.
// After first good line, add the lines until the end of the file,
// or next blank line
// ...put it all in map_data->map_content
// NOTE the -1 is to remove a newline that later goes away
void	read_map_from_fd(t_lib1 *map_data, int fd)
{
	char	*line;
	char	*newcontent;

	map_data->how_many_lines = 0;
	line = find_next_line(fd);
	if (!line)
		exit (EXIT_FAILURE);	// HACK should free things not just exit
	map_data->how_many_lines++;
	map_data->how_many_colums = ft_strlen(line) - 1;
	map_data->map_content = line;	// NOTE This is to put *something* there before strjoin call, but may mess up the map...
//	free (line);	// NOTE Do not free this, it is the base of map_content now
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
