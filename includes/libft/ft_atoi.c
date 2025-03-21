/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:01:55 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/19 18:02:08 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	nb;

	sign = 1;
	nb = 0;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = (nb * 10) + (*nptr - 48);
		nptr++;
	}
	nb = sign * nb;
	return (nb);
}
/*
#include <stdlib.h>
#include <stdio.h>
int	main(void)
{
	const char	*string = "-5675858";
	int	i, j;
	i = ft_atoi(string);
	j = atoi(string);
	printf("%d\n", i);
	printf("%d\n", j);
	return (0);
}*/
