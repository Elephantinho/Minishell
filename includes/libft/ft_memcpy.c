/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:34:53 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/25 20:52:13 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int	main()
{
	{
	char	sr[] = "fdsf";
	char	des[] = "adsadsa";
	char	*d1;
	size_t	n;

	n = 5;
	d1 = ft_memcpy(des , sr, n);
	printf("%s\n", des);
	printf("%s\n", d1);
	}
	{
	char	sr[] = "fdsf";
	char	des[] = "adsadsa";
	char	*d1;
	size_t	n;

	n = 5;
	d1 = memcpy(des, sr, n);
	printf("%s\n", des);
	printf("%s\n", d1);
	}
	return 0;
}*/
