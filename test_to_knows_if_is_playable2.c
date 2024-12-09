/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_to_knows_if_is_playable2.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:47:47 by emedina-          #+#    #+#             */
/*   Updated: 2024/11/27 17:39:04 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// TODO Understand what this tests
t_lib1	*test_to_knows_if_is_playable2(t_lib1 *map_data)
{
	isnt_borded_of_walls(map_data->map_array, map_data->how_many_lines,
		map_data->how_many_colums);
	return (map_data);
}