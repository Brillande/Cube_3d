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

// TODO Understand what this tests
t_lib1	*test_to_knows_if_is_playable2(t_lib1 *map_data)
{
	isnt_borded_of_walls(map_data->map_array, map_data->how_many_lines,
		map_data->how_many_colums);
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
