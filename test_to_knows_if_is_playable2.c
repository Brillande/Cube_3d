/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_to_knows_if_is_playable2.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:47:47 by emedina-          #+#    #+#             */
/*   Updated: 2024/11/27 17:39:04 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

t_lib1	*test_to_knows_if_is_playable2(t_lib1 *map_data)
{
	isnt_borded_of_walls(map_data->map_array, map_data->how_many_lines,
		map_data->how_many_colums);
	find_out_if_is_playable(map_data);
	return (map_data);
}

// TODO Understand if the flood_fill works for us now
// What is its purpose and how does it work?
void	flood_fill(t_lib1 *map_data, int x, int y)
{
	if (map_data->cpy_of_map_array[x][y] != '1'
		&& map_data->cpy_of_map_array[x][y] != 'E'
		&& map_data->cpy_of_map_array[x][y] != '2')
	{
		map_data->cpy_of_map_array[x][y] = '2';
		flood_fill(map_data, x + 1, y);
		flood_fill(map_data, x - 1, y);
		flood_fill(map_data, x, y + 1);
		flood_fill(map_data, x, y - 1);
	}
}

// FIXME What does this do different from the other flood_fill?
void	flood_fill1(t_lib1 *map_data, int x, int y)
{
	if (map_data->cpy_of_map_array[x][y] != '1')
	{
		map_data->cpy_of_map_array[x][y] = '1';
		flood_fill1(map_data, x + 1, y);
		flood_fill1(map_data, x - 1, y);
		flood_fill1(map_data, x, y + 1);
		flood_fill1(map_data, x, y - 1);
	}
}

// How does this work? Is it needed? We no longer have coins or exits.
void	find_out_if_is_playable(t_lib1 *map_data)
{
	int	playable;

	playable = 1;
	flood_fill(map_data, map_data->player_coor_x, map_data->player_coor_y);
	while (map_data->x < map_data->how_many_lines && playable)
	{
		while (map_data->y < map_data->how_many_colums && playable)
		{
			if (map_data->cpy_of_map_array[map_data->x][map_data->y] != '1'
				&& map_data->cpy_of_map_array[map_data->x][map_data->y] != '0'
				&& map_data->cpy_of_map_array[map_data->x][map_data->y] != 'E'
				&& map_data->cpy_of_map_array[map_data->x][map_data->y] != '2')
				playable = 0;
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
	find_out_if_is_playable2(map_data, playable);
}
