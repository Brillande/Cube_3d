/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_to_knows_if_is_playable.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:29:35 by emedina-          #+#    #+#             */
/*   Updated: 2024/11/27 17:39:36 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "cube_3d.h"

// DONE Change test: permitted characters
// TODO Implement tests for the non-map elements: present and valid
// DONE Change test: filename is .cub not .ber
// DONE Change tests: spaces are allowed
// DONE Remove test for "valid path" - not needed in this game.
// NOTE Why are we storing two copies of the map_content in the struct??
// NOTE how_many_lines and how_many_columns was counted in read_map_from_fd
// TODO There is no need to return map_data, caller doesn't use it
t_lib1	*test_to_knows_if_is_playable(t_lib1 *map_data)
{
	if (!hasnt_forbidden_char(map_data->map_content))
	{
		exit(EXIT_FAILURE);
	}
	map_data->map_array = ft_split(map_data->map_content, '\n');
	map_data->cpy_of_map_array = ft_split(map_data->map_content, '\n');
	map_data->how_many_lines = count_words(map_data->map_content, '\n');
	map_data->how_many_colums = (map_data->map_length
			/ map_data->how_many_lines) - 1;
	return (map_data);
}

// FIXME The map does not have be rectangular
// ...the bordering does not work for irregular shapes
// Can we assume that the map starts at 0,0 or not? NO
// - Find first marker
// - Must be a wall (1)
void	isnt_borded_of_walls(char **map_array, int lines, int colms)
{
	int	x;
	int	y;

	x = 0;
	while (x < lines)
	{
		y = 0;
		while (y < colms)
		{
			if (map_array[0][y] != '1' || map_array[lines - 1][y] != '1'
				|| map_array[0][y + 1] != '1')
			{
				perror("\nerror\n no esta rodeado de muros o no es rectangular");
				exit(EXIT_FAILURE);
			}
			if (map_array[x][0] != '1' || map_array[x][colms] != '1')
			{
				perror("\nerror\n no esta rodeado de muros o no es rectangular");
				exit(EXIT_FAILURE);
			}
			y++;
		}
		x++;
	}
}

// FIXED Change the allowed characters: 0, 1, N, E, W, S
// ...newline maybe OK still...
// NOTE For this to work now it *must* only receive the map part of the file.
// NOTE Spaces are OK, but may need different handling.
// TODO Check whether the map is *always* the end of the file
// TODO Check whether the return value causes EXIT on failure
int	hasnt_forbidden_char(char *map_content)
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
				perror("\nerror\n hay algun caracter prohibido");
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

// How many vertical lines in the map data.
// Counts the "words" separated by char c
// In this program we use it calling with newline
int	count_words(const char *str, char c)
{
	int	num_words;
	int	i;

	num_words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			++num_words;
			while (str[i] != '\0' && str[i] != c)
				++i;
		}
		else
			++i;
	}
	return (num_words);
}
