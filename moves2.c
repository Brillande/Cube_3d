#include "cube_3d.h"

// Función para mover al jugador hacia adelante
void	key_w(t_lib1 *data)
{
    double	move_x;
    double	move_y;
    // Calcula las nuevas coordenadas del jugador
    move_x = data->player.x + data->player.game_speed * cos(data->player.pa);
    move_y = data->player.y + data->player.game_speed * sin(data->player.pa);
    // Verifica si el movimiento es válido y actualiza las coordenadas del jugador
    if (check_move(move_x, move_y, data))
    {
        data->player.x = move_x;
        data->player.y = move_y;
    }
}

// Función para verificar si el movimiento es válido
// FIXME len_cols and len_rows are not populated - map is not a rectangle
// (although we need a way to make sure the map_array check is in bounds)
// TODO Confirm that this receives the correct player location to check against
int check_move(int x, int y, t_lib1 *data) {
    // Verifica si las nuevas coordenadas están dentro de los límites del mapa
    if (data->map_array[x][y] == '1')
            return (false);
        return (true);
}

// Función para manejar el movimiento del jugador
void move(t_lib1 *data) {
    // Verifica si se presionó la tecla correspondiente y llama a la función de movimiento adecuada
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_left(&data->player);
//        key_left(data);
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
        key_a(data);
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
        key_d(data);
    if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_right(&data->player);
//        key_right(data);
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
        key_s(data);
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
        key_w(data);
    // Llama a la función para dibujar la vista 3D
    draw_3d(data);
}

// Función para manejar los eventos de teclas
void click_button(mlx_key_data_t keydata, void *info) {
    t_lib1 *data;

    data = (t_lib1 *)info;
    // Cierra la ventana si se presiona la tecla ESC
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(data->mlx);
    // Llama a la función de movimiento
    move(data);
}

// FIXME This ending method leaks memory - should be the same as ESC
// Función para manejar el evento de cerrar la ventana
int close_clik(t_lib1 *data) {
    // Cierra la ventana y termina el programa
    mlx_close_window(data->mlx);
    exit(0);
}
