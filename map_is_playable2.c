/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_playable2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:01:27 by emedina-          #+#    #+#             */
/*   Updated: 2025/02/27 16:56:20 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Split the raw map string to an array.
// Ensure it is safely-structured.
// Check that there are no consecutive newlines in the string before splitting.
// ...any other things to protect against?
static char	**split_map_to_array(char *map_string)
{
	int	i;

	i = 0;
	while (map_string[i + 1] != '\0')
	{
		if (map_string[i] == '\n')
			if (map_string[i + 1] == '\n')
				return (NULL);
		i++;
	}
	return (ft_split(map_string, '\n'));
}

// - Check that map_content only has allowed characters and a single player
// - turn the raw content into map_array
// - check to make sure the map is surrounded
// -- first a quick test
// -- then a slower, per-square, one
// - Find the player's position
// - Setup player start data
void	map_is_playable(t_lib1 *map_data)
{
	if ((!only_legal_char(map_data->map_content))
		|| (!only_one_player(map_data->map_content)))
		bad_map(map_data, "Illegal char in map");
	map_data->map_array = split_map_to_array(map_data->map_content);
	if (!map_data->map_array)
		bad_map(map_data, "Map splitting failed to make a valid array\n");
	if (!basic_wall_test(map_data))
		bad_map(map_data, "Wall count error\n");
	if (!check_each_square(map_data))
		bad_map(map_data, "Map bounding error\n");
	get_start_position(map_data);
	if (map_data->player_faces == -1)
		bad_map(map_data, "Player position error\n");
	setup_player(map_data);
}

// NOTE Spaces are OK, but may need different handling.
// Reads the map part of the file (in form of string)
// and complains if an odd character is found.
// Returns 0 if the map cannot be played.
// Returns 1 is the map is acceptable.
int	only_legal_char(char *map_content)
{
	int	i;

	i = 0;
	if (map_content)
	{
		while (map_content[i] != '\0')
		{
			if (map_content[i] != '1' && map_content[i] != '0'
				&& map_content[i] != 'N' && map_content[i] != 'E'
				&& map_content[i] != 'W' && map_content[i] != 'S'
				&& map_content[i] != ' ' && map_content[i] != '\n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
