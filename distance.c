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
void dda_alg(t_lib1 *data)
{
	while (data->hit == 0)
	{
		ft_printf("side_dist_x: %f, side_dist_y: %f\n", data->side_dist_x, data->side_dist_y);
		// Avanzar en la dirección X o Y
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += data->delta_x;
			data->map_x += data->direction_x;	// TODO Check that direction_x/y are correctly set!
			data->player.side = 0;
			ft_printf("DDA for x. side_dist_x now: %f, applied delta: %f\t", data->side_dist_x, data->delta_x);
			ft_printf("coords to test X:%i\tY: %i\n", data->map_x, data->map_y);
			// Determinar el lado del impacto
			/* if (data->direction_x > 0) { */
			/*     data->player.side = EAST; // was 2 */
			/* } else { */
			/*     data->player.side = WEST; // was 3 */
			/* } */
		}
		else
		{
            data->side_dist_y += data->delta_y;
            data->map_y += data->direction_y;
            // Determinar el lado del impacto
			data->player.side = 1;
			ft_printf("DDA for y. side_dist_y now: %f, applied delta: %f\t", data->side_dist_y, data->delta_y);
			ft_printf("coords to test X:%i\tY: %i\n", data->map_x, data->map_y);
            /* if (data->step_y > 0) { */
            /*     data->player.side = NORTH; // was 0 */
            /* } else { */
            /*     data->player.side = SOUTH; // was 1 */
            /* } */
        }

        // Verificar límites del mapa
        if (data->map_x < 0 || data->map_y < 0 )
		{
            fprintf(stderr, "Error: Out of map bounds: x %i y %i\n", data->map_x, data->map_y);
			exit(EXIT_FAILURE);
        }

        // Verificar colisión con una pared
        // FIXED The collision is not detected!
		ft_printf("Testing map square X: %i\tY: %i\tvalue is: %c\n", data->map_x, data->map_y, data->map_array[data->map_x][data->map_y]);
//        if (data->map_array[data->map_x][data->map_y] == '1')
        if (ft_strncmp(&data->map_array[data->map_x][data->map_y], "1", 1) == 0)
		{
			ft_printf("Hit wall!\n");
            data->hit = 1;
        }
    }
}

// Move a ray across gridlines (x and y) until it hits a wall (represented in map_array)
// When it finishes, we have the distances travelled for the height calculation
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
			ray->side_dist_y += ray->delta_x;
			ray->map_y += ray->direction_y;
			ray->axis = 1;
		}
		// check for hit
        if (ft_strncmp(&map_array[ray->map_x][ray->map_y], "1", 1) == 0)
			hit_wall = 1;
	}
}

// LIke get_step_and_side but returns a set-up ray to be used in DDA
// Which in t_ray change and which remain the same?
// map_x and map_y are the same for all rays (player start point)
// axis, different per ray but only 2 options for any player orientation
// direction_x/y are the same.
// ray_x and ray_y vary a little for each as we scan across
// side_dist_x/y and delta_x/y needed once per ray
// This needs the coords from the player and for the ray
// TODO Set new_ray.axis - initialise somehow?
// FIXME rads comes in as 0 for the first call.
t_ray	setup_ray(t_lib1 *data, double rads)
{
	t_ray	new_ray;

	ft_printf("Setting up a ray at %f rads\n", rads);
	new_ray.ray_x = cos(rads);
	new_ray.ray_y = sin(rads);
	new_ray.map_x = data->map_x;
	new_ray.map_y = data->map_y;
    new_ray.delta_x = fabs(1 / data->ray_x);
    new_ray.delta_y = fabs(1 / data->ray_y);
	if (new_ray.ray_x < 0)
	{
		new_ray.direction_x = -1;
		new_ray.side_dist_x = (data->player.x - new_ray.map_x) * data->delta_x;
	}
	else
	{
		new_ray.direction_x = 1;
		new_ray.side_dist_x = (new_ray.map_x + 1.0 - data->player.x) * data->delta_x;
	}
	if (new_ray.ray_y < 0)
	{
		new_ray.direction_y = -1;
		new_ray.side_dist_y = (data->player.y - new_ray.map_y) * data->delta_y;
	}
	else
	{
		new_ray.direction_y = 1;
		new_ray.side_dist_y = (new_ray.map_y + 1.0 - data->player.y) * data->delta_y;
	}
	print_ray_properties(new_ray);
	return (new_ray);
}

// What does this do? Where were delta_x and delta_y calculated?
// calculates the initial steps and distances for the (DDA) algorithm,
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
// ray_x/y are a vector representation calculated in len_find from the angle passed into the loop
// NOTE All the values in this could be in t_ray instead...
// TODO Try and reverse y as the array goes x > and y down
void	get_step_and_side(t_lib1 *data)
{
	if (data->ray_x < 0)
	{
		data->direction_x = -1;
		data->side_dist_x = (data->player.x - data->map_x) * data->delta_x;
		// HACK This is the initial position,. only to test a static image
//		data->side_dist_x = (data->player_coor_x - data->map_x) * data->delta_x;
	}
	else
	{
		data->direction_x = 1;
//		data->side_dist_x = (data->map_x + 1.0 - data->player_coor_x) * data->delta_x;
		data->side_dist_x = (data->map_x + 1.0 - data->player.x) * data->delta_x;
	}
	if (data->ray_y < 0)
	{
		data->direction_y = -1;
		//data->side_dist_y = (data->player_coor_y - data->map_y) * data->delta_y;
		data->side_dist_y = (data->player.y - data->map_y) * data->delta_y;
	}
	else
	{
		data->direction_y = 1;
//		data->side_dist_y = (data->map_y + 1.0 - data->player_coor_y) * data->delta_y;
		data->side_dist_y = (data->map_y + 1.0 - data->player.y) * data->delta_y;
	}
}
