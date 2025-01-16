#include "cube_3d.h"

// TODO Check that player.side is compatible with enums etc
// TODO Compare with player_view_distance
// Calcula la distancia perpendicular desde el jugador hasta la pared más cercana
// angle = ???
// distance = ???
// ca = corrected (against...?) angle
// perp_dist = returned
double	find_distance(t_lib1 *data, double angle)
{
	double	distance;
	double	ca;
	double	perp_dist;

	 // Determina la distancia inicial basada en el lado del jugador
	if (data->player.side == 0 || data->player.side == 2)
		distance = data->side_x - data->delta_x;
	else
		distance = data->side_y - data->delta_y;
	// Calcula el ángulo corregido
	ca = data->player.pa - angle;
	if (ca < 0)
		ca += 2 * M_PI;
	else if (ca > 2 * M_PI)
		ca -= 2 * M_PI;
	// Calcula la distancia perpendicular usando el coseno del ángulo corregido
	perp_dist = distance * cos(ca);
	perp_dist = fabs(perp_dist);
	// Calcula la posición de la pared en el eje x
	if (data->player.side == EAST || data->player.side == WEST)
		data->player.wall_x = data->player.y + data->ray_y * perp_dist;
	else
		data->player.wall_x = data->player.x + data->ray_x * perp_dist;
	// Ajusta la posición de la pared para que esté en el rango [0, 1]
	data->player.wall_x -= floorf(data->player.wall_x);
	return (perp_dist);
}

// Encuentra la longitud del rayo desde el jugador hasta la pared más cercana
// TODO variables that don't change should be set outside this function
// ...for example the initial player position.
// We call this function for *every* ray we scan;
// the player is not moving at that time.
double	len_find(t_lib1 *data, double angle)
{
	// Inicializa las coordenadas del mapa y los rayos
	data->map_y = (int)data->player.y;
	data->map_x = (int)data->player.x;
	data->ray_x = cos(angle);
	data->ray_y = sin(angle);
	data->delta_x = fabs(1 / data->ray_x);
	data->hit = 0;
	data->delta_y = fabs(1 / data->ray_y);
	// Encuentra el rayo y ejecuta el algoritmo DDA
	find_ray(data);
	dda_alg(data);
	// Calcula y retorna la distancia perpendicular
	return (find_distance(data, angle));
}

// Dibuja la vista 3D del entorno
// NOTE Unclear why these values. They give a range of 1000 steps.
// The ray calculation should be based on the width of the window
// and some other parameter, not magic numbers.
// i.e. SCREENWIDTH is the number of rays / x-columns we need to calculate.
// TODO Use FIELDOFVIEW to calculate the angle_offset
// ...what does 0.3 represent in degrees?
void	draw_3d(t_lib1 *data)
{
	int		view_col;
	double	angle_offset;
	double	view_step;

	// Inicializa el ángulo de inicio y el contador
	angle_offset = -0.3;
	view_col = 0;
	view_step = ((fabs(angle_offset) * 2) / SCREENWIDTH);
//	while (angle_offset < 0.3)
	while (view_col <= SCREENWIDTH)
	{
		// Recorre un rango de ángulos para dibujar cada rayo
		data->player.ray = len_find(data, data->player.pa + angle_offset);
		walls(data, view_col);
		// Incrementa el ángulo y el contador
//		angle_offset += 0.0006;	// FIXME Remove magic number which was 0.6 / 1000
		angle_offset += view_step;
		view_col++;
	}
	// Muestra la imagen en la ventana
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}