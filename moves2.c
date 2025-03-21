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

// These movement functions move the *player* not just her viewpoint.

// Función para verificar si el movimiento es válido
// FIXME len_cols and len_rows are not populated - map is not a rectangle
// (although we need a way to make sure the map_array check is in bounds)
// TODO Confirm that this receives the correct player location to check against
static int	check_move(int x, int y, t_lib1 *data)
{
	if (x < 0 || y < 0 || x >= data->len_cols || y >= data->len_rows)
	{
		if (data->map_array[x][y] == '1')
			return (false);
		return (true);
	}
	return (false);
}

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

// Función para mover al jugador hacia la derecha
// "Strafe" to the right. Position changes, view angle stays the same.
void	move_right(t_lib1 *data)
{
	double	move_x;
	double	move_y;

	move_x = data->player.x + data->player.game_speed
		* cos(data->player.pa - 0.5 * M_PI);
	move_y = data->player.y + data->player.game_speed
		* sin(data->player.pa - 0.5 * M_PI);
	if (check_move(move_x, move_y, data))
	{
		data->player.y = move_y;
		data->player.x = move_x;
	}
}

// Función para mover al jugador hacia atrás
// Move player backwards, if not into a wall
void	move_backward(t_lib1 *data)
{
	double	move_x;
	double	move_y;

	move_x = data->player.x - data->player.game_speed * cos(data->player.pa);
	move_y = data->player.y - data->player.game_speed * sin(data->player.pa);
	if (check_move(move_x, move_y, data))
	{
		data->player.x = move_x;
		data->player.y = move_y;
	}
}

// Función para mover al jugador hacia la izquierda
// "Strafe" to the left. Position changes, view angle stays the same.
void	move_left(t_lib1 *data)
{
	double	move_x;
	double	move_y;

	move_x = data->player.x + data->player.game_speed
		* cos(data->player.pa + 0.5 * M_PI);
	move_y = data->player.y + data->player.game_speed
		* sin(data->player.pa + 0.5 * M_PI);
	if (check_move(move_x, move_y, data))
	{
		data->player.y = move_y;
		data->player.x = move_x;
	}
}
