/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaikney <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:33:06 by chaikney          #+#    #+#             */
/*   Updated: 2023/05/10 11:32:21 by chaikney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Locates the first occurrence of the null-terminated string *needle* in the
// string *haystack*, where not more than *len* characters are searched.
// Characters that appear after a `\0' character are not searched.
// If needle is an empty string, haystack is returned;
// if needle occurs nowhere in haystack, NULL is returned;
// otherwise returns a pointer to
// the first character of the first occurrence of needle.
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char				*here;
	unsigned int		needlength;
	unsigned int		i;

	i = 0;
	if (*needle == '\0')
		return ((char *)(haystack));
	here = ft_strchr(haystack, needle[0]);
	needlength = ft_strlen(needle);
	if ((here == NULL) || (needlength > len) \
			|| (*haystack == '\0'))
		return (NULL);
	while ((*haystack != '\0') && ((len - needlength) >= i))
	{
		if ((haystack[0] == needle[0]) && \
				(ft_strncmp(haystack, needle, needlength) == 0))
			return ((char *)(haystack));
		haystack++;
		i++;
	}
	return (NULL);
}
