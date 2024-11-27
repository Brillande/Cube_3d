/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:29:59 by emedina-          #+#    #+#             */
/*   Updated: 2023/07/07 10:19:35 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_choice(va_list ap, char *str, size_t *counter)
{
	if (*str == 'c')
		ft_putchar_counter(va_arg(ap, int), counter);
	else if (*str == 's')
		ft_putstr_counter(va_arg(ap, char *), counter);
	else if (*str == 'p')
		ft_putptr_counter(va_arg(ap, void *), counter);
	else if (*str == 'i' || *str == 'd')
		ft_putnbr_counter(va_arg(ap, int), counter);
	else if (*str == 'u')
		ft_putunsignedint_counter(va_arg(ap, unsigned int), counter);
	else if (*str == 'x' || *str == 'X')
	{
		if (*str == 'x')
			ft_puthex_counter(va_arg(ap, unsigned int), counter, HEX_LOW_BASE);
		else
			ft_puthex_counter(va_arg(ap, unsigned int), counter, HEX_UPP_BASE);
	}
	else if (*str == '%')
		ft_putchar_counter(*str, counter);
}

int	ft_printf(char const *str, ...)
{
	va_list	ap;
	size_t	counter;

	if (!str)
		return (0);
	counter = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			ft_choice(ap, (char *)str, &counter);
		}
		else
			ft_putchar_counter(*str, &counter);
		str++;
	}
	va_end(ap);
	return (counter);
}

/* int	main(void)
{
	ft_printf("Caracter: %c\n", 'A');
	printf("Caracter: %c\n", 'A');
	ft_printf("Cadena: %s\n", "Hola, mundo!");
	printf("Cadena: %s\n", "Hola, mundo!");
	ft_printf("Puntero: %p\n", main);
	printf("Puntero: %p\n", main);
	ft_printf("Entero: %u\n", 123456);
	printf("Entero: %u\n", 123456);
	ft_printf("Hexadecimal (minúsculas): %x\n", 245);
	printf("Hexadecimal (minúsculas): %x\n", 245);
	ft_printf("Hexadecimal (mayúsculas): %X\n", 245);
	printf("Hexadecimal (mayúsculas): %X\n", 245);
	ft_printf("Porcentaje: %%\n");
	printf("Porcentaje: %%\n");
	ft_printf("numero positivo %i\n", 33);
	ft_printf("numero negativo %d\n", -44);
	printf("numero positivo %i\n", 33);
	printf("numero negativo %d\n", -44);
	return (0);
}
 */