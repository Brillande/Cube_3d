/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:36:29 by emedina-          #+#    #+#             */
/*   Updated: 2025/02/20 20:10:44 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// NOTE Is this is a general function we could use elsewhere?
//Esta función obtiene el valor RGBA de un píxel en una textura dada

static int	get_rgba(mlx_texture_t *texture, int x, int y)
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

// TODO Give this function a useful name and description
void	fill_info(t_info *info, t_lib1 *data, double height)
{
	info->tex = data->texture[data->player.side];
	if (height >= SCREENHEIGHT)
	{
		info->top = 0;
		info->bottom = SCREENHEIGHT - 1;
		info->text_start = ((height - SCREENHEIGHT) / 2.0)
			* info->tex->height / height;
	}
	else
	{
		info->top = (SCREENHEIGHT - height) / 2;
		info->bottom = (SCREENHEIGHT + height) / 2;
		info->text_start = 0.0;
	}
	info->step = info->tex->height / height;
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
void textured_walls(t_lib1 *data, int screen_col, mlx_image_t *img, double strike_pt, mlx_texture_t *tex, double distance) {
    int tex_x;
	int	tex_y;
    double tex_step;
    int line_height;
    int midpoint;
    int start_point;
    int end_point;
    int i;
    double tex_pos;
    int colour;

    if (distance == 0)
        line_height = SCREENHEIGHT;
    else
        line_height = SCREENHEIGHT / distance;

    tex_x = (int)(strike_pt * (double)tex->width);
    tex_step = 1.0 * tex->height / line_height;
    midpoint = SCREENHEIGHT / 2;
    start_point = (-line_height / 2) + midpoint;
    end_point = (line_height / 2) + midpoint;

    // Ajustar start_point y end_point para manejar el zoom al acercarse a una pared
    if (start_point < 0) {
        tex_pos = -start_point * tex_step;
        start_point = 0;
    } else {
        tex_pos = 0;
    }

    if (end_point >= SCREENHEIGHT)
        end_point = SCREENHEIGHT - 1;

    i = 0;
    while (i < start_point)
        mlx_put_pixel(img, screen_col, i++, data->rgb_ceiling);

    while (i <= end_point) {
        tex_y = (int)tex_pos & (tex->height - 1);
        tex_pos += tex_step;
        colour = get_rgba(tex, tex_x, tex_y);
        mlx_put_pixel(img, screen_col, i++, colour);
    }

    while (i < SCREENHEIGHT)
        mlx_put_pixel(img, screen_col, i++, data->rgb_floor);
}

// FIXME The EAST and NORTH values here will need to be changed, post-enumeration
// What was specific about those two that meant the maths would be different?
// ...in the old version they were 2 and 4. Can't see any value here.
// NOTE What does player.side represent?
// NOTE What does player.ray represent?
// NOTE What is t_info doing?
// Esta función dibuja las paredes en la pantalla
void	walls(t_lib1 *data, int i)
{
	double	height;
	int		x;
	t_info	info;

	height = SCREENHEIGHT / data->player.ray;
	x = 0;
	fill_info(&info, data, height);
	draw_ceiling_and_floor(data, i);
	while (x < info.bottom - info.top)
	{
		if (data->player.side == EAST || data->player.side == NORTH)
			info.color = get_rgba(info.tex,
					((unsigned int)((1.0 - data->player.wall_x)
							* info.tex->width)),
					((unsigned int)(info.text_start + x * info.step)));
		else
			info.color = get_rgba(info.tex,
					((unsigned int)((data->player.wall_x) * info.tex->width)),
					((unsigned int)(info.text_start + x * info.step)));
		mlx_put_pixel(data->img, i, x + info.top, info.color);
		x++;
	}
	i++;
}
