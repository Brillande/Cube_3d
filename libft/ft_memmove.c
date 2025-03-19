/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaikney <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:46:20 by chaikney          #+#    #+#             */
/*   Updated: 2023/05/03 11:54:41 by chaikney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Copies len bytes from string src to string dst.
// Returns the original value of dst.
// The two strings may overlap;
// the copy is always done in a non-destructive manner.
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*marker;
	const char	*s;

	marker = dst;
	s = src;
	if (marker == s)
		return (dst);
	if ((s + len <= marker) || (marker + len <= s))
		marker = ft_memcpy(marker, s, len);
	else if (s < marker)
	{
		s += len;
		marker += len;
		while (len-- > 0)
			*--marker = *--s;
	}
	else
	{
		while (len-- > 0)
			*marker++ = *s++;
	}
	return (dst);
}
