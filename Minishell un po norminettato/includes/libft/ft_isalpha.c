/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:51:37 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/18 16:52:20 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	int	i;

	i = 0;
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
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
	n = ft_isalpha((int)argv[1][0]);
	m = isalpha((int)argv[1][0]);
	printf("%d\n", n);
	printf("%d\n", m);
	}
	return 0;
}*/
