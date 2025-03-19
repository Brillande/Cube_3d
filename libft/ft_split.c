/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaikney <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:46:46 by chaikney          #+#    #+#             */
/*   Updated: 2023/05/18 13:38:20 by chaikney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*chop_this(char const *s, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (len == 0)
		return (NULL);
	sub = malloc((len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	while (i < (len))
	{
		sub[i] = s[i];
		i++;
	}
	sub[len] = '\0';
	return (sub);
}

static int	getnumberofwords(char const *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			words++;
		while ((s[i] != '\0') && (s[i] != c))
			i++;
	}
	return (words);
}

static void	tidy_up(char **arr, int n)
{
	while (--n >= 0)
		free (arr[n]);
}

static int	add_word(const char *str, int len, int wordtoadd, char **retstrings)
{
	char	*word;

	word = chop_this(str, len);
	if (word == NULL)
	{
		free (word);
		return (tidy_up (retstrings, wordtoadd), -1);
	}
	else
		retstrings[wordtoadd] = word;
	return (wordtoadd + 1);
}

// Allocates and returns an array of strings obtained
// by splitting ’s’ using the character ’c’ as a delimiter.
// The array must end with a NULL pointer.
// s: The string to be split.
// c: The delimiter character.
// Return: The array of new strings resulting from the split.
//	 - NULL if the allocation fails.
char	**ft_split(char const *s, char c)
{
	char	**retstrings;
	int		i;
	int		j;
	int		wordtoadd;

	wordtoadd = 0;
	i = 0;
	retstrings = malloc((getnumberofwords(s, c) + 1) * sizeof(char *));
	if (!retstrings)
		return (NULL);
	while ((s[i] != '\0'))
	{
		while (s[i] == c)
			i++;
		j = i;
		while ((s[i] != '\0') && (s[i] != c))
			i++;
		if (i > j)
			wordtoadd = add_word((s + j), (i - j), wordtoadd, retstrings);
		if (wordtoadd == -1)
			return (free(retstrings), NULL);
	}
	retstrings[wordtoadd] = NULL;
	return (retstrings);
}
