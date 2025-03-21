/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:32:08 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/25 20:08:33 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	c1;

	c1 = c;
	i = ft_strlen(s);
	if (c1 == '\0')
		return ((char *)&s[i]);
	i--;
	while (i >= 0)
	{
		if (s[i] == c1)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	{
	char	c = 'c';
	char	*st = "ciaociao";
	char	*st1;

	st1 = ft_strrchr(st, c);
	printf("%s\n", st);
	printf("%s\n", st1);
	}
	{
	char	c = 'c';
	char	*st = "ciaociao";
	char	*st1;

	st1 = strrchr(st, c);
	printf("%s\n", st);
	printf("%s\n", st1);
	}
}*/
