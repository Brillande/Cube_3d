/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:58:09 by emedina-          #+#    #+#             */
/*   Updated: 2023/09/23 16:27:26 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_img2(t_lib1 *map_data)
{
	int	i;
	int	j;

	i = 0;
	while (map_data->map_array[i])
	{
		j = 0;
		while (map_data->map_array[i][j] != '\0')
		{
			if (map_data->map_array[i][j] == 'C')
				mlx_put_image_to_window(map_data->mlx, map_data->win,
					map_data->coin, (j * 64) + 16, (i * 64) + 16);
			if (map_data->map_array[i][j] == 'E')
				mlx_put_image_to_window(map_data->mlx, map_data->win,
					map_data->exit, j * 64, (i * 64) + 8);
			j++;
		}
		i++;
	}
}

void	print_img3(t_lib1 *map_data)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (map_data->map_array[i][j] != 'P')
	{
		j++;
		if (map_data->map_array[i][j] == '\0')
		{
			j = 0;
			i++;
		}
	}
	mlx_put_image_to_window(map_data->mlx, map_data->win, map_data->player, (j
			* 64) + 14, (i * 64) - 4);
}

int	key_hook(int keycode, t_lib1 *map_data)
{
	int	y;
	int	x;

	x = map_data->player_coor_x;
	y = map_data->player_coor_y;
	if (keycode == 53)
		exit_game(map_data);
	else if (keycode == 13)
		move(map_data, x - 1, y);
	else if (keycode == 1)
		move(map_data, x + 1, y);
	else if (keycode == 0)
		move(map_data, x, y - 1);
	else if (keycode == 2)
		move(map_data, x, y + 1);
	return (0);
}

int	move(t_lib1 *map_data, int x, int y)
{
	if (map_data->map_array[x][y] == '1')
	{
		return (0);
	}
	if (map_data->map_array[x][y] == 'C')
	{
		map_data->coins_collected++;
	}
	if (map_data->map_array[x][y] == 'E'
		&& map_data->coins_collected == map_data->total_coins)
	{
		map_data->count++;
		ft_printf("\nMovimientos: %i\n", map_data->count);
		exit_game(map_data);
	}
	if (map_data->map_array[x][y] == 'E'
		&& map_data->coins_collected != map_data->total_coins)
		return (0);
	map_data->map_array[map_data->player_coor_x][map_data->player_coor_y] = '0';
	map_data->map_array[x][y] = 'P';
	map_data->player_coor_x = x;
	map_data->player_coor_y = y;
	map_data->count++;
	ft_printf("\nMovimientos: %i\n", map_data->count);
	return (0);
}

int	exit_game(t_lib1 *map_data)
{
	mlx_destroy_window(map_data->mlx, map_data->win);
	free(map_data->mlx);
	exit(EXIT_SUCCESS);
}
