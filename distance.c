#include "cube_3d.h"

void	dda_alg(t_lib1 *data, t_lib1 *ca)
{
	while (ca->dmg == 0)
	{
		if (ca->x_side < ca->y_side)
		{
			ca->x_side += ca->x_delta;
			ca->x_map += ca->x_step;
			data->player.side = 0 + (ca->x_step + 1);
		}
		else
		{
			ca->y_side += ca->y_delta;
			ca->y_map += ca->y_step;
			data->player.side = 1 + (1 + ca->y_step);
		}
		if (data->map[ca->y_map][ca->x_map] == '1')
			ca->dmg = 1;
	}
}

void	find_ray(t_lib1 *cal, t_lib1 *data)
{
	if (cal->ray_x < 0)
	{
		cal->x_step = -1;
		cal->x_side = (data->player.x - cal->x_map) * cal->x_delta;
	}
	else
	{
		cal->x_step = 1;
		cal->x_side = (cal->x_map + 1.0 - data->player.x) * cal->x_delta;
	}
	if (cal->ray_y < 0)
	{
		cal->y_step = -1;
		cal->y_side = (data->player.y - cal->y_map) * cal->y_delta;
	}
	else
	{
		cal->y_step = 1;
		cal->y_side = (cal->y_map + 1.0 - data->player.y) * cal->y_delta;
	}
}

double	find_distance(t_lib1 *data, t_lib1 *cal, double angle)
{
	double	distance;
	double	ca;
	double	perp_dist;

	if (data->player.side == 0 || data->player.side == 2)
		distance = cal->x_side - cal->x_delta;
	else
		distance = cal->y_side - cal->y_delta;
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
	t_lib1	maths;

	maths.y = (int)data->player_coor_y;
	maths.x = (int)data->player_coor_x;
	maths.x_ray = cos(angle);
	maths.y_ray = sin(angle);
	maths.x_delta = fabs(1 / maths.x_ray);
	maths.dmg = 0;
	maths.y_delta = fabs(1 / maths.y_ray);
	find_ray(&maths, data);
	dda_alg(data, &maths);
	return (find_distance(data, &maths, angle));
}

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