/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 22:24:45 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/19 22:25:06 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dst);
	i = 0;
	if (size <= dest_len)
		return (size + src_len);
	while (src[i] != '\0' && (dest_len + i) < (size - 1))
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}
/*
//FORSE VA RIGUARDATA NON SO SE FUNZIONA COME 
//L'ORIGINALE
#include <stdio.h>
#include <string.h>
int	main()
{
	char	src[] = "damnn";
	char	dest[16] = "damndouble";
	size_t	n = 13;
	int	i;
	
	i = ft_strlcat(dest, src, n);
	printf("%d\n", i);
	printf("%s\n", dest);
	
	return (0);
}*/
