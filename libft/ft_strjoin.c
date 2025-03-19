/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaikney <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:29:47 by chaikney          #+#    #+#             */
/*   Updated: 2023/05/15 13:12:53 by chaikney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Allocates and returns a new string, which is the
// result of the concatenation of ’s1’ and ’s2’
// s1: The prefix string.
// s2: The suffix string.
// Return The new string. Or NULL if the allocation fails.
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	howbig;
	char	*newstr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	howbig = (ft_strlen(s1) + ft_strlen(s2) + 1);
	newstr = malloc(howbig * sizeof(char));
	if (newstr != NULL)
	{
		while (s1[i] != '\0')
		{
			newstr[i] = s1[i];
			i++;
		}
		while (s2[j] != '\0')
		{
			newstr[i + j] = s2[j];
			j++;
		}
		newstr[i + j] = '\0';
	}
	return (newstr);
}
