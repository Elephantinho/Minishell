/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:38:31 by mchiaram          #+#    #+#             */
/*   Updated: 2024/03/21 14:49:56 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printhex(unsigned int num, char c)
{
	if (num == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	if (num > 15)
	{
		ft_printhex(num / 16, c);
		ft_printhex(num % 16, c);
	}
	else if (num < 10)
		ft_putchar_fd(num + '0', 1);
	else
	{
		if (c == 'x')
			ft_putchar_fd(num - 10 + 'a', 1);
		else
			ft_putchar_fd(num - 10 + 'A', 1);
	}
	return (ft_ptrdigitcount(num));
}

static int	ft_putstr(char *str)
{
	size_t	nchar;

	nchar = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*str)
	{
		ft_putchar_fd(*str++, 1);
		nchar++;
	}
	return (nchar);
}

size_t	ft_digits_count(long int n, char c)
{
	size_t	ndigits;
	int		div;

	ndigits = 0;
	div = 10;
	if (c == 'x' || c == 'X' || c == 'p')
		div = 16;
	if (n == 0)
		return (1);
	if (c == 'u')
		n = (unsigned int)n;
	else if (n < 0)
	{
		ndigits++;
		n *= -1;
	}
	while (n > 0)
	{
		ndigits++;
		n /= div;
	}
	return (ndigits);
}

static int	ft_printparam(char c, va_list args)
{
	if (c == 'c')
		ft_putchar_fd(va_arg(args, int), 1);
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_putptr(va_arg(args, void *)));
	else if (c == 'i' || c == 'd')
		return (ft_printnbr(va_arg(args, int), c));
	else if (c == 'u')
		return (ft_printnbr(va_arg(args, unsigned int), c));
	else if (c == 'x' || c == 'X')
		return (ft_printhex(va_arg(args, unsigned int), c));
	else
		ft_putchar_fd(c, 1);
	return (1);
}

int	ft_printf(const char *str, ...)
{
	int		nchar;
	va_list	args;

	nchar = 0;
	va_start(args, str);
	if (!str || *str == '\0')
		return (0);
	while (*str)
	{
		if (*str == '%' && *(str + 1) != '\0')
		{
			nchar += ft_printparam(*++str, args);
			str++;
		}
		if (*str != '%' && *str != '\0')
		{
			ft_putchar_fd(*str++, 1);
			nchar++;
		}
	}
	va_end(args);
	return (nchar);
}
