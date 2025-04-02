/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_visuals_and_colours2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:29:24 by emedina-          #+#    #+#             */
/*   Updated: 2025/04/02 18:36:59 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_textures(t_lib1 *map_data, int fd)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		map_data->texture[i] = mlx_load_png(map_data->texture_paths[i]);
		if (!map_data->texture[i])
		{
			bad_visuals(map_data, "Texture not in PNG format",
				map_data->texture_paths[i], fd);
		}
		i++;
	}
}

int	get_colour_array_from_line(int fd, char key, char *line)
{
	int		i;
	char	**parts;

	i = 0;
	(void) fd;
	parts = ft_split(line, ',');
	if (count_parts(parts) != 3)
	{
		clear_array(parts);
		return (-1);
	}
	while (parts[0][i] != key)
	{
		if (parts[0][i++] == '\0')
		{
			clear_array(parts);
			return (-1);
		}
	}
	return (read_colour_from_array(parts));
}
