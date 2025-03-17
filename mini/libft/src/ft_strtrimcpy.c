/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimcpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:10:33 by mchiaram          #+#    #+#             */
/*   Updated: 2025/01/30 14:45:08 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrimcpy(char *dst, const char *src, size_t size)
{
	size_t	offset;

	if (!src || size == 0)
		return (NULL);
	offset = 0;
	while (*src && (*src == ' '
			|| *src == '\t' || *src == '\n'))
		src++;
	dst = ft_calloc(size + 1, sizeof(char));
	while (src && offset < (size))
	{
		dst[offset++] = *src++;
	}
	return (dst);
}
