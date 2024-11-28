#include "cube_3d.h"

void	key_left(t_lib1 *data)
{
	data->player.pa -= 0.05 * M_PI;
	if (data->player.pa < 0)
		data->player.pa += 2 * M_PI;
	data->player.x_camera = cos(data->player.pa) * 5.0;
	data->player.y_camera = sin(data->player.pa) * 5.0;
}

void	key_right(t_lib1 *data)
{
	data->player.pa += 0.05 * M_PI;
	if (data->player.pa > 2 * M_PI)
		data->player.pa -= 2 * M_PI;
	data->player.x_camera = cos(data->player.pa) * 5.0;
	data->player.y_camera = sin(data->player.pa) * 5.0;
}

void	key_a(t_lib1 *data)
{
	double	move_x;
	double	move_y;

	move_x = data->player.x + data->player.game_speed
		* cos(data->player.pa - 0.5 * M_PI);
	move_y = data->player.y + data->player.game_speed
		* sin(data->player.pa - 0.5 * M_PI);
	if (check_move(move_x, move_y, data))
	{
		data->player.y = move_y;
		data->player.x = move_x;
	}
}

void	key_d(t_lib1 *data)
{
	double	move_x;
	double	move_y;

	move_x = data->player.x + data->player.game_speed
		* cos(data->player.pa + 0.5 * M_PI);
	move_y = data->player.y + data->player.game_speed
		* sin(data->player.pa + 0.5 * M_PI);
	if (check_move(move_x, move_y, data))
	{
		data->player.y = move_y;
		data->player.x = move_x;
	}
}

void	key_s(t_lib1 *data)
{
	double	move_x;
	double	move_y;

	move_x = data->player.x - data->player.game_speed * cos(data->player.pa);
	move_y = data->player.y - data->player.game_speed * sin(data->player.pa);
	if (check_move(move_x, move_y, data))
	{
		data->player.x = move_x;
		data->player.y = move_y;
	}
}