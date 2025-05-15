/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:31:45 by ade-ross          #+#    #+#             */
/*   Updated: 2025/04/14 01:01:41 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}
/*
#include <string.h>
#include <stdio.h>
int	main()
{
	const char *st = "ciaoo";

	size_t l = ft_strlen(st);
	size_t n = strlen(st);
	printf("%zu", l);
	printf("%zu", n);
	return 0;
}*/
