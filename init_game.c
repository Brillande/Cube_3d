/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:20:40 by emedina-          #+#    #+#             */
/*   Updated: 2024/11/27 17:32:17 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// Defines a hook whereby ESCAPE quites the game
// TODO Free memory before quitting -- call exit_game?
void	key_hook(mlx_key_data_t keydata, void *info)
{
	t_lib1	*data;

	data = (t_lib1 *) info;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(data->mlx);
		exit(0);
	}
	move(data);
}

// NOTE Commented out because is duplicated in moves2.c
/* void	move(t_lib1 *data) */
/* { */
/* 	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)) */
/* 		key_left(data); */
/* 	if (mlx_is_key_down(data->mlx, MLX_KEY_A)) */
/* 		key_a(data); */
/* 	if (mlx_is_key_down(data->mlx, MLX_KEY_D)) */
/* 		key_d(data); */
/* 	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)) */
/* 		key_right(data); */
/* 	if (mlx_is_key_down(data->mlx, MLX_KEY_S)) */
/* 		key_s(data); */
/* 	if (mlx_is_key_down(data->mlx, MLX_KEY_W)) */
/* 		key_w(data); */
/* 	print_3d(data); */
/* } */

// NOTE I don't think returning the map_data is needed here.
// Entry point to the game after the map data has been read.
t_lib1	*init_game(t_lib1 *map_data)
{
	open_window(map_data);
	return (map_data);
}

// opens tyhe main game window
// Defines some key hooks (which?)
// Selects initial images
// Enters the loop
// FIXME The window sizes are based on a 2d map, we need fixed viewport size
// (Could use SCREENWIDTH and SCREENHEIGHT)
void	open_window(t_lib1 *map_data)
{
	map_data->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT,
							 "cube_3d chris branch",1);
	map_data->img = mlx_new_image(map_data->mlx, 1 * 64, 1 * 64);
	select_img(map_data);
	mlx_key_hook(map_data->win, &key_hook, map_data);
	mlx_loop(map_data->mlx);
}

// FIXME Invalid read in the texture_to_image calls below, leads to segfault
// NOTE All these seem based on 2 dimensional model, with obsolete parts
void	select_img(t_lib1 *map_data)
{
	// FIXME Cokmpilation error in the call below
//	map_data->player = mlx_texture_to_image(map_data->mlx, map_data->player);
	map_data->wall = mlx_texture_to_image(map_data->mlx, map_data->wall);
	map_data->ground = mlx_texture_to_image(map_data->mlx, map_data->ground);
	map_data->coin = mlx_texture_to_image(map_data->mlx, map_data->coin);
	map_data->exit = mlx_texture_to_image(map_data->mlx, map_data->exit);
}

int	print_img(t_lib1 *map_data)
{
	print_img1(map_data);
	print_img2(map_data);
	print_img3(map_data);
	return (0);
}

// Prints a 2-d grid of images
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
				mlx_image_to_window(map_data->mlx,
					map_data->ground, j * 64, i * 64);
			if (map_data->map_array[i][j] == '1')
				mlx_image_to_window(map_data->mlx,
					map_data->wall, j * 64, i * 64);
			j++;
		}
		i++;
	}
}

