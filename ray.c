#include "cube_3d.h"

// TODO Check that player.side is compatible with enums etc
// TODO Compare with player_view_distance
// Calcula la distancia perpendicular desde el jugador hasta la pared más cercana
// angle = ???
// distance = ???
// ca = corrected (against...?) angle
// perp_dist = returned
double	find_distance(t_lib1 *data, t_lib1 *cal, double angle)
{
	double	distance;
	double	ca;
	double	perp_dist;

	 // Determina la distancia inicial basada en el lado del jugador
	if (data->player.side == 0 || data->player.side == 2)
		distance = cal->side_x - cal->delta_x;
	else
		distance = cal->side_y - cal->delta_y;
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
		data->player.wall_x = data->player.y + cal->ray_y * perp_dist;
	else
		data->player.wall_x = data->player.x + cal->ray_x * perp_dist;
	// Ajusta la posición de la pared para que esté en el rango [0, 1]
	data->player.wall_x -= floorf(data->player.wall_x);
	return (perp_dist);
}

// Encuentra la longitud del rayo desde el jugador hasta la pared más cercana
double	len_find(t_lib1 *data, double angle)
{
	t_lib1	cal;

	// Inicializa las coordenadas del mapa y los rayos
	cal.map_y = (int)data->player.y;
	cal.map_x = (int)data->player.x;
	cal.ray_x = cos(angle);
	cal.ray_y = sin(angle);
	cal.delta_x = fabs(1 / cal.ray_x);
	cal.hit = 0;
	cal.delta_y = fabs(1 / cal.ray_y);
	// Encuentra el rayo y ejecuta el algoritmo DDA
	find_ray(&cal, data);
	dda_alg(data, &cal);
	// Calcula y retorna la distancia perpendicular
	return (find_distance(data, &cal, angle));
}

// Dibuja la vista 3D del entorno
// NOTE Unclear what these constants are.
void	draw_3d(t_lib1 *data)
{
	int		a;
	double	i;
	// Inicializa el ángulo de inicio y el contador
	i = -0.3;
	a = 0;
	while (i < 0.3)
	{
		// Recorre un rango de ángulos para dibujar cada rayo
		data->player.ray = len_find(data, data->player.pa + i);
		walls(data, a);
		// Incrementa el ángulo y el contador
		i += 0.0006;
		a++;
	}
	// Muestra la imagen en la ventana
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}