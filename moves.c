#include "cube_3d.h"

// Función para mover la cámara hacia la izquierda
void	key_left(t_lib1 *data)
{
    // Disminuye el ángulo de la cámara
    data->player.pa -= 0.05 * M_PI;
    // Ajusta el ángulo si es menor que 0
    if (data->player.pa < 0)
        data->player.pa += 2 * M_PI;
    // Calcula las nuevas coordenadas de la cámara
    data->player.x_camera = cos(data->player.pa) * 5.0;
    data->player.y_camera = sin(data->player.pa) * 5.0;
}

// Función para mover la cámara hacia la derecha
void	key_right(t_lib1 *data)
{
    // Aumenta el ángulo de la cámara
    data->player.pa += 0.05 * M_PI;
    // Ajusta el ángulo si es mayor que 2 * PI
    if (data->player.pa > 2 * M_PI)
        data->player.pa -= 2 * M_PI;
    // Calcula las nuevas coordenadas de la cámara
    data->player.x_camera = cos(data->player.pa) * 5.0;
    data->player.y_camera = sin(data->player.pa) * 5.0;
}

// Función para mover al jugador hacia la izquierda
void	key_a(t_lib1 *data)
{
    double	move_x;
    double	move_y;

    // Calcula las nuevas coordenadas del jugador
    move_x = data->player.x + data->player.game_speed
        * cos(data->player.pa - 0.5 * M_PI);
    move_y = data->player.y + data->player.game_speed
        * sin(data->player.pa - 0.5 * M_PI);
    // Verifica si el movimiento es válido y actualiza las coordenadas del jugador
    if (check_move(move_x, move_y, data))
    {
        data->player.y = move_y;
        data->player.x = move_x;
    }
}

// Función para mover al jugador hacia la derecha
void	key_d(t_lib1 *data)
{
    double	move_x;
    double	move_y;

    // Calcula las nuevas coordenadas del jugador
    move_x = data->player.x + data->player.game_speed
        * cos(data->player.pa + 0.5 * M_PI);
    move_y = data->player.y + data->player.game_speed
        * sin(data->player.pa + 0.5 * M_PI);
    // Verifica si el movimiento es válido y actualiza las coordenadas del jugador
    if (check_move(move_x, move_y, data))
    {
        data->player.y = move_y;
        data->player.x = move_x;
    }
}

// Función para mover al jugador hacia atrás
void	key_s(t_lib1 *data)
{
    double	move_x;
    double	move_y;

    // Calcula las nuevas coordenadas del jugador
    move_x = data->player.x - data->player.game_speed * cos(data->player.pa);
    move_y = data->player.y - data->player.game_speed * sin(data->player.pa);
    // Verifica si el movimiento es válido y actualiza las coordenadas del jugador
    if (check_move(move_x, move_y, data))
    {
        data->player.x = move_x;
        data->player.y = move_y;
    }
}