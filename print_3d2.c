/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print3d2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:39:56 by emedina-          #+#    #+#             */
/*   Updated: 2025/02/26 18:41:28 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// FIXME The EAST and NORTH values here will need to be changed,
// post-enumeration
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
