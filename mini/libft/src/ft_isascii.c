/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:51:53 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/30 13:58:28 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*int	main(void)
{
	unsigned char	c;

	c = 125;
	printf("ft_isascii:\n");
	while (c <= 129)
	{
		printf("%c result: %d\n", c, ft_isascii(c));
		c++;
	}
	c = 125;
	printf("\nisascii:\n");
	while (c <= 129)
	{
		printf("%c result: %d\n", c, isascii(c));
		c++;
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---

	This function checks whether c is a 7-bit unsigned 
	char value that fits into the ASCII character set.
	
	---RETURN VALUE---
    The values returned are nonzero if the character c falls into the
	tested class, and zero if not.
*/