/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:22:32 by chaikney          #+#    #+#             */
/*   Updated: 2025/03/19 12:44:35 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Dibuja la vista 3D del entorno
// Loop over each ray to be calculated for the view window
// ...what does 0.3 represent in degrees?
// a - the pixel coordinate (x) where the ray will be drawn (in walls)
void	draw_3d(t_lib1 *data)
{
	mlx_texture_t	*selected_texture;
	mlx_image_t		*new_img;
	t_ray			ray;
	int				view_col;

	view_col = 0;
	new_img = mlx_new_image(data->mlx, SCREENWIDTH, SCREENHEIGHT);
	while (view_col < SCREENWIDTH)
	{
		ray = setup_ray(data, data->player.pa, view_col);
		dda_for_one_ray(&ray, data->map_array);
		ray.length = find_distance_ray(&ray);
		ray.wall_strike = find_strike_point(&ray,
				data->player.x, data->player.y);
		selected_texture = data->texture[ray.impact_side];
		setup_wall_drawing(selected_texture, &ray);
		draw_textured_walls(data, new_img, selected_texture, &ray);
		view_col++;
	}
	new_img->enabled = true;
	mlx_delete_image(data->mlx, data->img);
	data->img = new_img;
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

// Return the x-coordinate on the camera plane for the ray in screen_col
// Result is normalised to a range of -1 (left) to 1 (right edge)
double	get_camera_x(int screen_col)
{
	double	camera_x;

	camera_x = (2 * screen_col) / (double) SCREENWIDTH - 1;
	return (camera_x);
}

// Find the point of the wall where the ray struck it.
// NB The point is normalised to a 0-1 range
// Formula based on this:
//   if (side == 0) wallX = posY + perpWallDist * rayDirY;
//      else           wallX = posX + perpWallDist * rayDirX;
//      wallX -= floor((wallX));
double	find_strike_point(t_ray *r, double x_origin, double y_origin)
{
	double	hit_me;

	if (r->axis == 0)
	{
		hit_me = y_origin + r->length * r->ray_y;
	}
	else
	{
		hit_me = x_origin + r->length * r->ray_x;
	}
	hit_me -= floorf(hit_me);
	if ((r->impact_side == EAST || r->impact_side == SOUTH))
		hit_me = 1 - hit_me;
	return (hit_me);
}
