/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:47:02 by emedina-          #+#    #+#             */
/*   Updated: 2025/03/19 18:11:10 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Free memory reserved for map_data t_lib and exit
// TODO later split this so it can be called at end of game, too.
void	clear_data(t_lib1 *map_data)
{
	int	i;

	i = 0;
	free (map_data->map_content);
	free (map_data->fullpath);
	if (map_data->map_array)
	{
		while (map_data->map_array[i])
			free (map_data->map_array[i++]);
		free (map_data->map_array);
	}
	i = 0;
	while (i < 4)
		free(map_data->texture_paths[i++]);
	exit (EXIT_FAILURE);
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
		map_is_playable(&map_data);
		init_game(&map_data);
	}
}
