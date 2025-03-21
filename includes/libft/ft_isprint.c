/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:48:53 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/18 18:05:01 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	int	i;

	i = 0;
	if (c >= 32 && c <= 126)
		i = 1;
	return (i);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main()
{
	int	string = 32;
	int     n,m;

	printf("char is: %c\n", string);
	n = ft_isprint((int)string);
	m = isprint((int)string);
	printf("%d\n", n);
	printf("%d\n", m);
	return 0;
}*/
