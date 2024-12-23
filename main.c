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
	char	*line;
	char	*newcontent;

	map_data->how_many_colums = 0;
	map_data->how_many_lines = 0;
	line = get_next_line(fd);
	while ((line) && (line_is_blank(line) == 1))
	{
		free (line);
		line = get_next_line(fd);
	}
	map_data->map_content = line;	// HACK This is to put *something* there before strjoin call, but may mess up the map...
	while ((line) && (line_is_blank(line) == 0))
	{
		map_data->how_many_lines++;
		if ((int) ft_strlen(line) > map_data->how_many_colums)
			map_data->how_many_colums = ft_strlen(line);
		newcontent = ft_strjoin(map_data->map_content, line);	// FIXME this causes invlaid read
		free(line);
		// FIXME Invalid free here.
//		free(map_data->map_content);
		map_data->map_content = newcontent;
		line = get_next_line(fd);
	}
	if (line)
		free(line);
}

void	print_read_from_file(t_lib1 map_data)
{
	ft_printf("Have read file\n");
	ft_printf("North texture: %s\n", map_data.texture_paths[0]);
	ft_printf("South texture: %s\n", map_data.texture_paths[1]);
	ft_printf("East texture: %s\n", map_data.texture_paths[2]);
	ft_printf("West texture: %s\n", map_data.texture_paths[3]);
	ft_printf("Floor colour: %i\n", map_data.rgb_floor);
	ft_printf("Ceiling colour: %i\n", map_data.rgb_ceiling);
	ft_printf("Map data read:\n%s", map_data.map_content);
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
		print_read_from_file(map_data);		// HACK this is for debugging only
//		read_the_map(&map_data);
		test_to_knows_if_is_playable(&map_data);
		init_game(&map_data);
	}
}
