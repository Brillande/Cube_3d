#include "cube_3d.h"
// TODO Add 42 header to boundary_test.c

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
int	walls_horizontal(int x, char *mapline, int max_x)
{
	int	test_x;

	if (mapline[x] != '1')
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

// return 1 if either end has no wall
// Return 0 if both directions reach a wall or startpoint is invalid
// we are testing a column; so x shoulld not change
int	walls_vertical(int line, char **map_array, int max_y, int column)
{
	int	test_y;

	if ((map_array) && (map_array[line][column] != '1'))
	{
		test_y = line;
		while (test_y >= 0)
		{
			if (map_array[test_y][column] == '1')
				break ;
			test_y--;
		}
		if (test_y < 0)
			return (1);
		test_y = line;
		while (test_y <= max_y)
		{
			if (map_array[test_y][column] == '1')
				break ;
			test_y++;
		}
		if (test_y > max_y)
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
// FIXME check_each_square fails to allow not_rectangle.cub
int	check_each_square(t_lib1 *map_data)
{
	int	test_col;
	int	test_line;

	test_line = 0;
	test_col = find_top_left(map_data->map_array[test_line]);
	while (test_line < (map_data->how_many_lines))
	{
		while (test_col < (map_data->how_many_colums))
		{
//			ft_printf("col: %i, line:%i\n", test_col, test_line);	// HACK debugging only
			if (walls_horizontal(test_col, map_data->map_array[test_line],
					ft_strlen(map_data->map_array[test_line]) - 1) == 1)
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