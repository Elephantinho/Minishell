/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:45:01 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/30 12:25:49 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr_dest;
	const unsigned char	*ptr_src;

	if (dest && src)
	{
		ptr_dest = (unsigned char *)dest;
		ptr_src = (const unsigned char *)src;
		if (ptr_dest == ptr_src)
			return (dest);
		while (n != 0)
		{
			*(ptr_dest++) = *(ptr_src++);
			n--;
		}
	}
	return (dest);
}

/*int	main(int argc, char *argv[])
{
	char	dest[50];
	int		slen;
	
	if (argc == 4)
	{
		slen = ft_strlen(argv[1]);
		ft_memcpy(dest, argv[1], (slen + 1));
		printf("copied %s bytes of %s into %s\n\n", argv[3], argv[2], dest);
		ft_memcpy(dest, argv[2], ft_atoi(argv[3]));
		printf("ft_memcpy: %s\n", dest);
		memcpy(dest, argv[1], (slen + 1));
		memcpy(dest, argv[2], ft_atoi(argv[3]));
		printf("memcpy: %s", dest);
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---

	The memcpy() function copies n bytes from memory area src 
	to memory area dest.
	
	The memory areas must not overlap.
	Use memmove(3) if the memory areas do overlap.

	---RETURN VALUE---
    The memcpy() function returns a pointer to dest.
*/