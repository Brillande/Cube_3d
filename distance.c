/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:35:44 by emedina-          #+#    #+#             */
/*   Updated: 2025/03/19 12:46:59 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// NOTE Compared to find_distance, this does less.
// ...no angle correction, no setting of wall_x.
// (wall_x aka wall_strike is set now in find_strike_point())
double	find_distance_ray(t_ray *ray)
{
	double	perp_dist;

	if (ray->axis == 0)
		perp_dist = ray->side_dist_x - ray->delta_x;
	else if (ray->axis == 1)
		perp_dist = ray->side_dist_y - ray->delta_y;
	else
	{
		printf("Error finding perp_dist of ray: axis not right! %i\n",
			ray->axis);
		exit(EXIT_FAILURE);
	}
	return (perp_dist);
}

// - Move a ray across gridlines (x and y) until it hits a wall
// - As we go we increment side_dist_x/y,
// -- measuring distance travelled in each axis
// - When loop finishes, we have distances travelled for the height calculation
// NOTE Seemed possible to set axis on the way *out* of the loop, not during...
// ....but that did not work?
// - side_dist_x/y: ...?
// - delta_x/y: .....?
// - axis: Are we going N-S (0, more up than down) or E-W (1, more sideways)
void	dda_for_one_ray(t_ray *ray, char **map_array)
{
	int	hit_wall;

	hit_wall = 0;
	while (hit_wall == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_x;
			ray->map_x += ray->direction_x;
			ray->axis = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			ray->map_y += ray->direction_y;
			ray->axis = 1;
		}
		// FIXME Segfault here with map8_biggest.cub. Failed for this.
		if (ft_strncmp(&map_array[ray->map_x][ray->map_y], "1", 1) == 0)
			hit_wall = 1;
	}
	set_impact_side(ray);
}

// direction_y = 1 means it *cannot* strike south
// direction_x = 1 means it *cannot* strike east
// direction_y = -1 means it *cannot* strike north
// direction_x = -1 means it *cannot* strike west
// axis determines N-S or E-W
void	set_impact_side(t_ray *ray)
{
	if (ray->axis == 0)
	{
		if (ray->direction_x > 0)
			ray->impact_side = SOUTH;
		else
			ray->impact_side = NORTH;
	}
	else
	{
		if (ray->direction_y > 0)
			ray->impact_side = WEST;
		else
			ray->impact_side = EAST;
	}
}

// This needs the coords from the player and for the ray
// camera_x: normalised x-coordinate in camera space
// Returns a set-up ray to be used in DDA
// Which in t_ray change and which remain the same?
// map_x and map_y are the same for all rays (player start point)
// axis, different per ray but only 2 options for any player orientation
// direction_x/y are the same.
// ray_x and ray_y vary a little for each as we scan across
// side_dist_x/y and delta_x/y needed once per ray
// / ray calculation for delta x
t_ray	setup_ray(t_lib1 *data, double rads, double camera_x)
{
	t_ray	new_ray;

	new_ray.ray_x = cos(rads);
	new_ray.ray_y = sin(rads);
	new_ray.ray_x = new_ray.ray_x + (camera_x * data->player.x_camera);
	new_ray.ray_y = new_ray.ray_y + (camera_x * data->player.y_camera);
	new_ray.map_x = (int) data->player.x;
	new_ray.map_y = (int) data->player.y;
	if (new_ray.ray_x == 0)
		new_ray.ray_x = 0.0000000000000000000001;
	if (new_ray.ray_y == 0)
		new_ray.ray_y = 0.0000000000000000000001;
	new_ray.delta_x = fabs(1 / new_ray.ray_x);
	new_ray.delta_y = fabs(1 / new_ray.ray_y);
	new_ray.axis = -1;
	new_ray.length = 0.0;
	get_step_and_side(&new_ray, data->player);
	new_ray.wall_strike = -1.0;
	return (new_ray);
}

// Calculates the initial steps and distances for the (DDA) algorithm,
// used to determine the intersection of a ray with a grid of pixels or cells.
// Depending on the direction of ray_x and ray_y (set in WHERE?)
// We modify step (i.e. direction)
// and calculate side_ based on delta_x (FROM WHERE)
// and the fractional part of the player's location
// (i.e. the difference between their real coords 
//and the map square they are within).
// ------------------------------
// At the end of this function we have updated:
// direction_x = whether the calculations go forward or back in the x_axis
// direction_y = same for the y-axis
// side_dist_x = are these intersection coords with the gridlines then?
// side_dist_y =
// ...these values are then used in dda_alg()
// calculates STEP (i.e. direction in each)
// and SIDE DISTANCEs (i.e. distance to next crossing)
// TODO Try and reverse y as the array goes x > and y down
void	get_step_and_side(t_ray *ray, t_player player)
{
	if (ray->ray_x < 0)
	{
		ray->direction_x = -1;
		ray->side_dist_x = (player.x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->direction_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player.x) * ray->delta_x;
	}
	if (ray->ray_y < 0)
	{
		ray->direction_y = -1;
		ray->side_dist_y = (player.y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->direction_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player.y) * ray->delta_y;
	}
}
