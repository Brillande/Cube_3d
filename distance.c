#include "cube_3d.h"

// TODO Use e_directions instead of cryptic numbers here
void dda_alg(t_lib1 *data, t_lib1 *ca)
{
	(void) ca;
    while (data->hit == 0) {
        // Avanzar en la dirección X o Y
        if (data->side_x < data->side_y) {
            data->side_x += data->delta_x;
            data->map_x += data->step_x;
            // Determinar el lado del impacto
            if (data->step_x > 0) {
                data->player.side = 0;
            } else {
                data->player.side = 1;
            }
        } else {
            data->side_y += data->delta_y;
            data->map_y += data->step_y;
            // Determinar el lado del impacto
            if (data->step_y > 0) {
                data->player.side = 2;
            } else {
                data->player.side = 3;
            }
        }

        // Verificar límites del mapa
        ft_printf("map_x: %d, map_y: %d\n", data->map_x, data->map_y);
        if (data->map_x < 0 || data->map_x >= data->len_cols || data->map_y < 0 || data->map_y >= data->len_rows) {
            fprintf(stderr, "Error: Out of map bounds\n");
            break;
        }

        // Verificar colisión con una pared
        // NOTE this should be map_array[][] as map is blank
        if (data->map_array[data->map_y][data->map_x] == '1') {
            data->hit = 1;
        }
    }
}

// What does this do?
void	find_ray(t_lib1 *cal, t_lib1 *data)
{
	(void) cal;
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