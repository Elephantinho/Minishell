/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:54:32 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/31 15:21:06 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_digitcount(int n)
{
	size_t	ndigits;

	ndigits = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		ndigits++;
		n *= -1;
	}
	while (n != 0)
	{
		ndigits++;
		n /= 10;
	}
	return (ndigits);
}

char	*ft_itoa(int n)
{
	char		*str;
	size_t		ndigits;
	long int	nbr;

	nbr = (long int)n;
	ndigits = ft_digitcount(nbr);
	str = ft_calloc(sizeof(char), (ndigits + 1));
	if (!str)
		return (NULL);
	if (nbr == 0)
		str[0] = '0';
	else if (nbr < 0)
	{
		*str = '-';
		nbr *= -1;
	}
	while (nbr != 0)
	{
		ndigits--;
		*(str + ndigits) = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (str);
}

/*int	main(int argc, char *argv[])
{
	if (argc == 2)
	{
		printf("Converted %s from int to char\n\n", argv[1]);
		printf("ft_itoa %s", ft_itoa(ft_atoi(argv[1])));
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---

	Allocates (with malloc(3)) and returns a string
	representing the integer received as an argument.
	Negative numbers must be handled.
	
	---RETURN VALUE---
	The string representing the integer.
	NULL if the allocation fails.
*/