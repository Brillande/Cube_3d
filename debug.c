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

void	print_ray_properties(t_ray ray)
{
	ft_printf("Ray leaving from coordinates %i, %i\n", ray.map_x, ray.map_y);
	ft_printf("with vector heading %f, %f", ray.ray_x, ray.ray_y);
	ft_printf("...direction X: %i, Y: %i and axis: %i\n", ray.direction_x, ray.direction_y, ray.axis);
	ft_printf("delta_x: %f,\tdelta_y: %f\n", ray.delta_x, ray.delta_y);
	ft_printf("side_dist_x: %f\tside_dist_y: %f", ray.side_dist_x, ray.side_dist_y);
}

// FIXME I am not getting anything from this.
void	print_player_info(t_player p)
{
	ft_printf("is this all blanks again? %f", p);
	ft_printf("Player info.\nAngle: %f\nX: %f, Y: %f\n", p.pa, p.x,  p.y);
	ft_printf("Ray length: %f\twall_x (meaning unknown): %f\n", p.ray, p.wall_x);
	ft_printf("side: %i\tcamera x: %f, y: %f, game_speed: %f\n", p.side, p.x_camera, p.y_camera, p.game_speed);
}
