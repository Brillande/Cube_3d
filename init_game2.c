/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:58:09 by emedina-          #+#    #+#             */
/*   Updated: 2024/11/27 17:37:44 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// FIXME Prints images of coin / exit that are not part of this game!
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
				mlx_image_to_window(map_data->mlx,
					map_data->coin, (j * 64) + 16, (i * 64) + 16);
			if (map_data->map_array[i][j] == 'E')
				mlx_image_to_window(map_data->mlx,
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
	// FIXME expects mlx_image_t but passes t_player
//	mlx_image_to_window(map_data->mlx, map_data->player, (j * 64) + 14, (i * 64) - 4);
}

// FIXME "multiple definition of key_hook"
/* void	key_hook(mlx_key_data_t keydata, void *info) */
/* { */
/* 	t_lib1	*data; */

/* 	data = (t_lib1 *) info; */
/* 	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS) */
/* 	{ */
/* 		mlx_close_window(data->mlx); */
/* 		exit(0); */
/* 	} */
/* 	move(data); */
/* } */


// FIXME This function is never called and is incomplete
int	exit_game(t_lib1 *map_data)
{
	free(map_data->mlx);
	exit(EXIT_SUCCESS);
}
