#include "cube_3d.h"

// TODO Use e_directions instead of cryptic numbers here
// Old versions:
// #define EAST 2
// #define WEST 3
// #define NORTH 4
// ...and we had true and false taking up 0 and 1...
// FIXED Constantly throws "out of bounds" errrors
// FIXME x goes below 0 (-321) because we add -1 (step) - so collision not detected in time.
void dda_alg(t_lib1 *data)
{
	while (data->hit == 0)
	{
		// Avanzar en la dirección X o Y
		// NOTE Surely side_x and side_y can be equal?
		// Therefore there should be a third condition?
		if (data->side_x < data->side_y)
		{
			data->side_x += data->delta_x;
			data->map_x += data->step_x;
			// Determinar el lado del impacto
			if (data->step_x > 0)
				data->player.side = NORTH; // was 0; guessing here
			else
				data->player.side = SOUTH; // was 1; guessing here
		}
		else
		{
			data->side_y += data->delta_y;
			data->map_y += data->step_y;
			// Determinar el lado del impacto
			if (data->step_y > 0)
				data->player.side = EAST; // was 2
			else
				data->player.side = WEST; // was 3
		}
		// Verificar límites del mapa
		ft_printf("map_x: %d, map_y: %d\n", data->map_x, data->map_y);
		if (data->map_x < 0 || data->map_y < 0 )
		{
			fprintf(stderr, "Error: Out of map bounds\n");
			break;
		}
		// Verificar colisión con una pared
		// NOTE this should be map_array[][] as map is blank
		if (data->map_array[data->map_x][data->map_y] == '1') {
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
// step_x = whether the calculations go forward or back in the x_axis
// step_y = same for the y-axis
// side_x = are these intersection coords with the gridlines then?
// side_y =
// ...these values are then used in dda_alg()
void	find_ray(t_lib1 *data)
{
	if (data->ray_x < 0)
	{
		data->step_x = -1;
		data->side_x = (data->player.x - data->map_x) * data->delta_x;
	}
	else
	{
		data->step_x = 1;
		data->side_x = (data->map_x + 1.0 - data->player.x) * data->delta_x;
	}
	if (data->ray_y < 0)
	{
		data->step_y = -1;
		data->side_y = (data->player.y - data->map_y) * data->delta_y;
	}
	else
	{
		data->step_y = 1;
		data->side_y = (data->map_y + 1.0 - data->player.y) * data->delta_y;
	}
}
