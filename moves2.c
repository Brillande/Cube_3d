#include "cube_3d.h"

void	key_w(t_lib1 *data)
{
	double	move_x;
	double	move_y;

	move_x = data->player.x + data->player.game_speed * cos(data->player.pa);
	move_y = data->player.y + data->player.game_speed * sin(data->player.pa);
	if (check_move(move_x, move_y, data))
	{
		data->player.x = move_x;
		data->player.y = move_y;
	}
}

int check_move(int x, int y, t_lib1 *data) {
    if (data->len_cols > x && data->len_rows > y && x > 0 && y > 0) {
        if (data->map[y][x] == '1')
            return (false);
        return (true);
    }
    return (false);
}

void move(t_lib1 *data) {
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
        key_left(data);
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
        key_a(data);
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
        key_d(data);
    if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
        key_right(data);
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
        key_s(data);
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
        key_w(data);
    print_3d(data);
}

void click_button(mlx_key_data_t keydata, void *info) {
    t_lib1 *data;

    data = (t_lib1 *)info;
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(data->mlx);
    move(data);
}

int close_clik(t_lib1 *data) {
    mlx_close_window(data->mlx);
    exit(0);
}