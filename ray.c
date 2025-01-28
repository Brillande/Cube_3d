/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:22:32 by chaikney          #+#    #+#             */
/*   Updated: 2025/01/20 12:27:15 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// Return the wall face that a ray of angle x intersects with
// TODO Implement and test get_wall_face
// Add protection against zero and negative numbers
// TODO How to handle numbers that go above 360 afer adding 45?
enum e_direction	get_wall_face(double x)
{
	if ((x < 0) || (x >= 360))
		return (-1);
	x += 45.0;
	if (x == 0)
		return (NORTH);
	return ((x / 90.0));
}

// NOTE Check that player.side is NOT MEANT TO BE compatible with enums etc
// TODO Compare with player_view_distance
// Calcula la distancia perpendicular desde el jugador hasta la pared más cercana
// angle = ???
// distance = ???
// ca = corrected (against...?) angle
// perp_dist = returned
// NOTE from elsewhere thing. The distance to the camera plane...
//This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
// What do we use PI for?
double	find_distance(t_lib1 *data, double angle)
{
//	double	distance;
	double	ca;
	double	perp_dist;

	 // Determina la distancia inicial basada en el lado del jugador
	 // If this is North-South, we use X, else Y
	 // FIXME This simple version cannot be used unless we know side and delta are scaled to |ray_dir| or eq.
	/* if (data->player.side == 0) */
	/* 	distance = data->side_dist_x - data->delta_x; */
	/* else */
	/* 	distance = data->side_dist_y - data->delta_y; */
	if (data->player.side == 0)
		perp_dist = (data->map_x - data->player_coor_x + (1 - data->direction_x / 2) / data->ray_x) ;
	else
		perp_dist = (data->map_y - data->player_coor_y + (1 - data->direction_y / 2) / data->ray_y) ;
	// Calcula el ángulo corregido
	ca = data->player.pa - angle;
	if (ca < 0)
		ca += 2 * M_PI;
	else if (ca > 2 * M_PI)
		ca -= 2 * M_PI;
	// Calcula la distancia perpendicular usando el coseno del ángulo corregido
	/* perp_dist = distance * cos(ca); */
	/* perp_dist = fabs(perp_dist); */
	// Calcula la posición de la pared en el eje x
	// TODO Split this to a separate function
	if (data->player.side == EAST || data->player.side == WEST)
		data->player.wall_x = data->player.y + data->ray_y * perp_dist;
	else
		data->player.wall_x = data->player.x + data->ray_x * perp_dist;
	// Ajusta la posición de la pared para que esté en el rango [0, 1]
	data->player.wall_x -= floorf(data->player.wall_x);
	return (perp_dist);
}

double len_find(t_lib1 *data, double angle)
{
    // Inicializa las coordenadas del rayo
    data->ray_x = cos(angle);
    data->ray_y = sin(angle);
    data->delta_x = fabs(1 / data->ray_x);
    data->delta_y = fabs(1 / data->ray_y);
    data->hit = 0;

    // Inicializa las coordenadas del mapa
    data->map_x = (int)data->player.x;
    data->map_y = (int)data->player.y;

    // Encuentra el rayo y ejecuta el algoritmo DDA
    get_step_and_side(data);
    dda_alg(data);

    // Calcula y retorna la distancia perpendicular
    return find_distance(data, angle);
}

// Dibuja la vista 3D del entorno
// Loop over each ray to be calculated for the view window
// NOTE Unclear why these values. They give a range of 1000 steps.
// The ray calculation should be based on the width of the window
// and some other parameter, not magic numbers.
// i.e. SCREENWIDTH is the number of rays / x-columns we need to calculate.
// TODO Use FIELDOFVIEW to calculate the angle_offset
// ...what does 0.3 represent in degrees?
// a - the pixel coordinate (x) where the ray will be drawn (in walls)
void	draw_3d(t_lib1 *data)
{
	int		view_col;
	double	angle_offset;
	double	view_step;

	// Inicializa el ángulo de inicio y el contador
	angle_offset = - 0.3;
	view_col = 0;
	view_step = ((fabs(angle_offset) * 2) / SCREENWIDTH);
	// Moved this from len_find - only need called once
	// (It's the player's map coords)
	data->map_y = (int)data->player.y;
	data->map_x = (int)data->player.x;
	// HACK below for debugging, tidy later.
	printf("Debugging len_find loop. map_x: %i\tmap_y: %i\n", data->map_x, data->map_y);
	printf("Debugging len_find loop. player.x: %f\tplayer.y: %f\n", data->player.x, data->player.y);
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
