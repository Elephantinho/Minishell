/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:58:24 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/30 17:31:43 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (ptr);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

/*				---MAN DESCRIPTION---

	The calloc() function allocates memory for an array of nmemb elements
	of size bytes each and returns a pointer to the allocated memory.
	
	The memory is set to zero.
	
	---RETURN VALUE---
	If nmemb or size is 0, then calloc() returns either NULL,
	or a unique pointer value that can later be successfully passed to free().
	
	If the multiplication of nmemb and size would result in integer overflow,
	then calloc() returns an error.
*/