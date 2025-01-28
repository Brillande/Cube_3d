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
void dda_alg(t_lib1 *data)
{
	while (data->hit == 0)
	{
		printf("side_dist_x: %f, side_dist_y: %f\n", data->side_dist_x, data->side_dist_y);
		// Avanzar en la dirección X o Y
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += data->delta_x;
			data->map_x += data->direction_x;	// TODO Check that direction_x/y are correctly set!
			data->player.side = 0;
			printf("DDA for x. side_dist_x now: %f, applied delta: %f\t", data->side_dist_x, data->delta_x);
			printf("coords to test X:%i\tY: %i\n", data->map_x, data->map_y);
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
			printf("DDA for y. side_dist_y now: %f, applied delta: %f\t", data->side_dist_y, data->delta_y);
			printf("coords to test X:%i\tY: %i\n", data->map_x, data->map_y);
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
