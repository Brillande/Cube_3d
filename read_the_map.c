/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_the_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:23:01 by emedina-          #+#    #+#             */
/*   Updated: 2023/09/19 12:13:07 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

char	*read_map(char *full_path, int i)
{
	char	*buff;
	int		file;

	buff = malloc(sizeof(char *) * (i + 1));
	if (buff == NULL)
		return (NULL);
	file = open(full_path, O_RDONLY);
	if (file == -1)
		perror("error\n en read_map: no se pudo abrir el archivo");
	else
	{
		read(file, buff, i);
		buff[i] = '\0';
		close(file);
		return (buff);
	}
	return (NULL);
}

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
