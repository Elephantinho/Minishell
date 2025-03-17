/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:44:14 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/30 13:53:15 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (8);
	return (0);
}

/*int	main(int argc, char *argv[])
{
	unsigned char	c;

	if (argc == 2)
	{
		c = argv[1][0];
		printf("ft_isalnum: %d\n", ft_isalnum(c));
		printf("isalnum: %d", isalnum(c));
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---

	This function checks for an alphanumeric character;
	it is equivalent to (isalpha(c) || isdigit(c)).
	
	---RETURN VALUE---
    The values returned are nonzero if the character c falls into the
	tested class, and zero if not.
*/