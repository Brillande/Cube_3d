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
// TODO Do the simple maths version of this.
// TODO Is angle in DEGREES or RADIANS??
/* double	find_distance(t_lib1 *data, double angle) */
/* { */
/* //	double	distance; */
/* 	double	ca; */
/* 	double	perp_dist; */

/* 	 // Determina la distancia inicial basada en el lado del jugador */
/* 	 // If this is North-South, we use X, else Y */
/* 	 // NOTE Can use this simple version as we know side and delta are scaled to |ray_dir| or eq. */
/* 	 // THEY ARE. HOW DO I KNOW THAT? */
/* 	if (data->player.side == 0) */
/* 		perp_dist = data->side_dist_x - data->delta_x; */
/* 	else */
/* 		perp_dist = data->side_dist_y - data->delta_y; */
/* 	/\* if (data->player.side == 0) *\/ */
/* 	/\* 	perp_dist = (data->map_x - data->player_coor_x + (1 - data->direction_x / 2) / data->ray_x) ; *\/ */
/* 	/\* else *\/ */
/* 	/\* 	perp_dist = (data->map_y - data->player_coor_y + (1 - data->direction_y / 2) / data->ray_y) ; *\/ */
/* 	// Calcula el ángulo corregido */
/* 	ca = data->player.pa - angle; */
/* 	if (ca < 0) */
/* 		ca += 2 * M_PI; */
/* 	else if (ca > 2 * M_PI) */
/* 		ca -= 2 * M_PI; */
/* 	// Calcula la distancia perpendicular usando el coseno del ángulo corregido */
/* 	/\* perp_dist = distance * cos(ca); *\/ */
/* 	/\* perp_dist = fabs(perp_dist); *\/ */
/* 	// Calcula la posición de la pared en el eje x */
/* 	// TODO Split this to a separate function -- what does it *do*?? */
/* 	if (data->player.side == EAST || data->player.side == WEST) */
/* 		data->player.wall_x = data->player.y + data->ray_y * perp_dist; */
/* 	else */
/* 		data->player.wall_x = data->player.x + data->ray_x * perp_dist; */
/* 	// Ajusta la posición de la pared para que esté en el rango [0, 1] */
/* 	data->player.wall_x -= floorf(data->player.wall_x); */
/* 	return (perp_dist); */
/* } */

// Calculate the length of a ray (for one screen column) before it strikes a wall
// TODO Make sure that ray_x/y are set correctly. Where?
// - what is it representing?
// - what format is it mean to be in? For the delta thing it *must* be radians!
// Get a vector representation of the ray at angle (deg to radian, radian to x and y)
/* double len_find(t_lib1 *data, double angle) */
/* { */
/* 	double	rads; */

/*     // Inicializa las coordenadas del rayo */
/*     // HACK Protect against accidental division by zero. Would this even work? */
/* 	printf("In len_find. angle passed in: %f\n", angle); */
/*     /\* if (data->ray_x == 0) *\/ */
/* 	/\* 	data->ray_x = 1e30; *\/ */
/*     /\* if (data->ray_y == 0) *\/ */
/* 	/\* 	data->ray_y = 1e30; *\/ */
/*     // NOTE angle must be in RADIANS for this. Is it? */
/*     rads = degrees_to_radians(angle); */
/* 	// NOTE These two lines convert the ray representation from radians to vector */
/*     data->ray_x = cos(rads); */
/*     data->ray_y = sin(rads); */
/*     data->delta_x = fabs(1 / data->ray_x); */
/*     data->delta_y = fabs(1 / data->ray_y); */
/*     data->hit = 0; */
/* 	data->map_y = (int)data->player.y; */
/* 	data->map_x = (int)data->player.x; */

/*     // Encuentra el rayo y ejecuta el algoritmo DDA */
/*     get_step_and_side(data, data->player);	// NOTE Only a ray needed here */
/*     dda_alg(data);				// NOTE Ray and map needed there. */

/*     // Calcula y retorna la distancia perpendicular */
/*     // NOTE Does find_distance work with radians, vectors, or degrees?? */
/*     return find_distance(data, rads); */
/* //    return find_distance(data, angle); */
/* } */

// Dibuja la vista 3D del entorno
// Loop over each ray to be calculated for the view window
// NOTE Unclear why these values. They give a range of 1000 steps.
// The ray calculation should be based on the width of the window
// and some other parameter, not magic numbers.
// i.e. SCREENWIDTH is the number of rays / x-columns we need to calculate.
// TODO Use FIELDOFVIEW to calculate the angle_offset
// ...what does 0.3 represent in degrees?
// a - the pixel coordinate (x) where the ray will be drawn (in walls)
// FIXME There is a mix of DEGREES and RADIANS in use here, it is confusing
// FIXME player.pa and radians_offset are both 0 when we call a ray...
// ...which is then not set up correctly.
// DONE Identify texture to be used. in set_impact_side()
void	draw_3d(t_lib1 *data)
{
	int		view_col;
//	double	radian_offset;
//	double	deg_offset;
//	double	view_step;
	
	mlx_image_t	*new_img;
	t_ray	test_ray;
	double	camera_x;

	// Inicializa el ángulo de inicio y el contador
	// NOTE This is a radian value sometimes applied to degrees later! Makes things very small.
//	radian_offset = - 0.3;
//	deg_offset = radians_to_degrees(radian_offset);
	view_col = 0;
//	view_step = ((fabs(deg_offset) * 2) / SCREENWIDTH);	// FIXME Calculate view_step in RADIANS!!!
//	view_step = ((fabs(radian_offset) * 2) / SCREENWIDTH);
	// HACK below for debugging, tidy later.
//	printf("Debugging len_find loop. radian_offset: %f\tdegree offset: %f\tview_step: %f\n", radian_offset, deg_offset, view_step);
//	printf("Debugging len_find loop. map_x: %i\tmap_y: %i\n", data->map_x, data->map_y);
	printf("Debugging len_find loop. player.x: %f\tplayer.y: %f\n", data->player.x, data->player.y);
	
	print_player_info(data->player);	// HACK for debugging
//	while (angle_offset < 0.3)
	// Get a new image to draw on -- this could use make_background() ?
	new_img = mlx_new_image(data->mlx, SCREENWIDTH, SCREENHEIGHT);
	while (view_col < SCREENWIDTH)
	{
		// Recorre un rango de ángulos para dibujar cada rayo
		camera_x = get_camera_x((view_col));
		printf("About to set up a ray using player angle: %f no offset\n", data->player.pa);
//		test_ray = setup_ray(data, data->player.pa + radian_offset);
		test_ray = setup_ray(data, data->player.pa, camera_x);
		dda_for_one_ray(&test_ray, data->map_array);
//		data->player.ray = len_find(data, data->player.pa + deg_offset); // FIXME The 2nd parameter never changes
		test_ray.length = find_distance_ray(&test_ray);	// NOTE does not *have* to be a pointer
		// TODO Are the player.x/y locations the correct ones for this? We only have texture in the middle of the screen....
		test_ray.wall_strike = find_strike_point(&test_ray, data->player.x, data->player.y);
//		printf("I said Strike point is: %f\n", test_ray.wall_strike);
//		data->player.ray = test_ray.length;
//		solid_walls(data, test_ray.length, view_col, new_img);	// HACK Solid colour test function
		// HACK hardcoded texture below!
		// En la función draw_3d:
		mlx_texture_t *selected_texture = data->texture[test_ray.impact_side];
		textured_walls(data, view_col, new_img, test_ray.wall_strike, selected_texture, test_ray.length);
//		walls(data, view_col);
		view_col++;
	}
	// Muestra la imagen en la ventana
	new_img->enabled = true;
	mlx_delete_image(data->mlx, data->img);
	data->img = new_img;
//	mlx_image_to_window(data->mlx, new_img, 0, 0);	// HACK May have to replce the data->img pointer!
	mlx_image_to_window(data->mlx, data->img, 0, 0);	// FIXME Invalid read here
}

// Return the x-coordinate on the camera plane for the ray in screen_col
// Result is normalised to a range of -1 (left) to 1 (right edge)
double	get_camera_x(int screen_col)
{
	double	camera_x;

	camera_x = (2 * screen_col) / (double) SCREENWIDTH - 1;
	return (camera_x);
}

// Find the point of the wall where the ray struck it.
// NB The point is normalised to a 0-1 range
// Formula based on this:
//   if (side == 0) wallX = posY + perpWallDist * rayDirY;
//      else           wallX = posX + perpWallDist * rayDirX;
//      wallX -= floor((wallX));
double	find_strike_point(t_ray *r, double x_origin, double y_origin)
{
	double	hit_me;

	printf("Finding wall strike point with X: %f, Y: %f, length: %f\tdirection X: %f, Y: %f", x_origin,
		   y_origin, r->length, r->ray_x, r->ray_y);
	  if (r->axis == 0) { // Pared vertical
        hit_me = y_origin + r->length * r->ray_y;
    } else { // Pared horizontal
        hit_me = x_origin + r->length * r->ray_x;
    }
	// Ajusta la posición de la pared para que esté en el rango [0, 1]
	hit_me -= floorf(hit_me);
	if ((r->impact_side == EAST || r->impact_side == SOUTH)) {
        hit_me = 1 - hit_me;
    }
	if ((hit_me > 1) || (hit_me < 0))
		printf("***** Strike point calculation is bad! ");
	printf("\nStrike point is: %f\n", hit_me);
	return (hit_me);
}
