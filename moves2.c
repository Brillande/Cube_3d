/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:57:33 by emedina-          #+#    #+#             */
/*   Updated: 2025/02/26 18:42:30 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Función para mover al jugador hacia adelante
// Move player forward, if not into a wall.
void	move_forward(t_lib1 *data)
{
	double	move_x;
	double	move_y;

	move_x = data->player.x + data->player.game_speed * cos(data->player.pa);
	move_y = data->player.y + data->player.game_speed * sin(data->player.pa);
	if (check_move(move_x, move_y, data))
	{
		data->player.x = move_x;
		data->player.y = move_y;
	}
}

// Función para verificar si el movimiento es válido
// FIXME len_cols and len_rows are not populated - map is not a rectangle
// (although we need a way to make sure the map_array check is in bounds)
// TODO Confirm that this receives the correct player location to check against
int	check_move(int x, int y, t_lib1 *data)
{
	if (x < 0 || y < 0 || x >= data->len_cols || y >= data->len_rows)
	{
		if (data->map_array[x][y] == '1')
			return (false);
		return (true);
	}
	return (false);
}

// Función para manejar el movimiento del jugador
// Define the movement keys.
// TODO do we need draw_3d here or should it be elsewhere in the loop?
// ...or if nothing has changed, why even call it?
void	movement_hooks(t_lib1 *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_left(&data->player);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_left(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_right(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_right(&data->player);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_backward(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_forward(data);
	draw_3d(data);
}
