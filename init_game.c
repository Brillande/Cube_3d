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

#include "cube_3d.h"

// Defines a hook whereby ESCAPE quites the game
// TODO Free memory before quitting -- call exit_game? Where is the t_lib?
// TODO Add other key hooks here? How does it relate to moves.c?
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

// Create and return the background of floor / ceiling colours
// Define an image to use
// Set the pixels in the top half to rgb_ceiling
// and those in the bottom to rgb_floor
// (Later, experiment with fading to black to simulate darkness / distance)
// FIXED Find the correct location for to write to
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
	load_wall_textures(map_data);
	map_data->img = make_background(map_data);
	draw_3d(map_data);
	mlx_key_hook(map_data->mlx, &key_hook, map_data);
	mlx_loop(map_data->mlx);
}

// Translate textures to images / an image to put to the window
// - Load textures from texture_paths
// - Verify image loading
// - Convert to images
// - Verify conversion
// TODO Understand whether we need *
//images* at this stage or are textures enough?
// NOTE Later we refer to parts of these to get hold of the things-we-need-draw
// But right now I don't know how that works. Images or textures??
// TODO Convert the multiple variables to an array like texture[i]
void	load_wall_textures(t_lib1 *map_data)
{
	mlx_texture_t	*wall_e_texture;
	mlx_texture_t	*wall_n_texture;
	mlx_texture_t	*wall_s_texture;
	mlx_texture_t	*wall_w_texture;

	wall_e_texture = mlx_load_png(map_data->texture_paths[EAST]);
	wall_n_texture = mlx_load_png(map_data->texture_paths[NORTH]);
	wall_s_texture = mlx_load_png(map_data->texture_paths[SOUTH]);
	wall_w_texture = mlx_load_png(map_data->texture_paths[WEST]);
	if (!wall_e_texture || !wall_n_texture
		|| !wall_s_texture || !wall_w_texture)
	{
		fprintf(stderr, "Error loading textures\n");
		clear_data(map_data);
		exit(EXIT_FAILURE);
	}
	map_data->wall_e = mlx_texture_to_image(map_data->mlx, wall_e_texture);
	map_data->wall_n = mlx_texture_to_image(map_data->mlx, wall_n_texture);
	map_data->wall_s = mlx_texture_to_image(map_data->mlx, wall_s_texture);
	map_data->wall_w = mlx_texture_to_image(map_data->mlx, wall_w_texture);
	mlx_delete_texture(wall_e_texture);
	mlx_delete_texture(wall_n_texture);
	mlx_delete_texture(wall_s_texture);
	mlx_delete_texture(wall_w_texture);
}
