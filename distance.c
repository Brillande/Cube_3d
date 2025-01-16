#include "cube_3d.h"

// NOTE What does dda stand for?
// TODO Use e_directions instead of cryptic numbers here
// FIXME Norm forbids ternary expressions like
// data->player.side = (ca->step_x > 0) ? 0 : 1;
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
        // FIXME Should this be map_array[][]? map is blank
        if (data->map[ca->map_y][ca->map_x] == '1') {
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

/* double	find_distance(t_lib1 *data, t_lib1 *cal, double angle) */
/* { */
/* 	double	distance; */
/* 	double	ca; */
/* 	double	perp_dist; */

/* 	if (data->player.side == 0 || data->player.side == 2) */
/* 		distance = cal->side_x - cal->delta_x; */
/* 	else */
/* 		distance = cal->side_y - cal->delta_y; */
/* 	ca = data->player.pa - angle; */
/* 	if (ca < 0) */
/* 		ca += 2 * M_PI; */
/* 	else if (ca > 2 * M_PI) */
/* 		ca -= 2 * M_PI; */
/* 	perp_dist = distance * cos(ca); */
/* 	perp_dist = fabs(perp_dist); */
/* 	if (data->player.side == EAST || data->player.side == WEST) */
/* 		data->player.wall_x = data->player.y + cal->ray_y * perp_dist; */
/* 	else */
/* 		data->player.wall_x = data->player.x + cal->ray_x * perp_dist; */
/* 	data->player.wall_x -= floorf(data->player.wall_x); */
/* 	return (perp_dist); */
/* } */

// FIXME defined more than once
/* double	len_find(t_lib1 *data, double angle) */
/* { */
/* 	t_lib1	maths; */

/* 	maths.y = (int)data->player_coor_y; */
/* 	maths.x = (int)data->player_coor_x; */
/* 	maths.ray_x = cos(angle); */
/* 	maths.ray_y = sin(angle); */
/* 	maths.delta_x = fabs(1 / maths.ray_x); */
/* 	maths.hit = 0; */
/* 	maths.delta_y = fabs(1 / maths.ray_y); */
/* 	find_ray(&maths, data); */
/* 	dda_alg(data, &maths); */
/* 	return (find_distance(data, &maths, angle)); */
/* } */

// NOTE Unclear what these constants are.
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