/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:47:02 by emedina-          #+#    #+#             */
/*   Updated: 2024/11/27 17:38:25 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"
#include <stdlib.h>

// Read the map data from an already-open file to the BIG STRUCT
// Is it a blank line? carry on until we get something.
// After first good line, add the lines until the end of the file,
// or next blank line
// ...put it all in map_data->map_content
// TODO Test this function
// TODO Find out where to put size_x and size_y, use it directly.
void	read_map_from_fd(t_lib1 *map_data, int fd)
{
	size_t	size_x;
	size_t	size_y;
	char	*line;
	char	*newcontent;

	size_x = 0;
	size_y = 0;
	line = get_next_line(fd);
	while ((line) && (line_is_blank(line) == 1))
	{
		free (line);
		line = get_next_line(fd);
	}
	while ((line) && (line_is_blank(line) == 0))
	{
		size_y++;
		if (ft_strlen(line) > size_x)
			size_x = ft_strlen(line);
		newcontent = ft_strjoin(map_data->map_content, line);
		free(line);
		free(map_data->map_content);
		map_data->map_content = newcontent;
		line = get_next_line(fd);
	}
	if (line)
		free(line);
}

// Initialises a map data object
// Get a filepath from the args, do some checking, add it to map data
// reads the path into a buffer -- we don't want to do that any more
int	main(int argc, char **argv)
{
	t_lib1	map_data;
	int		fd;

	if (argc == 1)
	{
		perror("error\nno has seleccionado mapa");
		exit(EXIT_FAILURE);
	}
	if (argc == 2)
	{
		ft_bzero(&map_data, sizeof(map_data));
		join_the_fullpath(&map_data, argv[1]);
		fd = open(map_data.fullpath, O_RDONLY);
		if ((!fd) || (fd == -1))
			exit(EXIT_FAILURE);
		get_visuals(&map_data, fd);
		read_map_from_fd(&map_data, fd);
//		read_the_map(&map_data);
		test_to_knows_if_is_playable(&map_data);
		init_game(&map_data);
	}
}
