/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:57:32 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/19 16:58:05 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *) s)[i] = '\0';
		i++;
	}
}
/*
#include <unistd.h>
int	main()
{
	char	s[14] = "CIAO.Ciao ciao";

	ft_bzero (s, 5);
	size_t i = 0;
	while (i < 14)
	{
		write(1, &s[i], 1);
		i++;
	}
	return 0;
}*/
