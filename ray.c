/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:22:32 by chaikney          #+#    #+#             */
/*   Updated: 2025/02/20 20:28:31 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// Return the wall face that a ray of angle x intersects with
// TODO Implement and test get_wall_face
// Add protection against zero and negative numbers
// TODO How to handle numbers that go above 360 afer adding 45?
enum e_direction	get_wall_face(double x)
{
	if ((x < 0) || (x >= 360))
		return (-1);
	x += 45.0;
	if (x == 0)
		return (NORTH);
	return ((x / 90.0));
}

// Dibuja la vista 3D del entorno
// Loop over each ray to be calculated for the view window
// NOTE Unclear why these values. They give a range of 1000 steps.
// The ray calculation should be based on the width of the window
// and some other parameter, not magic numbers.
// i.e. SCREENWIDTH is the number of rays / x-columns we need to calculate.
// TODO Use FIELDOFVIEW to calculate the angle_offset
// ...what does 0.3 represent in degrees?
// a - the pixel coordinate (x) where the ray will be drawn (in walls)
// FIXME There is a mix of DEGREES and RADIANS in use here, it is confusing
// FIXME player.pa and radians_offset are both 0 when we call a ray...
// ...which is then not set up correctly.
// DONE Identify texture to be used. in set_impact_side()
void	draw_3d(t_lib1 *data)
{
	int				view_col;
	mlx_texture_t	*selected_texture;
	mlx_image_t		*new_img;
	t_ray			test_ray;
	double			camera_x;

	view_col = 0;
	new_img = mlx_new_image(data->mlx, SCREENWIDTH, SCREENHEIGHT);
	while (view_col < SCREENWIDTH)
	{
		camera_x = get_camera_x((view_col));
		test_ray = setup_ray(data, data->player.pa, camera_x);
		dda_for_one_ray(&test_ray, data->map_array);
		test_ray.length = find_distance_ray(&test_ray);
		test_ray.wall_strike = find_strike_point(&test_ray,
				data->player.x, data->player.y);
		selected_texture = data->texture[test_ray.impact_side];
		textured_walls(data, view_col, new_img, test_ray.wall_strike,
			selected_texture, test_ray.length);
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
	if ((hit_me > 1) || (hit_me < 0))
		printf("***** Strike point calculation is bad! ");
	return (hit_me);
}
