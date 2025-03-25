/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:09:36 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/21 00:10:18 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*sub_str;
	size_t	count;

	i = 0;
	count = 0;
	if (*little == '\0')
		return ((char *)big);
	while (*big != '\0' && count < len)
	{
		i = 0;
		sub_str = (char *)big;
		while (big[i] == little[i] && (count + i) < len)
		{
			if (little[i + 1] == '\0')
				return ((char *)sub_str);
			i++;
		}
		big++;
		count++;
	}
	return (0);
}
/*
#include <string.h>
#include <stdio.h>	
int	main(void)
{
	char	st[] = "holla";
	char	find[] = "lla";
	char	st1[] = "holla";
	char	find1[] = "lla";
	char	*substring;
	char	*substring1;
	
	substring = ft_strnstr(st, find, 6);
	substring1 = strstr(st1, find1);

	printf("%s\n", substring);
	printf("%s", substring1);
	return (0);
}*/
