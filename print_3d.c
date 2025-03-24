/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:36:29 by emedina-          #+#    #+#             */
/*   Updated: 2025/03/19 17:33:07 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Esta función obtiene el valor RGBA de un píxel en una textura dada
// Safely extract an RGBA colour from x, y coords of given texture
int	rgba_from_texture(mlx_texture_t *texture, int x, int y)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;
	unsigned int	in;

	in = y * texture->width * 4 + (x * 4);
	if (in + 3 >= texture->width * texture->height * 4)
		return (0);
	r = texture->pixels[y * texture->width * 4 + (x * 4)];
	g = texture->pixels[y * texture->width * 4 + (x * 4) + 1];
	b = texture->pixels[y * texture->width * 4 + (x * 4) + 2];
	a = texture->pixels[y * texture->width * 4 + (x * 4) + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

// Función para dibujar paredes texturizadas
// Set up the variables needed to draw one column of the screen.
// - tex_pos
// - tex_step
// - start_point
// - end_point
// NOTE view_col is also needed but is set elsewhere (for now)
void	textured_walls(t_lib1 *data, mlx_image_t *img,
						mlx_texture_t *tex, t_ray *ray)
{
	int		line_height;
	int		midpoint;

	if (ray->length == 0)
		line_height = SCREENHEIGHT;
	else
		line_height = SCREENHEIGHT / ray->length;
	midpoint = SCREENHEIGHT / 2;
	ray->start_point = (-line_height / 2) + midpoint;
	ray->end_point = (line_height / 2) + midpoint;
	if (ray->end_point >= SCREENHEIGHT)
		ray->end_point = SCREENHEIGHT - 1;
	data->tex_x = (int)(ray->wall_strike * (double)tex->width);
	data->tex_step = 1.0 * tex->height / line_height;
	if (ray->start_point < 0)
	{
		data->tex_pos = -ray->start_point * data->tex_step;
		ray->start_point = 0;
	}
	else
		data->tex_pos = 0;
	textured_walls2(data, img, tex, ray);
}

// TODO Transfer view_col to t_ray from t_lib1, it is a ray property!
void	textured_walls2(t_lib1 *data, mlx_image_t *img,
						mlx_texture_t *tex, t_ray *ray)
{
	int	i;
	int	tex_y;

	i = 0;
	while (i < ray->start_point)
		mlx_put_pixel(img, data->view_col, i++, data->rgb_ceiling);
	while (i <= ray->end_point)
	{
		tex_y = (int)data->tex_pos & (tex->height - 1);
		data->tex_pos += data->tex_step;
		mlx_put_pixel(img, data->view_col, i++,
			rgba_from_texture(tex, data->tex_x, tex_y));
	}
	while (i < SCREENHEIGHT)
		mlx_put_pixel(img, data->view_col, i++, data->rgb_floor);
}
