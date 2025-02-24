/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:58:09 by emedina-          #+#    #+#             */
/*   Updated: 2025/02/24 18:16:19 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// FIXME This function is never called and is incomplete
void exit_game(t_lib1 *map_data) {
    if (map_data->wall_e)
        mlx_delete_image(map_data->mlx, map_data->wall_e);
    if (map_data->wall_n)
        mlx_delete_image(map_data->mlx, map_data->wall_n);
    if (map_data->wall_s)
        mlx_delete_image(map_data->mlx, map_data->wall_s);
    if (map_data->wall_w)
        mlx_delete_image(map_data->mlx, map_data->wall_w);
    if (map_data->img)
        mlx_delete_image(map_data->mlx, map_data->img);
    if (map_data->mlx)
        mlx_terminate(map_data->mlx);
    clear_data(map_data);
    exit(EXIT_SUCCESS);
}
