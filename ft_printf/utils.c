/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:04:52 by emedina-          #+#    #+#             */
/*   Updated: 2023/07/07 00:38:34 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_counter(char c, size_t *counter)
{
	write(1, &c, 1);
	(*counter)++;
}

void	ft_putnbr_counter(int n, size_t *counter)
{
	if (n == INT_MIN)
	{
		ft_putnbr_counter((n / 10), counter);
		ft_putchar_counter((-(n % 10) + '0'), counter);
	}
	else if (n < 0)
	{
		ft_putchar_counter('-', counter);
		ft_putnbr_counter(-n, counter);
	}
	else
	{
		if (n > 9)
			ft_putnbr_counter((n / 10), counter);
		ft_putchar_counter((n % 10 + '0'), counter);
	}
}

void	ft_putstr_counter(char *str, size_t *counter)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		ft_putchar_counter(*str, counter);
		str++;
	}
}

void	ft_putptr_counter(void *ptr, size_t *counter)
{
	char				*str;
	long unsigned int	ptr_of_ptr;

	ptr_of_ptr = (long unsigned int)ptr;
	ft_putstr_counter("0x", counter);
	str = ft_aux(ptr_of_ptr, HEX_LOW_BASE);
	ft_putstr_counter(str, counter);
	free(str);
}

void	ft_putunsignedint_counter(unsigned int n, size_t *counter)
{
	char	*str;

	str = ft_aux(n, "0123456789");
	ft_putstr_counter(str, counter);
	free(str);
}
