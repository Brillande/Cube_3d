/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:51:17 by emedina-          #+#    #+#             */
/*   Updated: 2023/09/23 16:54:51 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_len(unsigned long long n, char *base)
{
	size_t	len;
	size_t	base_len;

	len = 1;
	base_len = ft_strlen(base);
	while (n >= base_len)
	{
		n /= base_len;
		len++;
	}
	return (len);
}

char	*ft_aux(unsigned long long n, char *base)
{
	char	*str;
	size_t	num_len;
	size_t	base_len;

	base_len = ft_strlen(base);
	num_len = ft_len(n, base);
	str = (char *)malloc((num_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[num_len] = '\0';
	while (num_len > 0)
	{
		num_len--;
		str[num_len] = base[n % base_len];
		n /= base_len;
	}
	return (str);
}

void	ft_puthex_counter(unsigned int n, size_t *counter, char *base)
{
	char	*str;

	str = ft_aux(n, base);
	ft_putstr_counter(str, counter);
	free(str);
}
