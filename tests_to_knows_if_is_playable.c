/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_to_knows_if_is_playable.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:29:35 by emedina-          #+#    #+#             */
/*   Updated: 2023/09/19 18:33:24 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "so_long.h"

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

int	hasnt_forbidden_char(char *map_content)
{
	int	i;

	i = 0;
	if (map_content)
	{
		while (map_content[i] != '\0')
		{
			if (map_content[i] != '1' && map_content[i] != '0'
				&& map_content[i] != 'C' && map_content[i] != 'E'
				&& map_content[i] != 'P' && map_content[i] != '\n')
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

int	count_p_e_c(char **map, t_lib1 *map_data, char target)
{
	int	count;
	int	x;
	int	y;

	count = 0;
	x = 0;
	y = 0;
	while (x < map_data->how_many_lines)
	{
		y = 0;
		while (y < map_data->how_many_colums)
		{
			if (map[x][y] == 'P')
			{
				map_data->player_coor_x = x;
				map_data->player_coor_y = y;
			}
			if (map[x][y] == target)
				count++;
			y++;
		}
		y = 0;
		x++;
	}
	return (count);
}
