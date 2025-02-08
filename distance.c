#include "cube_3d.h"
#include <stdlib.h>

// TODO Use e_directions instead of cryptic numbers here
// Old versions:angle
// #define EAST 2
// #define WEST 3
// #define NORTH 4
// ...and we had true and false taking up 0 and 1...
// FIXED Constantly throws "out of bounds" errrors
// FIXME x goes below 0 (-321) because we add -1 (step) - so collision not detected in time.
// FIXME Side_dist_x and side_dist_y are doubles but we have defined them as 1 or -1.
// If side_dist_x = 1
// NOTE That *side* here represents N-S or E-W - better named axis??
// side_dist_x and y are set in find_ray
// This should be simple!
// - Jump to next map square in either x or y direction
// - Check if the map square is a wall
// FIXME The x and ys are backwards somewhere...
// NOTE That x increases going right BUT y *decreases* going up - is this assumption different?
/* void dda_alg(t_lib1 *data) */
/* { */
/* 	while (data->hit == 0) */
/* 	{ */
/* 		ft_printf("side_dist_x: %f, side_dist_y: %f\n", data->side_dist_x, data->side_dist_y); */
/* 		// Avanzar en la dirección X o Y */
/* 		if (data->side_dist_x < data->side_dist_y) */
/* 		{ */
/* 			data->side_dist_x += data->delta_x; */
/* 			data->map_x += data->direction_x;	// TODO Check that direction_x/y are correctly set! */
/* 			data->player.side = 0; */
/* 			ft_printf("DDA for x. side_dist_x now: %f, applied delta: %f\t", data->side_dist_x, data->delta_x); */
/* 			ft_printf("coords to test X:%i\tY: %i\n", data->map_x, data->map_y); */
/* 			// Determinar el lado del impacto */
/* 			/\* if (data->direction_x > 0) { *\/ */
/* 			/\*     data->player.side = EAST; // was 2 *\/ */
/* 			/\* } else { *\/ */
/* 			/\*     data->player.side = WEST; // was 3 *\/ */
/* 			/\* } *\/ */
/* 		} */
/* 		else */
/* 		{ */
/*             data->side_dist_y += data->delta_y; */
/*             data->map_y += data->direction_y; */
/*             // Determinar el lado del impacto */
/* 			data->player.side = 1; */
/* 			ft_printf("DDA for y. side_dist_y now: %f, applied delta: %f\t", data->side_dist_y, data->delta_y); */
/* 			ft_printf("coords to test X:%i\tY: %i\n", data->map_x, data->map_y); */
/*             /\* if (data->step_y > 0) { *\/ */
/*             /\*     data->player.side = NORTH; // was 0 *\/ */
/*             /\* } else { *\/ */
/*             /\*     data->player.side = SOUTH; // was 1 *\/ */
/*             /\* } *\/ */
/*         } */

/*         // Verificar límites del mapa */
/*         if (data->map_x < 0 || data->map_y < 0 ) */
/* 		{ */
/*             fprintf(stderr, "Error: Out of map bounds: x %i y %i\n", data->map_x, data->map_y); */
/* 			exit(EXIT_FAILURE); */
/*         } */

/*         // Verificar colisión con una pared */
/*         // FIXED The collision is not detected! */
/* 		ft_printf("Testing map square X: %i\tY: %i\tvalue is: %c\n", data->map_x, data->map_y, data->map_array[data->map_x][data->map_y]); */
/* //        if (data->map_array[data->map_x][data->map_y] == '1') */
/*         if (ft_strncmp(&data->map_array[data->map_x][data->map_y], "1", 1) == 0) */
/* 		{ */
/* 			ft_printf("Hit wall!\n"); */
/*             data->hit = 1; */
/*         } */
/*     } */
/* } */

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
		printf("Error finding perp_dist of ray: axis not right! %i\n", ray->axis);
		exit(EXIT_FAILURE);
	}
	printf("Ray distance calculated as: %f\n", perp_dist);
	return (perp_dist);
}

// Move a ray across gridlines (x and y) until it hits a wall (represented in map_array)
// When it finishes, we have the distances travelled for the height calculation
// TODO Fix the axis / side problem: we need to know what side of a wall is hit.
// TODO Seems we can set axis on the way *out* of the loop, not during.
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
			ray->axis = 0;	// mark impact type
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			ray->map_y += ray->direction_y;
			ray->axis = 1;
		}
		// check for hit
        if (ft_strncmp(&map_array[ray->map_x][ray->map_y], "1", 1) == 0)
			hit_wall = 1;
	}
	set_impact_side(ray);
	print_ray_properties(*ray);	// HACK debug statement
}

// direction_y = 1 means it *cannot* strike south
// direction_x = 1 means it *cannot* strike east
// direction_y = -1 means it *cannot* strike north
// direction_x = -1 means it *cannot* strike west
// axis determines N-S or E-W
void	set_impact_side(t_ray *ray)
{
	printf("Looking for impact side\n");
	print_ray_properties(*ray);
	if ((ray->direction_x == 1) && (ray->direction_y == 1))
	{
		if (ray->axis == 0)
			ray->impact_side = NORTH;
		else
			ray->impact_side = WEST;
		// North or west
	}
	if ((ray->direction_x == 1) && (ray->direction_y == -1))
	{
		if (ray->axis == 0)
			ray->impact_side = SOUTH;
		else
			ray->impact_side = WEST;
		// south or west
	}
	if ((ray->direction_x == -1) && (ray->direction_y == 1))
	{
		if (ray->axis == 0)
			ray->impact_side = NORTH;
		else
			ray->impact_side = EAST;
		// north or east
	}
	if ((ray->direction_x == -1) && (ray->direction_y == -1))
	{
		if (ray->axis == 0)
			ray->impact_side = SOUTH;
		else
			ray->impact_side = EAST;
		// south or east
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
// DONE Set new_ray.axis - initialise somehow?
// FIXED rads comes in as 0 for the first call.
// FIXED delta_x/y come in as "inf", clearly wrong. compare to _
// FIXED delta_x/y seem to change - across a screen loop they tend to 0?
// FIXED Should not be reading e.g. delta_x from data, it changes for each ray.
// FIXED? If the player angle has no offset (i.e. dead in the middle), delta_x goes off to infinity
// DONE Protect against ray_x/y values of 0 -- they wreck the 1 / ray calculation for delta x
t_ray	setup_ray(t_lib1 *data, double rads, double camera_x)
{
	t_ray	new_ray;

	printf("Setting up a ray at %f rads\n", rads);	// HACK for debugging
	// Convert given angle to a vector
	new_ray.ray_x = cos(rads);
	new_ray.ray_y = sin(rads);
	// Correction (maybe!) for the camera plane
	new_ray.ray_x = new_ray.ray_x + (camera_x * data->player.x_camera);
	new_ray.ray_y = new_ray.ray_y + (camera_x * data->player.y_camera);
	// Set starting map box based on precise player position
	new_ray.map_x = (int) data->player.x;
	new_ray.map_y = (int) data->player.y;
	if (new_ray.ray_x == 0)
		new_ray.ray_x = 0.0000000000000000000001;
	if (new_ray.ray_y == 0)
		new_ray.ray_y = 0.0000000000000000000001;
    new_ray.delta_x = fabs(1 / new_ray.ray_x);
    new_ray.delta_y = fabs(1 / new_ray.ray_y);
	new_ray.axis = -1;	// HACK is this an OK initialisation value?
	new_ray.length = 0.0;
	get_step_and_side(&new_ray, data->player);
	new_ray.wall_strike = -1.0;
//	print_ray_properties(new_ray);	// HACK for debugging
	return (new_ray);
}

// Calculates the initial steps and distances for the (DDA) algorithm,
// used to determine the intersection of a ray with a grid of pixels or cells.
// Depending on the direction of ray_x and ray_y (set in WHERE?)
// We modify step (i.e. direction)
// and calculate side_ based on delta_x (FROM WHERE)
// and the fractional part of the player's location
// (i.e. the difference between their real coords and the map square they are within).
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
