/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:31:31 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/18 17:32:08 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	int	i;

	i = 0;
	if (c >= 0 && c <= 127)
		i = 1;
	return (i);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main()
{
	int	st = 200;
	int     n,m;

	printf("char is: %c\n", st);
	n = ft_isascii(st);
	m = isascii(st);
	printf("%d\n", n);
	printf("%d\n", m);
	return 0;
}*/
