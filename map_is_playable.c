/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_playable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:29:35 by emedina-          #+#    #+#             */
/*   Updated: 2025/02/27 16:44:57 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// FIXME There are too many functions in map_is_playable.c

// The player should only be generated in one place in the map.
// Return 1 if the map has one player exactly
// Return 0 if there are 0 or more than 1 players.
int	only_one_player(char *map)
{
	char	*c;
	int		flag;

	c = map;
	flag = 0;
	while (*c != '\0')
	{
		if ((*c == 'N') || (*c == 'W') || (*c == 'E') || (*c == 'S'))
			flag++;
		c++;
		if (flag > 1)
			return (0);
	}
	if (flag == 0)
		return (0);
	else
		return (1);
}

// Helper for basic_wall_test. Returns the number of '1' chars in a line.
int	count_walls(char *map_line)
{
	int	n;
	int	j;

	n = 0;
	j = 0;
	while ((map_line) && (map_line[j] != '\0'))
	{
		if (map_line[j] == '1')
			n++;
		j++;
	}
	return (n);
}

// A simple / quick test: each line must have at least 2 wall characters.
// Return 0 if the map cannot be played.
// Return 1 if the map can be played.
// NOTE Special case treatment of first and last lines for "pointy" maps
int	basic_wall_test(t_lib1 *map_data)
{
	int	i;

	i = 1;
	if (count_walls(map_data->map_array[0]) < 1)
		return (0);
	while (i < (map_data->how_many_lines - 1))
	{
		if (count_walls(map_data->map_array[i]) < 2)
			return (0);
		i++;
	}
	if (count_walls(map_data->map_array[map_data->how_many_lines - 1]) < 1)
		return (0);
	return (1);
}

// Given the initial player angle, set values of a *perpendicualr* camera vector
// ...of what size??
// - first we convert the angle into a direction vector
// - then we make a perpendicular vector:
// "To get the 2D vector perpendicular to another 2D vector simply
// swap the X and Y components, negating the new Y component.
// So { x, y } becomes { y, -x }.""
void	setup_camera_plane(double rads, t_player *player)
{
	t_vec	direction;

	direction = radians_to_vector(rads);
	player->x_camera = direction.y;
	player->y_camera = -1 * direction.x;
}

// this should not be needed, but it copies the read player start position
// to the player thing that is read later.
// TODO Perhaps this should read from a t_map and return a t_player?
// x/y:		precise location of the player on the map (centre of initial coords)
// pa:		RADIANS representation of the player's orientation, conversion of player_faces
// ray:		TODO remove this I think
// side:	unknown
// game_speed:	unknown
// wall_x:	unknown
void	setup_player(t_lib1 *map_data)
{
	map_data->player.x = (double)(map_data->player_coor_x) + 0.5;
	map_data->player.y = (double)(map_data->player_coor_y + 0.5);
	map_data->player.pa = degrees_to_radians(map_data->player_faces);
	map_data->player.ray = 0.0;
	map_data->player.side = 0;
	setup_camera_plane(map_data->player.pa, &map_data->player);
	map_data->player.game_speed = 1;
	map_data->player.wall_x = 0;
}
