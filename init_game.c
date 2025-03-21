/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:20:40 by emedina-          #+#    #+#             */
/*   Updated: 2025/02/26 19:09:26 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Defines a hook whereby ESCAPE quites the game
// Also defines the move keys
// TODO Free memory before quitting -- call exit_game? Where is the t_lib?
// FIXME There are 2 other functions that do the same as this. Highlander mode!
void	key_hooks(mlx_key_data_t keydata, void *info)
{
	t_lib1	*data;

	data = (t_lib1 *) info;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(data->mlx);
		exit(0);
	}
	movement_hooks(data);
}

// Create and return the background of floor / ceiling colours
// Define an image to use
// Set the pixels in the top half to rgb_ceiling
// and those in the bottom to rgb_floor
// (Later, experiment with fading to black to simulate darkness / distance)
mlx_image_t	*make_background(t_lib1 *map_data)
{
	int			x;
	int			y;
	mlx_image_t	*bg;

	x = 0;
	y = 0;
	bg = mlx_new_image(map_data->mlx, SCREENWIDTH, SCREENHEIGHT);
	while (x < (SCREENWIDTH))
	{
		while (y < (SCREENHEIGHT / 2))
			mlx_put_pixel(bg, x, y++, map_data->rgb_ceiling);
		x++;
		y = 0;
	}
	x = 0;
	y = (SCREENHEIGHT / 2);
	while (x < SCREENWIDTH)
	{
		while (y < SCREENHEIGHT)
			mlx_put_pixel(bg, x, y++, map_data->rgb_floor);
		x++;
		y = (SCREENHEIGHT / 2);
	}
	bg->enabled = true;
	return (bg);
}

// NOTE I don't think returning the map_data is needed here.
// Entry point to the game after the map data has been read.
void	init_game(t_lib1 *map_data)
{
	open_window(map_data);
}

// opens the main game window
// Defines some key hooks (which?)
// Loads the wall textures
// Generates the background
// Draws the first wall_s
// Enters the loop
// FIXED The window sizes are based on a 2d map, we need fixed viewport size
// (Could use SCREENWIDTH and SCREENHEIGHT)
void	open_window(t_lib1 *map_data)
{
	map_data->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT,
			"cub3d with DEFINEd sizes", 1);
	if (!map_data->mlx)
	{
		fprintf(stderr, "Error initializing MLX\n");
		clear_data(map_data);
	}
	map_data->img = make_background(map_data);
	draw_3d(map_data);
	mlx_key_hook(map_data->mlx, &key_hooks, map_data);
	mlx_loop(map_data->mlx);
}
