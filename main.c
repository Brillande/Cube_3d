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
		map_is_playable(&map_data);
		init_game(&map_data);
	}
}
