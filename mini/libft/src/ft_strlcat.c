/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:53:17 by mchiaram          #+#    #+#             */
/*   Updated: 2024/01/29 17:24:24 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	res;
	size_t	dstlen;
	size_t	srclen;

	if (!dst || !src)
		return (0);
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	i = 0;
	if (ft_strlen(dst) > size)
		res = srclen + size;
	else
		res = dstlen + srclen;
	while (dst[i])
		i++;
	while (*src && (i + 1) < size)
	{
		dst[i] = *src;
		i++;
		src++;
	}
	dst[i] = '\0';
	return (res);
}

/*int	main(int argc, char *argv[])
{
	char		*dst;
	const char	*src;
	size_t		result;

	dst = argv[1];
	src = argv[2];
	if (argc == 4)
	{
		printf("Dst string before: %s\n", dst);
		printf("Src string to be copied in dst: %s\n", src);
		printf("Size to be copied: %s\n\n", argv[3]);
		result = ft_strlcat(dst, src, ft_atoi(argv[3]));
		printf("New dst string: %s\n", dst);
		printf("Lenght of the string I tried to create: %ld\n", result);
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---

	The strlcat() function concatenates strings. 

	It's designed to be safer, more consistent,
	and less error prone replacements for strncat(3).

	Unlike that function, strlcat() takes the full
	size of the buffer (not just the length) 
	and guarantees to NUL-terminate the result (as long as size is larger
	than 0 or as long as there is at least one byte free in dst).

	Note that a byte for the NUL should be included in size.
	Also note that strlcat() only operates on true “C” strings.
	This means that both src and dst must be NUL-terminated.

	The strlcat() function appends the NUL-terminated string 
	src to the end of dst.
	It will append at most size - strlen(dst) - 1 bytes,
	NUL-terminating the result.

	---RETURN VALUE---
    The strlcat() function returns the total length of the string 
	it tried to create.
	
	For strlcat() that means the initial length of dst plus the length of src.
	While this may seem somewhat confusing, it was done to make truncation
	detection simple.
*/