/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:58:40 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/30 13:57:52 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (16384);
	return (0);
}

/*int	main(void)
{
	unsigned char	c;

	c = 30;
	printf("ft_isprint:\n");
	while (c <= 37)
	{
		printf("%c result: %d\n", c, ft_isprint(c));
		c++;
	}
	c = 30;
	printf("isprint:\n");
	while (c <= 37)
	{
		printf("%c result: %d\n", c, isprint(c));
		c++;
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---

	This function checks for any printable character including space.
	
	---RETURN VALUE---
    The values returned are nonzero if the character c falls into the
	tested class, and zero if not.
*/