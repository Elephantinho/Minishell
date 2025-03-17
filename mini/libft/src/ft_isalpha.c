/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:04:28 by mchiaram          #+#    #+#             */
/*   Updated: 2024/06/21 11:26:55 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1024);
	return (0);
}

/*int	main(int argc, char *argv[])
{
	unsigned char	c;
	
	if (argc == 2)
	{
		c = argv[1][0];
		printf("ft_isalpha: %d\n", ft_isalpha(c));
		printf("isalpha: %d\n", isalpha(c));
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---

	This function checks for an alphabetic character.
	
	---RETURN VALUE---
    The values returned are nonzero if the character c falls into the
	tested class, and zero if not.
*/