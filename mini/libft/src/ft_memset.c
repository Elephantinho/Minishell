/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:08:02 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/30 15:01:01 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	if (!s)
		return (NULL);
	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*(ptr++) = (unsigned char)c;
		n--;
	}
	return (s);
}

/*int	main(int argc, char *argv[])
{
	unsigned char	str[50];
	size_t			slen;
	
	if (argc == 4)
	{
		slen = ft_strlen(argv[1]);
		ft_memcpy(str, argv[1], (slen + 1));
		printf("string before function application: %s\n\n", str);
		ft_memset(str, argv[2][0], ft_atoi(argv[3]));
		printf("ft_memset: %s\n", str);
		ft_memcpy(str, argv[1], (slen + 1));
		memset(str, argv[2][0], ft_atoi(argv[3]));
		printf("memset: %s\n", str);
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---
    The memset() function fills the first n bytes of
	the memory area pointed to by s with the constant byte c.

	---RETURN VALUE---
    The memset() function returns a pointer to the memory area s.
*/