/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_to_knows_if_is_playable3.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:03:19 by emedina-          #+#    #+#             */
/*   Updated: 2023/09/19 19:03:36 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_out_if_is_playable2(t_lib1 *map_data, int playable)
{
	flood_fill1(map_data, map_data->player_coor_x, map_data->player_coor_y);
	map_data->x = 0;
	map_data->y = 0;
	while (map_data->x < map_data->how_many_lines && playable)
	{
		while (map_data->y < map_data->how_many_colums && playable)
		{
			if (map_data->cpy_of_map_array[map_data->x][map_data->y] != '1'
				&& map_data->cpy_of_map_array[map_data->x][map_data->y] != '0')
			{
				playable = 0;
			}
			map_data->y++;
		}
		map_data->y = 0;
		map_data->x++;
	}
	if (!playable)
	{
		perror("error\nno puede recoger todas las monedas y llegar a la salida");
		exit(EXIT_FAILURE);
	}
}
