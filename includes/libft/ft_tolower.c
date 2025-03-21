/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:12:56 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/20 00:15:17 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}
/*#include <ctype.h>
#include <stdio.h>
int	main()
{
	char	c = 'z';

	printf("%c\n", c);
	c = ft_tolower(c);
	char c1 = ft_tolower(c);
	printf("%c\n", c);
	printf("%d\n", c1);
	return 0;
}*/
