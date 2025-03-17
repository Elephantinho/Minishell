/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:50:21 by mchiaram          #+#    #+#             */
/*   Updated: 2024/03/21 14:50:56 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ptrdigitcount(uintptr_t n)
{
	size_t			ndigits;

	ndigits = 0;
	if (n == 0)
		return (5);
	while (n > 0)
	{
		ndigits++;
		n /= 16;
	}
	return (ndigits);
}

static void	ft_printptr(uintptr_t num)
{
	if (num > 15)
	{
		ft_printptr(num / 16);
		ft_printptr(num % 16);
	}
	else if (num < 10)
		ft_putchar_fd(num + '0', 1);
	else
		ft_putchar_fd(num - 10 + 'a', 1);
}

int	ft_putptr(void *ptr)
{
	uintptr_t	num;
	size_t		nchar;

	num = (uintptr_t)ptr;
	if (num == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	nchar = 2;
	write(1, "0x", 2);
	ft_printptr(num);
	nchar += ft_ptrdigitcount(num);
	return (nchar);
}
