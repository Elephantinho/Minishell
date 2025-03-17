/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freelcopy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:38:07 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:38:10 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_freelcopy(char **dst, const char *src, size_t size)
{
	size_t	offset;

	if (!src || !size)
	{
		if (*(dst))
			free (*(dst));
		return (NULL);
	}
	if (*(dst))
		free (*(dst));
	*(dst) = ft_calloc((size + 1), sizeof(char));
	offset = 0;
	while (*(src + offset) != '\0' && offset < (size))
	{
		*(*(dst) + offset) = *(src + offset);
		offset++;
	}
	return (*(dst));
}

/*				---DESCRIPTION---
	The freelcpy() function copies strings freeing the dst string
	(if already exists) before allocating it again.

	Can be used to completely replace the value inside
	the variable dst while freeing its memory

	---RETURN VALUES---
    The freelcpy() function returns the newly allocated
	dst string.
 */