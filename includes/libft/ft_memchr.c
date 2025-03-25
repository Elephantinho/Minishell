/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:56:06 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/25 18:15:25 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*st;
	unsigned char		c1;

	c1 = (unsigned char)c;
	st = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*st == c1)
			return (st);
		st++;
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	{
	char	c = 0;
	char	st[] = "ciao";
	char	*st1;

	st[2]= 2;
	st1 = ft_memchr(st, c + 256, 3);
	printf("%s\n", st);
	printf("%s\n", st1);
	}
	{
	char	c = 0;
	char	st[] = "ciao";
	char	*st1;

	st[2]= 2;
	st1 = memchr(st, c + 256, 3);
	printf("%s\n", st);
	printf("%s\n", st1);
	}
} */
