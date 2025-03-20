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

// TODO Implement tests for the non-map elements: present and valid
// NOTE Why are we storing two copies of the map_content in the struct??
// NOTE how_many_lines and how_many_columns was counted in read_map_from_fd
// - Check that map_content only has allowed characters and a single player
// - turn the raw content into map_array using ft_split
// - check to make sure the map is surrounded
void	map_is_playable(t_lib1 *map_data)
{
	if ((!only_legal_char(map_data->map_content))
		|| (!only_one_player(map_data->map_content)))
		clear_data(map_data);
	map_data->map_array = ft_split(map_data->map_content, '\n');
	if (!basic_wall_test(map_data))
	{
		ft_printf("Wall count error\n");
		clear_data(map_data);
	}
	if (!check_each_square(map_data))
	{
		ft_printf("Map bounding error\n");
		clear_data(map_data);
	}
	get_start_position(map_data);
	if (map_data->player_faces == -1)
		clear_data(map_data);
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
			{
				perror("Illegal character in map\n");
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}
