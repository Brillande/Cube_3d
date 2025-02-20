/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:00:34 by emedina-          #+#    #+#             */
/*   Updated: 2025/02/20 18:11:50 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// Rotate the player's view and the camera plane
// "To rotate a vector, multiply it with the rotation matrix
// [ cos(a) -sin(a) ]
// [ sin(a)  cos(a) ]"
// player.pa is in *degrees* so needs converted wl fr
// "The direction of vector rotation is
// - anticlockwise if θ is positive (e.g. 90°),
// - and clockwise if θ is negative "
// but note.... "f a left-handed Cartesian coordinate system is used,
// with x directed to the right but y directed down, R(θ) is clockwise.
// Such non-standard orientations are rarely used in mathematics but
// are common in 2D computer graphics, which often have the origin in the
// top left corner and the y-axis down the screen or page"
// TODO Confirm that the angle correction
// is correctly calculated and applied here.
void	rotate_left(t_player *p)
{
	double	theta;

	theta = 0.05 * M_PI;
	p->pa += theta;
	if (p->pa > 2 * M_PI)
		p->pa -= 2 * M_PI;
	rotate_vector(&p->x_camera, &p->y_camera, theta);
}

void	rotate_right(t_player *p)
{
	double	theta;

	theta = -0.05 * M_PI;
	p->pa += theta;
	if (p->pa < 0)
		p->pa += 2 * M_PI;
	rotate_vector(&p->x_camera, &p->y_camera, theta);
}

// Función para mover la cámara hacia la izquierda
void	key_left(t_lib1 *data)
{
	data->player.pa -= 0.05 * M_PI;
	if (data->player.pa < 0)
		data->player.pa += 2 * M_PI;
	data->player.x_camera = cos(data->player.pa) * 5.0;
	data->player.y_camera = sin(data->player.pa) * 5.0;
}

// Función para mover la cámara hacia la derecha
void	key_right(t_lib1 *data)
{
	data->player.pa += 0.05 * M_PI;
	if (data->player.pa > 2 * M_PI)
		data->player.pa -= 2 * M_PI;
	data->player.x_camera = cos(data->player.pa) * 5.0;
	data->player.y_camera = sin(data->player.pa) * 5.0;
}

// Función para mover al jugador hacia la izquierda
void	key_a(t_lib1 *data)
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
