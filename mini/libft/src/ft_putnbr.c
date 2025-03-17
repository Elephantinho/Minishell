/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:53:31 by mchiaram          #+#    #+#             */
/*   Updated: 2024/03/21 14:51:25 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putunsigned(int n)
{
	unsigned int	nbr;
	char			c;

	nbr = (unsigned int)n;
	if (nbr > 9)
	{
		ft_putunsigned(nbr / 10);
		ft_putunsigned(nbr % 10);
	}
	if (nbr <= 9)
	{
		c = (nbr + '0');
		write(1, &c, 1);
	}
}

static void	ft_putnbr(int n)
{
	long int		nbr;
	char			c;

	nbr = (long int)n;
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr *= -1;
	}
	if (nbr > 9)
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
	if (nbr <= 9)
	{
		c = (nbr + '0');
		write(1, &c, 1);
	}
}

int	ft_printnbr(int nbr, char c)
{
	if (c == 'u')
		ft_putunsigned(nbr);
	else
		ft_putnbr(nbr);
	return (ft_digits_count(nbr, c));
}
