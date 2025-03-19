/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:36:29 by emedina-          #+#    #+#             */
/*   Updated: 2025/03/19 12:25:33 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// NOTE Is this is a general function we could use elsewhere?
//Esta función obtiene el valor RGBA de un píxel en una textura dada
int	get_rgba(mlx_texture_t *texture, int x, int y)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = texture->pixels[y * texture->width * 4 + (x * 4)];
	g = texture->pixels[y * texture->width * 4 + (x * 4) + 1];
	b = texture->pixels[y * texture->width * 4 + (x * 4) + 2];
	a = texture->pixels[y * texture->width * 4 + (x * 4) + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

// TODO Work out how this relates to the get_background function
//esta función dibuja el techo y el suelo
void	draw_ceiling_and_floor(t_lib1 *data, int i)
{
	int	start;
	int	half;

	start = 0;
	half = SCREENHEIGHT / 2;
	while (start < half)
	{
		mlx_put_pixel(data->img, i, start, data->rgb_ceiling);
		start++;
	}
	while (start < SCREENHEIGHT)
	{
		mlx_put_pixel(data->img, i, start, data->rgb_floor);
		start++;
	}
}

// Draw a wall column in a solid colour
// This is called after we have a correct (ha) height for wall
// - Calculate the pixel range that should be floor, ceiling and wall
// - draw down the screen_column in that colour
// FIXME Too slow! Is there a better way than directly pixel_put?

// find the x-coord of the texture corresponding to wall_strike
// define a step size for us to move up through the texture column
// Drawing the floor and ceiling is the same as solid_walls() but...
//
// TODO Split this oh lord its a mess
// FIXME Current issues: directly ahead we lose 
//the bottom (grey) and top (cut off) - skewed?
// FIXME Mirror effect in map.cub simple case
// - when the ray crosses halfway, RHS is wrong (> player angle)

// Función para dibujar paredes texturizadas
void	textured_walls(t_lib1 *data, mlx_image_t *img,
						mlx_texture_t *tex, t_ray ray)
{
	int		line_height;
	int		midpoint;

	if (ray.length == 0)
		line_height = SCREENHEIGHT;
	else
		line_height = SCREENHEIGHT / ray.length;
	if (ray.impact_side == 1)
		data->tex_x = tex->width - (int)(ray.wall_strike * (double)tex->width);
	else
		data->tex_x = (int)(ray.wall_strike * (double)tex->width);
	data->tex_step = 1.0 * tex->height / line_height;
	midpoint = SCREENHEIGHT / 2;
	data->start_point = (-line_height / 2) + midpoint;
	data->end_point = (line_height / 2) + midpoint;
	textured_walls2(data, img, tex);
}

void	textured_walls2(t_lib1 *data, mlx_image_t *img,
						mlx_texture_t *tex)
{
	int	i;

	if (data->start_point < 0)
	{
		data->tex_pos = -data->start_point * data->tex_step;
		data->start_point = 0;
	}
	else
	{
		data->tex_pos = 0;
	}
	if (data->end_point >= SCREENHEIGHT)
		data->end_point = SCREENHEIGHT - 1;
	i = 0;
	while (i < data->start_point)
		mlx_put_pixel(img, data->view_col, i++, data->rgb_ceiling);
	while (i <= data->end_point)
	{
		data->tex_y = (int)data->tex_pos & (tex->height - 1);
		data->tex_pos += data->tex_step;
		data->colour = get_rgba(tex, data->tex_x, data->tex_y);
		mlx_put_pixel(img, data->view_col, i++, data->colour);
	}
	while (i < SCREENHEIGHT)
		mlx_put_pixel(img, data->view_col, i++, data->rgb_floor);
}
