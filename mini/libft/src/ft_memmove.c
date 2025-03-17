/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:13:04 by mchiaram          #+#    #+#             */
/*   Updated: 2024/01/29 17:25:12 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	if (!dest || !src)
		return (NULL);
	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	if (ptr_dest == ptr_src)
		return (dest);
	if (ptr_dest < ptr_src)
	{
		while (n-- > 0)
			*(ptr_dest++) = *(ptr_src++);
	}
	else
	{
		ptr_dest += n;
		ptr_src += n;
		while (n > 0)
		{
			*(--ptr_dest) = *(--ptr_src);
			n--;
		}
	}
	return (dest);
}

/*int	main(int argc, char *argv[])
{
	char	dest[50];
	
	if (argc == 4)
	{
		ft_memcpy(dest, argv[1], (ft_strlen(argv[1]) + 1));
		printf("moved %s bytes of %s into %s\n\n", argv[3], argv[2], dest);
		ft_memmove(dest, argv[2], ft_atoi(argv[3]));
		printf("ft_memmove: %s\n", dest);
		memcpy(dest, argv[1], (ft_strlen(argv[1]) + 1));
		memmove(dest, argv[2], ft_atoi(argv[3]));
		printf("memmove: %s", dest);
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---

	The  memmove() function copies n bytes from memory
	area src to memory area dest.
	
	The memory areas may overlap: copying takes place as though the bytes in
	src are first copied into a temporary array that does not
	overlap src or dest,
	and the bytes are then copied from the temporary array to dest.

	---RETURN VALUE---
    The memcpy() function returns a pointer to dest.
*/