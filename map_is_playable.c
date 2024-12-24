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

// NOTE, this won't handle sticking-out bits at the tlop and bottom....
int	count_walls(char *map_line)
{
	int	n;
	int	j;

	n = 0;
	j = 0;
	while ((map_line) && (map_line[j] != '\0'))
	{
		if (map_line[j]  == '1')
			n++;
		j++;
	}
	ft_printf("Counted %i walls\n", n);	// HACK for debugging
	return (n);
}

// A simple / quick test: each line must have at least 2 wall characters.
// return 0 if each line of map data has at least 2 wall characters.
// Return 1 if not.
// NOTE Special case treatment of first and last lines for "pointy" maps
int	basic_wall_test(t_lib1 *map_data)
{
	int	i;

	i = 1;
	if (count_walls(map_data->map_array[0]) < 1)
		return (1);
	while (i < (map_data->how_many_lines - 1))
	{
		if (count_walls(map_data->map_array[i]) < 2)
			return (1);
		i++;
	}
	if (count_walls(map_data->map_array[map_data->how_many_lines - 1]) < 1)
		return (1);
	return (0);
}

// TODO Implement tests for the non-map elements: present and valid
// NOTE Why are we storing two copies of the map_content in the struct??
// NOTE how_many_lines and how_many_columns was counted in read_map_from_fd
// - Check that map_content only has allowed characters and a single player
// - turn the raw content into map_array using ft_split
// - check to make sure the map is surrounded -- NOTE only works for rectangular maps
// TODO If any test fails, we have to clear map_content!
void	map_is_playable(t_lib1 *map_data)
{
	if ((!only_legal_char(map_data->map_content)) ||
		(!only_one_player(map_data->map_content)))
		exit (EXIT_FAILURE);
	map_data->map_array = ft_split(map_data->map_content, '\n');
	print_map_array(map_data);	// HACK for debugging
	if (basic_wall_test(map_data) == 1)
	{
		ft_printf("Wall count error\n");
		exit (EXIT_FAILURE);
	}
	if (check_each_square(map_data) == 1)
	{
		ft_printf("Map bounding error\n");
		exit (EXIT_FAILURE);
	}
}

// NOTE For this to work now it *must* only receive the map part of the file.
// NOTE Spaces are OK, but may need different handling.
// TODO Check whether the map is *always* the end of the file
// TODO Check whether the return value causes EXIT on failure
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
				perror("\nerror\n hay algun caracter prohibido");
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}
