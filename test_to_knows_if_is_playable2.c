/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_to_knows_if_is_playable2.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:47:47 by emedina-          #+#    #+#             */
/*   Updated: 2023/09/19 19:06:25 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_lib1	*test_to_knows_if_is_playable2(t_lib1 *map_data)
{
	so_many_p_e_c_has(map_data, map_data->map_array);
	isnt_borded_of_walls(map_data->map_array, map_data->how_many_lines,
		map_data->how_many_colums);
	find_out_if_is_playable(map_data);
	return (map_data);
}

void	so_many_p_e_c_has(t_lib1 *map_data, char **map)
{
	int	p;
	int	e;

	map_data->total_coins = count_p_e_c(map, map_data, 'C');
	p = count_p_e_c(map, map_data, 'P');
	e = count_p_e_c(map, map_data, 'E');
	if (map_data->total_coins == 0 || p == 0 || e == 0 || p > 1 || e > 1)
	{
		perror("error\nnumero de monedas, salidas o jugadores incorrecto");
		exit(EXIT_FAILURE);
	}
}

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
