/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:27:59 by ade-ross          #+#    #+#             */
/*   Updated: 2024/12/18 22:09:03 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;
	int		tot;

	tot = nmemb * size;
	if (nmemb == 0 || size == 0 || (tot / size != nmemb))
	{
		return (malloc(0));
	}
	arr = malloc(nmemb * size);
	if (!(arr))
	{
		return (0);
	}
	return (ft_memset(arr, 0, (nmemb * size)));
}
/*
int	main()
{
	char *try = calloc(10, sizeof(int));
	char *try2 = ft_calloc(10, 2);
	for (int i =0; i <15; i++)
				printf("%c", try[i]);
	for (int i =0; i <15; i++)
				printf("%c", try2[i]);
	return (0);
}*/
