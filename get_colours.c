/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colours.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:03:27 by chaikney          #+#    #+#             */
/*   Updated: 2025/04/02 18:39:35 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Take an array of character and return the number of (non-NULL)
// members it has.
int	count_parts(char **arr)
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
void	clear_array(char **arr)
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
int	read_colour_from_array(char **parts)
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
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_printf("Error\n", 2);
		ft_printf("RGB values must be between 0 and 255\n", 2);
		return (-1);
	}
	return (0 << 24 | r << 16 | g << 8 | b);
}
