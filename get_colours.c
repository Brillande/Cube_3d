/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colours.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaikney <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:03:27 by chaikney          #+#    #+#             */
/*   Updated: 2025/03/25 13:03:29 by chaikney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Take an array of character and return the number of (non-NULL)
// members it has.
static int	count_parts(char **arr)
{
	int	n;

	n = 0;
	if (!arr)
		return (-1);
	while (arr[n] != (void *) 0)
		n++;
	return (n);
}

// Free each string in an array, then the pointer to that array.
static void	clear_array(char **arr)
{
	int	j;

	j = 0;
	while (arr[j] != (void *)0)
		free (arr[j++]);
	free (arr);
}

// Receive a string array of 3 integers representing red green and blue
// Return a single integer composed of those values.
// NOTE Array size has already been checked, but the values have not.
// NOTE If any part is not a number,  atoi returns 0 and we can safely use it
static int	read_colour_from_array(char **parts)
{
	int		r;
	int		g;
	int		b;
	char	*tmp;

	tmp = ft_substr(parts[0], 2, ft_strlen(parts[0]) - 2);
	r = ft_atoi(tmp);
	free(tmp);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	clear_array(parts);
	return (0 << 24 | r << 16 | g << 8 | b);
}

// Reads lines from file descriptor fd.
// - when the next (non-blank) line is found, split it at commas
// - Look for the key char (i.e. F or C)
// -- we will skip over / allow leading spaces
// - If found, send the array to be turned into colours.
// - If NOT found, free the split array and return -1
// NOTE In happy case, parts array is freed in return function.
static int	get_colour_array(int fd, char key)
{
	int		i;
	char	*line;
	char	**parts;

	i = 0;
	line = find_next_line(fd);
	parts = ft_split(line, ',');
	free (line);
	if (count_parts(parts) != 3)
	{
		clear_array(parts);
		return (-1);
	}
	while (parts[0][i] != key)
	{
		if (parts[0][i++] == '\0')
		{
			clear_array(parts);
			return (-1);
		}
	}
	return (read_colour_from_array(parts));
}

// Wrapper function for safely collecting the 2 colours from an open fd.
void	read_colours(t_lib1 *data, int fd)
{
	data->rgb_floor = get_colour_array(fd, 'F');
	data->rgb_ceiling = get_colour_array(fd, 'C');
	if ((data->rgb_floor == -1) || (data->rgb_ceiling == -1))
		bad_visuals(data, "Colour failure", "");
}
