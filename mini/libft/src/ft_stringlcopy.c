/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringlcopy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:27:37 by mchiaram          #+#    #+#             */
/*   Updated: 2024/10/22 12:17:41 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stringlcopy(char *dst, const char *src, size_t size)
{
	size_t	offset;

	if (!src || !size)
		return (NULL);
	dst = ft_calloc((size + 1), sizeof(char));
	offset = 0;
	while (*(src + offset) != '\0' && offset < (size))
	{
		*(dst + offset) = *(src + offset);
		offset++;
	}
	return (dst);
}
