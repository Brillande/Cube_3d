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
int	find_top_left(char *str)
{
	int	i;

	i = 0;
	while ((str[i] != '\0') && (str[i] == ' '))
		i++;
	return (i);
}

// return 1 if either side has no wall
// Return 0 if both directions reach a wall or startpoint is invalid
// refuse to test walls or newlines
// Move left through the array until a 1 is hit.
// Move right through the array (until the max) or a 1 is hit.
int	walls_horizontal(int x, char *mapline, int max_x)
{
	int	test_x;

	if ((mapline[x] != '1') && (mapline[x] != '\n'))
	{
		test_x = x;
		while (test_x >= 0)
		{
			if (mapline[test_x] == '1')
				break ;
			test_x--;
		}
		if (test_x < 0)
			return (1);
		test_x = x;
		while (test_x <= max_x)
		{
			if (mapline[test_x] == '1')
				break ;
			test_x++;
		}
		if (test_x > max_x)
			return (1);
	}
	return (0);
}

int	walls_vertical2(int test_y, int max_y, int column, char **map_array)
{
	while (test_y <= max_y)
	{
		if (!map_array[test_y][column])
			return (1);
		else if (map_array[test_y][column] == ' ')
			return (1);
		else if (map_array[test_y][column] == '1')
			break ;
		test_y++;
	}
	if (test_y > max_y)
		return (1);
	return (0);
}

// return 1 if either end has no wall
// Return 0 if both directions reach a wall or startpoint is invalid
// we are testing a column; so x shoulld not change
// FIXED Does not correctly reject not_bounded.cub
// Treat a mising value as a fail, i.e. A gap before reaching a 1.
// start_line = coord to cheeck from
// column = same, other axis
// map_array = the map
// max_y = the number of lines in the map, where to stop the downward check.
// FIXED walls_vertical fails to catch map8_broken
int	walls_vertical(int start_line, char **map_array, int max_y, int column)
{
	int	test_y;

	if ((map_array) && (map_array[start_line][column] != '1'))
	{
		test_y = start_line;
		while (test_y >= 0)
		{
			if (!map_array[test_y][column])
				return (1);
			else if (map_array[test_y][column] == ' ')
				return (1);
			else if (map_array[test_y][column] == '1')
				break ;
			test_y--;
		}
		if (test_y < 0)
			return (1);
		test_y = start_line;
		return (walls_vertical2(test_y, max_y, column, map_array));
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
// NOTE If our square is 1, space or newline we do not need to check it.
// TODO BUT! a space counts as a gap if it is inside the body of the map...
// TODO Check that the how_many_lines thing works.
int	check_each_square(t_lib1 *map_data)
{
	int	test_col;
	int	test_line;
	int	test_line_len;

	test_line = 0;
	while (test_line < (map_data->how_many_lines))
	{
		test_col = find_top_left(map_data->map_array[test_line]);
		test_line_len = (int) ft_strlen(map_data->map_array[test_line]) - 1;
		while (test_col < test_line_len)
		{
			if (walls_horizontal(test_col, map_data->map_array[test_line],
					test_line_len) == 1)
				return (0);
			if (walls_vertical(test_line, map_data->map_array,
					map_data->how_many_lines, test_col) == 1)
				return (0);
			test_col++;
		}
		test_col = 0;
		test_line++;
	}
	return (1);
}
