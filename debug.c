/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaikney <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:12:10 by chaikney          #+#    #+#             */
/*   Updated: 2025/01/17 14:12:15 by chaikney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// HACK This is for debugging, remove later.
void	print_read_from_file(t_lib1 map_data)
{
	ft_printf("Have read file\n");
	ft_printf("North texture: %s\n", map_data.texture_paths[0]);
	ft_printf("South texture: %s\n", map_data.texture_paths[1]);
	ft_printf("East texture: %s\n", map_data.texture_paths[2]);
	ft_printf("West texture: %s\n", map_data.texture_paths[3]);
	ft_printf("Floor colour: %i\n", map_data.rgb_floor);
	ft_printf("Ceiling colour: %i\n", map_data.rgb_ceiling);
	ft_printf("Map data read:\n%s", map_data.map_content);
	ft_printf("Sizes:\nX: %i\tY: %i\n", map_data.how_many_colums,
		map_data.how_many_lines);
}

// HACK for debugging, remove later
// NOTE Now the map is not rectangulaar, cannot rely on how_many_rows
// to count through the array.
// Also, there are no newlines in the map once it arrives in the array.
void	print_map_array(t_lib1 *map_data)
{
	int	j;

	j = 0;
	while (j < map_data->how_many_lines)
	{
		ft_printf("L%i:\t%s\n", j, map_data->map_array[j]);
		j++;
	}
}

// Print the player's coordinates and orientation
// (as a compass bearing, 0-270 degrees).
void	print_start_position(t_lib1 *map_data)
{
	ft_printf("The player starts at X: %i Y: %i, facing %i degrees\n",
		map_data->player_coor_x, map_data->player_coor_y,
		map_data->player_faces);
}
