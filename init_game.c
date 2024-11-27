/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:20:40 by emedina-          #+#    #+#             */
/*   Updated: 2023/09/27 22:16:05 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_lib1	*init_game(t_lib1 *map_data)
{
	open_window(map_data);
	return (map_data);
}

void	open_window(t_lib1 *map_data)
{
	map_data->how_many_colums += 1;
	map_data->mlx = mlx_init();
	map_data->win = mlx_new_window(map_data->mlx, map_data->how_many_colums
			* 64, map_data->how_many_lines * 64, "so_long emedina-");
	map_data->img = mlx_new_image(map_data->mlx, 1 * 64, 1 * 64);
	select_img(map_data);
	mlx_loop_hook(map_data->mlx, print_img, map_data);
	mlx_key_hook(map_data->win, key_hook, map_data);
	mlx_hook(map_data->win, 17, 0, exit_game, map_data);
	mlx_loop(map_data->mlx);
}

void	select_img(t_lib1 *map_data)
{
	map_data->player = mlx_xpm_file_to_image(map_data->mlx, "img/player.xpm",
			&map_data->width, &map_data->heigth);
	map_data->wall = mlx_xpm_file_to_image(map_data->mlx, "img/wall.xpm",
			&map_data->width, &map_data->heigth);
	map_data->ground = mlx_xpm_file_to_image(map_data->mlx, "img/ground.xpm",
			&map_data->width, &map_data->heigth);
	map_data->coin = mlx_xpm_file_to_image(map_data->mlx, "img/coin.xpm",
			&map_data->width, &map_data->heigth);
	map_data->exit = mlx_xpm_file_to_image(map_data->mlx, "img/exit.xpm",
			&map_data->width, &map_data->heigth);
}

int	print_img(t_lib1 *map_data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	print_img1(map_data);
	print_img2(map_data);
	print_img3(map_data);
	return (0);
}

void	print_img1(t_lib1 *map_data)
{
	int	i;
	int	j;

	i = 0;
	while (map_data->map_array[i])
	{
		j = 0;
		while (map_data->map_array[i][j] != '\0')
		{
			if (map_data->map_array[i][j] != '1')
				mlx_put_image_to_window(map_data->mlx, map_data->win,
					map_data->ground, j * 64, i * 64);
			if (map_data->map_array[i][j] == '1')
				mlx_put_image_to_window(map_data->mlx, map_data->win,
					map_data->wall, j * 64, i * 64);
			j++;
		}
		i++;
	}
}
