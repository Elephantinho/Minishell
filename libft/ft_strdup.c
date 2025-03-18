/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 23:22:06 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/22 17:03:40 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*new;

	i = 0;
	new = (char *)malloc(ft_strlen(src) * sizeof(char) + 1);
	if (!new)
		return (NULL);
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
/*
int	main()
{
	const char *str = "holaa";
	char *copy = ft_strdup(str);
	char *copy1 = strdup(str);
	printf("%s\n", copy);
	printf("%s\n", copy1);
	return (0);
}*/
