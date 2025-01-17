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
t_lib1	*init_game(t_lib1 *map_data)
{
	open_window(map_data);
	return (map_data);
}

// opens the main game window
// Defines some key hooks (which?)
// Selects initial images
// Enters the loop
// FIXED The window sizes are based on a 2d map, we need fixed viewport size
// (Could use SCREENWIDTH and SCREENHEIGHT)
void	open_window(t_lib1 *map_data)
{
   map_data->how_many_colums += 1;	// TODO Consider removing this; where is it used?
   map_data->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "cub3d with DEFINEd sizes", 1);
	if (!map_data->mlx) {
		fprintf(stderr, "Error initializing MLX\n");
		clear_data(map_data);
	}
	// FIXME Should this not be WIDTH / HEIGHT?
	map_data->img = mlx_new_image(map_data->mlx, 10 * 64, 10 * 64);
	if (!map_data->img) {
		fprintf(stderr, "Error creating new image\n");
		clear_data(map_data);
	}
	draw_3d(map_data);
	load_wall_textures(map_data);
	map_data->img = make_background(map_data);
	mlx_image_to_window(map_data->mlx, map_data->img, 0, 0);
	mlx_key_hook(map_data->mlx, &key_hook, map_data);
	// FIXME Segfault caused here, gen protection fault
	mlx_loop(map_data->mlx);
}

// Translate textures to images / an image to put to the window
// - Load textures from texture_paths
// - Verify image loading
// - Convert to images
// - Verify conversion
// TODO Understand whether we need *images* at this stage or are textures enough?
// NOTE Later we refer to parts of these to get hold of the things-we-need-draw
// NOTE We do *not* need to convert these to images!
// Images are disllpayed directly on the screen,
// textures hold the key info that we will use to find the wall colours
// https://github.com/codam-coding-college/MLX42/wiki/Textures
// TODO Convert the multiple variables to an array like texture[i]
void load_wall_textures(t_lib1 *map_data)
{
	int	i;

	i = 0;
	while (i <= 3)
	{
		map_data->texture[i] = mlx_load_png(map_data->texture_paths[i]);
		i++;
	}
	while (i >= 0)
	{
		if (!map_data->texture[i])
		{
			fprintf(stderr, "Error loading textures\n");
			clear_data(map_data);
			exit(EXIT_FAILURE);
		}
		i--;
    }
}
