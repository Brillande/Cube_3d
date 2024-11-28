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

int	main(int argc, char **argv)
{
	t_lib1	map_data;

	if (argc == 1)
	{
		perror("error\nno has seleccionado mapa");
		exit(EXIT_FAILURE);
	}
	if (argc == 2)
	{
		ft_bzero(&map_data, sizeof(map_data));
		join_the_fullpath(&map_data, argv[1]);
		read_the_map(&map_data);
		test_to_knows_if_is_playable(&map_data);
		test_to_knows_if_is_playable2(&map_data);
		init_game(&map_data);
	}
}
