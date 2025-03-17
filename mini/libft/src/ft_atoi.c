/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:50:15 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/30 16:46:05 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	base;
	int	sign;
	int	i;

	if (!nptr)
		return (0);
	base = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		base = base * 10 + (nptr[i] - '0');
		i++;
	}
	return (base * sign);
}

/*int	main(int argc, char *argv[])
{
	if (argc == 2)
	{
		printf("converted %s from char to int:\n\n", argv[1]);
		printf("ft_atoi: %d\n", ft_atoi(argv[1]));
		printf("atoi: %d", atoi(argv[1]));
	}
}*/

/*				---MAN DESCRIPTION---

	The atoi() function converts the initial portion of
	the string pointed to by nptr to int.

	---RETURN VALUE---
    The converted value.
*/