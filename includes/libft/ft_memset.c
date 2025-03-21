/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:36:02 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/18 18:37:15 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	*st;

	st = (unsigned char *)s;
	c1 = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		st[i] = c1;
		i++;
	}
	return (st);
}
/*
#include <string.h>
#include <stdio.h>
#include <unistd.h>
int	main()
{
	int	st[10];
	char	*s;
	char	*t;
	int	i;

	i = 0;
	while (i < 10)
	{
		printf("%d ", (char) st[i]);
		i++;
	}
	printf("\n\n");

	s = ft_memset(st, 128, sizeof(st));

	i = 0;
	while (i < 10)
	{
		printf("%d ", (char) st[i]);
		i++;
	}
	printf("\n\n");
	
	t = memset(st, 128, sizeof(st));

	i = 0;
	while (i < 10)
	{
		printf("%d ", (char)st[i]);
		i++;
	}
	printf("\n\n");

	i = 3;
	while (i < 8)
	{
		st[i] = 124;
		i++;
	}
	
	i = 0;
	while (i < 10)
	{
		printf("%d ", (char)st[i]);
		i++;
	}
	printf("\n\n");
	
	i = 0;
	while (i < 10)
	{
		printf("%d ", s[i]);
		i++;
	}
	printf("\n\n");
	
	i = 0;
	while (i < 10)
	{
		printf("%d ", t[i]);
		i++;
	}
	
	printf("\n\n");
	return 0; 
}*/
