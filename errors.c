/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaikney <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:22:34 by chaikney          #+#    #+#             */
/*   Updated: 2025/03/25 14:22:35 by chaikney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Wraps the clear up needed in case of the map failing validation
void	bad_map(t_lib1 *map_data, char *error_msg)
{
	ft_printf("%s\n", error_msg);
	clear_map(map_data);
	clear_textures(map_data);
	exit(EXIT_FAILURE);
}

// Clear and exit if there is a problem with the provided path.
void	bad_file(t_lib1 *data, char *error_message)
{
	ft_printf("%s", error_message);
	if (data->fullpath)
		free (data->fullpath);
	exit (EXIT_FAILURE);
}

// Error handling for failures to load the textures.
// NOTE find_next_line reads the remainder of the file so we know it has been
// fully freed.
void	bad_visuals(t_lib1 *data, char *error_message, char *path, int fd)
{
	char	*siphon;
	ft_printf("%s: %s\n", error_message, path);
	if (data->fullpath)
		free(data->fullpath);
	clear_textures(data);
	siphon = find_next_line(fd);
	while (siphon)
	{
		free(siphon);
		siphon = find_next_line(fd);
	}
	close (fd);
	exit (EXIT_FAILURE);
}
