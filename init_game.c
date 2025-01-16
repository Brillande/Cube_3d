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
   map_data->how_many_colums += 1;
   map_data->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "cub3d with DEFINEd sizes", 1);
	if (!map_data->mlx) {
		fprintf(stderr, "Error initializing MLX\n");
		clear_data(map_data);
	}
	map_data->img = mlx_new_image(map_data->mlx, 10 * 64, 10 * 64);
	if (!map_data->img) {
		fprintf(stderr, "Error creating new image\n");
		clear_data(map_data);
	}
	draw_3d(map_data);
	select_img(map_data);
	map_data->img = make_background(map_data);
	// HACK Now lets try and overlay something to that background
	mlx_put_string(map_data->mlx, "KIULLLLLL MOOAR NAZIS!!!", 200, 150);
	mlx_image_to_window(map_data->mlx, map_data->img, 0, 0);
	// HACK Test to add textures to an already-there image.
	mlx_image_to_window(map_data->mlx, map_data->wallE, 100, 200);
	mlx_image_to_window(map_data->mlx, map_data->wallN, 200, 100);
	mlx_image_to_window(map_data->mlx, map_data->wallS, 200, 300);
	mlx_image_to_window(map_data->mlx, map_data->wallW, 300, 200);
	mlx_key_hook(map_data->mlx, &key_hook, map_data);
	mlx_loop(map_data->mlx);
	
	

}

// We need to translate textures to images / an image to put to the window
// - Load textures from texture_paths
// - Verify image loading
// - Convert to images
// - Verify conversion
// TODO select_img is not a descriptive name for the function anymore
// FIXME The textures go to the wrong places, i.e. WallE is the north image.
void select_img(t_lib1 *map_data)
{
    // Cargar las texturas
    mlx_texture_t	*wallE_texture;
    mlx_texture_t	*wallN_texture;
    mlx_texture_t	*wallS_texture;
    mlx_texture_t	*wallW_texture;

	wallE_texture = mlx_load_png(map_data->texture_paths[EAST]);
	wallN_texture = mlx_load_png(map_data->texture_paths[NORTH]);
	wallS_texture = mlx_load_png(map_data->texture_paths[SOUTH]);
	wallW_texture = mlx_load_png(map_data->texture_paths[WEST]);
    // Verificar que las texturas se cargaron correctamente
    if (!wallE_texture || !wallN_texture || !wallS_texture || !wallW_texture) {
        fprintf(stderr, "Error loading textures\n");
		clear_data(map_data);
        exit(EXIT_FAILURE);
    }

    // Convertir las texturas en imágenes
    map_data->wallE = mlx_texture_to_image(map_data->mlx, wallE_texture);
    map_data->wallN = mlx_texture_to_image(map_data->mlx, wallN_texture);
    map_data->wallS = mlx_texture_to_image(map_data->mlx, wallS_texture);
    map_data->wallW = mlx_texture_to_image(map_data->mlx, wallW_texture);

    // Verificar que las imágenes se crearon correctamente
    if (!map_data->wallE || !map_data->wallN || !map_data->wallS || !map_data->wallW) {
        fprintf(stderr, "Error converting textures to images\n");
		clear_data(map_data);
        exit(EXIT_FAILURE);
    }
}

// Prints a 2-d grid of images to the window / surface
// TODO Remove as obsolete? Does not get called from anywhere!
// NOTE Also does not appear in header file...
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
					map_data->wallE, j * 64, i * 64);
			j++;
		}
		i++;
	}
}
