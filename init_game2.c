/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:58:09 by emedina-          #+#    #+#             */
/*   Updated: 2025/03/19 14:11:21 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// FIXME This function is never called and is incomplete
int	exit_game(t_lib1 *map_data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (map_data->texture[i])
			mlx_delete_texture(map_data->texture[i++]);
	}
	free(map_data->mlx);
	exit(EXIT_SUCCESS);
}
