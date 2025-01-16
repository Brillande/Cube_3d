#include "cube_3d.h"

// TODO Use e_directions instead of cryptic numbers here
void dda_alg(t_lib1 *data, t_lib1 *ca) {
    while (ca->hit == 0) {
        // Avanzar en la dirección X o Y
        if (ca->side_x < ca->side_y) {
            ca->side_x += ca->delta_x;
            ca->map_x += ca->step_x;
            // Determinar el lado del impacto
            if (ca->step_x > 0) {
                data->player.side = 0;
            } else {
                data->player.side = 1;
            }
        } else {
            ca->side_y += ca->delta_y;
            ca->map_y += ca->step_y;
            // Determinar el lado del impacto
            if (ca->step_y > 0) {
                data->player.side = 2;
            } else {
                data->player.side = 3;
            }
        }

        // Verificar límites del mapa
        ft_printf("map_x: %d, map_y: %d\n", ca->map_x, ca->map_y);
        if (ca->map_x < 0 || ca->map_x >= data->len_cols || ca->map_y < 0 || ca->map_y >= data->len_rows) {
            fprintf(stderr, "Error: Out of map bounds\n");
            break;
        }

        // Verificar colisión con una pared
        // NOTE this should be map_array[][] as map is blank
        if (data->map_array[ca->map_y][ca->map_x] == '1') {
            ca->hit = 1;
        }
    }
}

// What does this do?
void	find_ray(t_lib1 *cal, t_lib1 *data)
{
	if (cal->ray_x < 0)
	{
		cal->step_x = -1;
		cal->side_x = (data->player.x - cal->map_x) * cal->delta_x;
	}
	else
	{
		cal->step_x = 1;
		cal->side_x = (cal->map_x + 1.0 - data->player.x) * cal->delta_x;
	}
	if (cal->ray_y < 0)
	{
		cal->step_y = -1;
		cal->side_y = (data->player.y - cal->map_y) * cal->delta_y;
	}
	else
	{
		cal->step_y = 1;
		cal->side_y = (cal->map_y + 1.0 - data->player.y) * cal->delta_y;
	}
}