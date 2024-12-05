/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_the_fullpath.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:22:49 by emedina-          #+#    #+#             */
/*   Updated: 2024/11/27 17:38:06 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// TODO Remove hardcoding of maps_directory (move to .h or something)
// TODO Check where fullpath gets freed and where it may not be.
// Takes the value from argv[1], checks it's valid and...
// Adds the full path for the map to the data struct->fullpath
// NOTE Does map_data even have to be returned? It is changed by pointer here.
t_lib1	*join_the_fullpath(t_lib1 *map_data, char *map_name)
{
	char	*map_name_with_extension;
	char	*maps_directory;

	map_name_with_extension = check_extension(map_name);
	if (map_name_with_extension != NULL)
	{
		maps_directory = "maps/";
		map_data->fullpath = ft_strjoin(maps_directory,
				map_name_with_extension);
		if (map_data->fullpath == NULL)
		{
			perror("Error\n al asignar memoria\n");
			exit(EXIT_FAILURE);
		}
	}
	return (map_data);
}

// Check that the filename ends in .cub.
// If yes, return the string; if no, exit the program.
char	*check_extension(char *map_extension)
{
	int	leng;

	leng = 0;
	leng = ft_strlen(map_extension);
	if (map_extension[leng - 1] == 'b' && map_extension[leng - 2] == 'u'
		&& map_extension[leng - 3] == 'c' && map_extension[leng - 4] == '.')
	{
		return (map_extension);
	}
	else
	{
		perror("Error\nLa extension no es .cub\n");
		exit(EXIT_FAILURE);
	}
}
