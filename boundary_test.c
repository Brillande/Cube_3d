/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boundary_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:13:04 by chaikney          #+#    #+#             */
/*   Updated: 2025/02/27 16:52:34 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// return the position of the first character in a map line
// This is simply the first non-space character
static int	find_column_start(char *str)
{
	int	i;

	i = 0;
	while ((str[i] != '\0') && (str[i] == ' '))
		i++;
	return (i);
}

// Perform column check in upwards direction
// return 1 if end has no wall
// Return 0 if reach a wall or startpoint is invalid
// start_line = coord to check from
// column = same, other axis. Does not change.
// map_array = the map
// max_y = the number of lines in the map, where to stop the downward check.
int	walls_downwards(int start_line, char **map_array, int max_y, int column)
{
	int		test_y;
	char	testing;

	if (map_array)
		testing = map_array[start_line][column];
	test_y = start_line;
	while (test_y < max_y)
	{
		if (map_array[test_y][0] == '\n')
			return (1);
		else if (!map_array[test_y][column])
			return (1);
		// what we need is to not be testing any spaces in the last line
		else if ((test_y == max_y - 1) && (testing == ' '))
			return (0);
		else if ((map_array[test_y][column] == ' ') && (testing != ' '))
			return (1);
		else if (map_array[test_y][column] == '1')
			break ;
		test_y++;
	}
	if (test_y >= max_y)
		return (1);
	return (0);
}

// Perform column check in upwards direction
// return 1 if end has no wall
// Return 0 if reach a wall or startpoint is invalid
// Treat a mising value as a fail, i.e. A gap before reaching a 1.
// start_line = coord to check from
// column = same, other axis. Does not change
// map_array = the map
int	walls_upwards(int start_line, char **map_array, int column)
{
	int		test_y;
	char	testing;

	if (map_array)
		testing = map_array[start_line][column];
	if (testing != '1')
	{
		test_y = start_line;
		while (test_y >= 0)
		{
			if (!map_array[test_y][column])
				return (1);
			else if ((map_array[test_y][column] == ' ') && (testing != ' '))
				return (1);
			else if (map_array[test_y][column] == '1')
				break ;
			test_y--;
		}
		if (test_y < 0)
			return (1);
	}
	return (0);
}

// Calls vertical and horizontal check for each square
// Bound to fail in interesting ways with space, player chars, etc.
// ...does not happen on "tall" maps, only wide ones.
// (Tall maps check wrong, only read as far as the other axis)
// ...they must be getting mixed up!
// Return 0 if the map cannot be played
// Return 1 if the map can be played.
// Initial and trailing spaces= bad (or ignore?), others to be tested as normal
int	check_each_square(t_lib1 *map)
{
	int	t_col;
	int	t_line;
	int	t_len;

	t_line = 0;
	while (t_line < (map->how_many_lines))
	{
		t_col = find_column_start(map->map_array[t_line]);
		t_len = (int) ft_strlen(map->map_array[t_line]);
		while (t_col < t_len)
		{
			if (walls_left(t_col, map->map_array[t_line]) == 1
				|| walls_right(t_col, map->map_array[t_line], t_len) == 1)
			{
				printf("left or right boundinfail\n");
				return (0);
			}
			if (walls_upwards(t_line, map->map_array, t_col) == 1)
			{
				printf("upward boundinfail\n");
				return (0);
			}
			if (walls_downwards(t_line, map->map_array,
					map->how_many_lines, t_col) == 1)
			{
				printf("%i, %i\t", t_col, t_line);
				printf("downward boundinfail\n");
				return (0);
			}
			t_col++;
		}
		t_col = 0;
		t_line++;
	}
	return (1);
}
