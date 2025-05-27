/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:01:19 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/30 19:08:42 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putnbr(int nb)
{
	char	nb_char;
	int		count;

	count = 0;
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (nb < 0)
	{
		nb = -nb;
		write(1, "-", 1);
		count++;
	}
	if (nb > 9)
	{
		count += ft_putnbr(nb / 10);
	}
	nb_char = (nb % 10) + '0';
	write(1, &nb_char, 1);
	count++;
	return (count);
}

int	ft_putnbr_u(unsigned int nb)
{
	char	nb_char;
	int		count;

	count = 0;
	if (nb > 9)
	{
		count += ft_putnbr(nb / 10);
	}
	nb_char = (nb % 10) + '0';
	write(1, &nb_char, 1);
	count++;
	return (count);
}

int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*str != '\0')
	{
		write(1, str, 1);
		count++;
		str++;
	}
	return (count);
}
