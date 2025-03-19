/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaikney <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:36:08 by chaikney          #+#    #+#             */
/*   Updated: 2023/04/24 10:37:31 by chaikney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns 1 if the char c is a digit or alphabetical.
// Return 0 otherwise.
// (As determined by ft_isascii|alpha|digit)
int	ft_isalnum(int c)
{
	int	retcode;

	retcode = 0;
	if (ft_isascii(c) == 1)
	{
		if ((ft_isalpha(c) == 1) || (ft_isdigit(c) == 1))
			retcode = 1;
		else
			retcode = 0;
	}
	return (retcode);
}
