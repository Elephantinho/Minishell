/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:23:37 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/18 17:24:12 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	int	i;

	i = 0;
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		i = 1;
	return (i);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main(int argc, char **argv)
{
	//char	string = 'a';
	int     n,m;

	if (argc >= 2)
	{
	printf("char is: %c\n", argv[1][0]);
	n = ft_isalnum((int)argv[1][0]);
	m = isalnum((int)argv[1][0]);
	printf("%d\n", n);
	printf("%d\n", m);
	}
	return 0;
}*/
