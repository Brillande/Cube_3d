/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:07:29 by chaikney          #+#    #+#             */
/*   Updated: 2025/03/28 16:02:13 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Clear the texture paths and the texture files
void	clear_textures(t_lib1 *tex_data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (tex_data->texture[i])
			mlx_delete_texture(tex_data->texture[i]);
		i++;
	}
}

// Free memory reserved for the map parts of t_lib
// TODO call this when the map fails validation.
void	clear_map(t_lib1 *map_data)
{
	int	i;

	i = 0;
	free(map_data->map_content);
	free(map_data->fullpath);
	if (map_data->map_array)
	{
		while (map_data->map_array[i])
			free (map_data->map_array[i++]);
		free (map_data->map_array);
	}
}

// Function handling normal program end.
// - Clear the map data we read from the file.
// - Clear the textures we loaded.
// - Terminate the MLX session
// - Exit the game.
void	exit_game(t_lib1 *game_data)
{
	clear_map(game_data);
	clear_textures(game_data);
	mlx_terminate(game_data->mlx);
	exit(EXIT_SUCCESS);
}
