/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:35:24 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/29 23:10:32 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

int	ft_putptr1(unsigned long nb)
{
	char	nb_char;
	int		count;

	count = 0;
	if (nb > 15)
		count += ft_putptr1(nb / 16);
	nb = nb % 16;
	if (nb <= 9)
		nb_char = (nb % 10) + '0';
	else
		nb_char = (nb % 16) - 10 + 'a';
	write(1, &nb_char, 1);
	count++;
	return (count);
}

int	ft_putptr(unsigned long p)
{
	int	count;

	count = 0;
	if (p == 0)
	{
		count += ft_putstr("(nil)");
		return (count);
	}
	else
	{
		count += ft_putstr("0x");
		count += ft_putptr1((unsigned long) p);
	}
	return (count);
}

int	ft_putnbr_x(unsigned int nb, char c)
{
	int		count;

	count = 0;
	if (nb > 15)
		count += ft_putnbr_x(nb / 16, c);
	nb = nb % 16;
	if (nb <= 9)
		count += ft_putchar((nb % 10) + '0');
	else
	{
		if (c == 'x')
			count += ft_putchar((nb % 16) - 10 + 'a');
		else
			count += ft_putchar((nb % 16) - 10 + 'A');
	}
	return (count);
}

int	ft_printf1(va_list args, const char *str, int *flag)
{
	int	count;

	count = 0;
	if (*str == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (*str == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (*str == 'p')
		count += ft_putptr((unsigned long)va_arg(args, void *));
	else if (*str == 'd' || *str == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (*str == 'u')
		count += ft_putnbr_u(va_arg(args, unsigned int));
	else if (*str == 'x' || *str == 'X')
		count += ft_putnbr_x(va_arg(args, unsigned int), *str);
	else if (*str == '%')
		count += ft_putchar('%');
	else
		*flag = 1;
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		flag;

	flag = 0;
	if (str == NULL)
		return (-1);
	count = 0;
	va_start(args, str);
	while (*str != 0)
	{
		if (*str == '%')
		{
			str++;
			count += ft_printf1(args, str, &flag);
		}
		else
			count += ft_putchar(*str);
		if (*str != '\0')
			str++;
	}
	va_end(args);
	if (flag == 1)
		return (-1);
	return (count);
}
/*
#include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
#include <limits.h>
int	main()
{
	//char s[] = "ciao";
	//void *p = &s;
	//int k = 1;

	// test generale semplice a capo per norminette
	int i = ft_printf("ciao %");
	printf("%d\n", i);
	int j = printf("ciao %");
	printf("%d\n", j);

	return (0);
} */
