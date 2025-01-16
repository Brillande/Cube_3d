#include "cube_3d.h"

// https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)
// - calculate the smaller of dy or dx for a unit increment of the other.
// - Sample a line at unit intervals in one coordinate;
// "corresponding integer values nearest the line path are determined for the other coordinate."
// Varies according if we have -ve or +ve slope
// "In its simplest implementation for linear cases such as lines, the algorithm
// interpolates values in interval by computing
// for each xi the equations xi = xi−1 + 1, yi = yi−1 + m,
// where m is the slope of the line."
// TODO Use e_directions instead of cryptic numbers here
// data - the main t_lib1 struct.
// TODO ca - another t_lib1, reasons to be clarified
// FIXME map_y keeps going to -1 and causing a segfault.
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
        // HACK Commented out; prevents a segfault though.
        ft_printf("map_x: %d, map_y: %d\n", ca->map_x, ca->map_y);
//        if (ca->map_x < 0 || ca->map_x >= data->len_cols || ca->map_y < 0 || ca->map_y >= data->len_rows) {
        if (ca->map_x < 0 || ca->map_y < 0)
		{
           fprintf(stderr, "Error: Out of map bounds\n");
            break;
       }

        // Verificar colisión con una pared
        // FIXME Should this be map_array[][]? map is blank
        // FIXME Segfault from going out of bounds here (map_y = -1)
        // TODO Explain why the array index is [y][x] not [x][y] here
        if (data->map[ca->map_y] [ca->map_x] == '1')
           ca->hit = 1;
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

// NOTE Unclear what these constants are.
// FIXME We have print_3d and draw_3d functions. Why?
void	print_3d(t_lib1 *data)
{
	int		a;
	double	i;

	i = -0.3;
	a = 0;
	while (i < 0.3)
	{
		data->player.ray = len_find(data, data->player.pa + i);
		walls(data, a);
		i += 0.0006;
		a++;
	}
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}