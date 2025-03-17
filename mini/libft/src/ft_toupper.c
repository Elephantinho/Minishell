/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:15:19 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/30 14:04:40 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

/*int	main(int argc, char *argv[])
{
	unsigned char	c;

	if (argc == 2)
	{
		c = argv[1][0];
		printf("char before the function application: %c\n\n", c);
		printf("ft_toupper: %c\n", ft_toupper(c));
		printf("toupper: %c", toupper(c));
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---
	This function converts lowercase letters to uppercase.

    If c is a lowercase letter, toupper() returns its uppercase equivalent,
	if an uppercase representation exists in the current locale.
	Otherwise, it returns c.

	---RETURN VALUE---
	The value returned is that of the converted letter,
	or c if the conversion was not possible.
*/