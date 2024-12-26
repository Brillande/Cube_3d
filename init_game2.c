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
