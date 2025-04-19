/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:17:55 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/19 23:21:30 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}
/*
forse da ricontrollare e anche tolower
#include <ctype.h>
#include <stdio.h>
int	main()
{
	char	c = 0;

	printf("%c\n", c);
	c = ft_toupper(c);
	char c1 = ft_toupper(c);
	printf("%c\n", c);
	printf("%c\n", c1);
	return 0;
}*/
