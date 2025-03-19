/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaikney <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:09:17 by chaikney          #+#    #+#             */
/*   Updated: 2023/05/11 18:52:07 by chaikney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Apply function ’f’ to each character of the string ’s’,
// and passing its index as first argument
// to create a new string (with malloc(3))
// resulting from successive applications of ’f’
// s: The string on which to iterate.
// f: The function to apply to each character.
// Return The string created from the successive applications of ’f’.
// 		or NULL if the allocation fails.
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*rtnstr;
	unsigned int	i;
	size_t			destsize;

	i = 0;
	destsize = ft_strlen(s) + 1;
	rtnstr = ft_calloc(destsize, sizeof(char));
	if (rtnstr == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		rtnstr[i] = f(i, s[i]);
		i++;
	}
	rtnstr[i] = '\0';
	return (rtnstr);
}
