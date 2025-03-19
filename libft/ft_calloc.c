/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaikney <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:31:49 by chaikney          #+#    #+#             */
/*   Updated: 2023/05/12 12:45:07 by chaikney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Contiguously allocates enough space for
// count objects that are
// size bytes of memory each
// Returns a pointer to the allocated memory.
// (The allocated memory is filled with bytes of value zero.)
void	*ft_calloc(size_t count, size_t size)
{
	size_t	gimme;
	void	*thisthing;

	gimme = (count * size);
	thisthing = malloc(gimme);
	if ((thisthing != NULL) && (gimme != 0))
		ft_bzero(thisthing, gimme);
	return (thisthing);
}
