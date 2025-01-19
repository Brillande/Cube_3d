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
				data->player.side = 0;
			else
				data->player.side = 1;
		}
		else
		{
			data->side_y += data->delta_y;
			data->map_y += data->step_y;
			// Determinar el lado del impacto
			if (data->step_y > 0)
				data->player.side = 2;
			else
				data->player.side = 3;
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

// What does this do?
// NOTE ray_x is set in......
// step_x = x direction
// side_x = a double meaning what? ? Direction? This is a mess.
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
