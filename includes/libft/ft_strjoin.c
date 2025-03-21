/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:35:42 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/26 00:27:20 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newst;
	int		i;

	i = 0;
	newst = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!newst)
		return (0);
	while (*s1 != '\0')
	{
		newst[i] = *s1;
		i++;
		s1++;
	}
	while (*s2 != '\0')
	{
		newst[i] = *s2;
		i++;
		s2++;
	}
	newst[i] = '\0';
	return (newst);
}
/*
int main()
{
	char	s1[] = "lorem ipsum";
	char	s2[] = "dolor sit amet";

	char	*st = ft_strjoin(s1, s2);
	printf("%s\n", st);
} */
