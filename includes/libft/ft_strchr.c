/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:38:52 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/25 18:11:14 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	c1;

	i = 0;
	c1 = (unsigned char )c;
	while (s[i] != '\0')
	{
		if (s[i] == c1)
			return ((char *)&s[i]);
		i++;
	}
	if (c1 == '\0')
		return ((char *)&s[i]);
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	{
	//char	c = 'i';
	char	*st = "ciaotciao";
	char	*st1;

	st1 = ft_strchr(st, 't' + 256);
	printf("%s\n", st);
	printf("%s\n", st1);
	}
	{
	//char	c = 'i';
	char	*st = "ciaotciao";
	char	*st1;

	st1 = strchr(st, 't' + 256);
	printf("%s\n", st);
	printf("%s\n", st1);
	}
} */
