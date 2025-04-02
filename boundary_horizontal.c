/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boundary_horizontal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaikney <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:37:53 by chaikney          #+#    #+#             */
/*   Updated: 2025/04/02 13:37:55 by chaikney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Confirm the square is bounded horizontally to its left
// return 1 if either side has no wall
// Return 0 if both directions reach a wall or startpoint is invalid
// refuse to test walls or newlines
// Move left through the array until a 1 is hit.
int	walls_left(int x, char *mapline)
{
	int		test_x;
	char	test_char;

	test_char = mapline[x];
	if ((test_char != '1') && (test_char != '\n'))
	{
		test_x = x;
		while (test_x >= 0)
		{
			if (mapline[test_x] == '1')
				break ;
			if ((test_char == ' ') && (mapline[test_x] != ' '))
				return (1);
			test_x--;
		}
		if (test_x < 0)
			return (1);
	}
	return (0);
}

// Confirm the square is bounded horizontally to its right
// return 1 if either side has no wall
// Return 0 if both directions reach a wall or startpoint is invalid
// NOTE We assume walls or newlines have been excluded in walls_left
// Move right through the array (until the max) or a 1 is hit.
int	walls_right(int x, char *mapline, int max_x)
{
	int		test_x;
	char	test_char;

	test_char = mapline[x];
	test_x = x;
	while (test_x <= max_x)
	{
		if (mapline[test_x] == '1')
			break ;
		if ((test_char == ' ') && (mapline[test_x] != ' '))
			return (1);
		test_x++;
	}
	if (test_x > max_x)
		return (1);
	return (0);
}
