/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_the_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:23:01 by emedina-          #+#    #+#             */
/*   Updated: 2024/11/27 17:38:47 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// Copy map file contents into a character array of determined length.
// NOTE Again, there is no need to return the tlib here, passed as reference
t_lib1	*read_the_map(t_lib1 *map_data)
{
	map_data->map_length = how_length_is_the_map(map_data->fullpath);
	if (map_data->map_length == 0)
	{
		exit(EXIT_FAILURE);
	}
	map_data->map_content = read_map(map_data->fullpath,
			map_data->map_length);
	return (map_data);
}

// Read the file into a buffer of given size (plus null terminator)
// TODO No longer used, remove later
char	*read_map(char *full_path, int i)
{
	char	*buff;
	int		file;

	buff = malloc(sizeof(char *) * (i + 1));
	if (buff == NULL)
		return (NULL);
	file = open(full_path, O_RDONLY);
	if (file == -1)
	{
		perror("error\n en read_map: no se pudo abrir el archivo");
		return (NULL);
	}
	else
	{
		read(file, buff, i);
		buff[i] = '\0';
		close(file);
		return (buff);
	}
}

// This returns the length of the buffer needed to hold the map
// information being present in the file.
// ...that would imply some get_next_line use and not opening the file here.
// ...find the first line of map data and read until the end.
// TODO No longer used, remove later assuming the replacement works...
int	how_length_is_the_map(char *full_path)
{
	int		file;
	char	*buff[1];
	int		i;

	i = 0;
	file = open(full_path, O_RDONLY);
	if (file == -1)
	{
		perror("ERROR\n No existe el archivo\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		while (read(file, buff, 1))
		{
			i++;
		}
		close(file);
		if (i < 1)
			return (close(file), perror("error,\n mapa vacio"), 0);
		return (i);
	}
}
