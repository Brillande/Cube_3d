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

#include "cub3D.h"

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

// This changes the player's view, (and camera plane) not her position.
void	rotate_right(t_player *p)
{
	double	theta;

	theta = -0.05 * M_PI;
	p->pa += theta;
	if (p->pa < 0)
		p->pa += 2 * M_PI;
	rotate_vector(&p->x_camera, &p->y_camera, theta);
}
