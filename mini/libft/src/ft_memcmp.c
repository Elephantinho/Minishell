/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:29:58 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/30 16:35:48 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr_s1;
	unsigned char	*ptr_s2;

	if (!s1 || !s2 || n == 0)
		return (0);
	ptr_s1 = (unsigned char *)s1;
	ptr_s2 = (unsigned char *)s2;
	while (--n)
	{
		if (*ptr_s1 != *ptr_s2)
			break ;
		ptr_s1++;
		ptr_s2++;
	}
	return (*ptr_s1 - *ptr_s2);
}

/*int	main(int argc, char *argv[])
{
	unsigned char	*s1;
	unsigned char	*s2;
	
	if (argc == 4)
	{
		s1 = (unsigned char *)argv[1];
		s2 = (unsigned char *)argv[2];
		printf("comparison between %s and %s:\n\n", ft_atoi(argv[3]), s1, s2);
		printf("ft_memcmp: %d\n", ft_memcmp(s1, s2, ft_atoi(argv[3])));
		printf("memcmp: %d", memcmp(s1, s2, ft_atoi(argv[3])));
	}
}*/

/*				---MAN DESCRIPTION---

	The memcmp() function compares the first n bytes 
	(each interpreted as unsigned char) of the memory areas s1 and s2.

	---RETURN VALUE---
	The  memcmp() function returns an integer less than, equal to, or greater
	than zero if the first n bytes of s1 is found, respectively,
	to be less than, to match, or be greater than the first n bytes of s2.

	For a nonzero return value, the sign is determined by the sign of the
	difference between the first pair of bytes (interpreted as unsigned char)
	that differ in s1 and s2.

    If n is zero, the return value is zero.
*/