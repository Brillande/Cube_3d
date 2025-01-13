#include "cube_3d.h"

double	find_distance(t_lib1 *data, t_lib1 *cal, double angle)
{
	double	distance;
	double	ca;
	double	perp_dist;

	if (data->player.side == 0 || data->player.side == 2)
		distance = cal->side_x - cal->delta_x;
	else
		distance = cal->side_y - cal->delta_y;
	ca = data->player.pa - angle;
	if (ca < 0)
		ca += 2 * M_PI;
	else if (ca > 2 * M_PI)
		ca -= 2 * M_PI;
	perp_dist = distance * cos(ca);
	perp_dist = fabs(perp_dist);
	if (data->player.side == EAST || data->player.side == WEST)
		data->player.wall_x = data->player.y + cal->ray_y * perp_dist;
	else
		data->player.wall_x = data->player.x + cal->ray_x * perp_dist;
	data->player.wall_x -= floorf(data->player.wall_x);
	return (perp_dist);
}

double	len_find(t_lib1 *data, double angle)
{
	t_lib1	cal;

	cal.map_y = (int)data->player.y;
	cal.map_x = (int)data->player.x;
	cal.ray_x = cos(angle);
	cal.ray_y = sin(angle);
	cal.delta_x = fabs(1 / cal.ray_x);
	cal.hit = 0;
	cal.delta_y = fabs(1 / cal.ray_y);
	find_ray(&cal, data);
	dda_alg(data, &cal);
	return (find_distance(data, &cal, angle));
}

// NOTE What is i? What is it based on?
// a is fed to walls in print3d.c, which is not described.
void	draw_3d(t_lib1 *data)
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