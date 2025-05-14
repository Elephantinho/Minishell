/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:17:09 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/25 20:51:00 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (0);
	if (dest > src)
	{
		while (n-- > 0)
			((unsigned char *)dest)[n] = ((const unsigned char *)src)[n];
	}
	else
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	{
	char	sr[32] = "";
	char	des[13] = "";
	char	*d;
	//des = sr - 3;
	d = memmove(des, sr, 5);
	printf("%s\n", d);
	printf("%s\n", sr);
	}
	{
	char	sr1[] = "12345678";
	//char	des1[5];
	char	*d1;
	d1 = memmove(sr1, sr1, 5);
	printf("%s\n", d1);
	printf("%s\n", sr1);
	}
	return 0;
}*/
