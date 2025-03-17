/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:21:54 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/31 15:34:23 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;

	if (!s)
		return (NULL);
	ptr = (unsigned char *)s;
	while (n != 0)
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		ptr++;
		n--;
	}
	return (NULL);
}

/*int	main(int argc, char *argv[])
{
	unsigned char	*str;
	
	if (argc == 4)
	{
		str = (unsigned char*)argv[1];
		printf("First occurence of %c in %s:\n", argv[2][0], argv[1]);
		printf("ft_memchr: %p\n", ft_memchr(str, argv[2][0], ft_atoi(argv[3])));
		printf("memchr: %p", memchr(str, argv[2][0], ft_atoi(argv[3])));
	}
}*/
/*				---MAN DESCRIPTION---

	The memchr() function scans the initial n bytes of the
	memory area pointed to by s for the first instance of c.
	Both c and the bytes of the memory area pointed to by s
	are interpreted as unsigned char.

	---RETURN VALUE---
	The memchr() function returns a pointer to the matching byte
	or NULL if the character does not occur in the given memory area.
*/