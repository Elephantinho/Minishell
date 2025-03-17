/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:20:23 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/30 14:05:35 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

/*int	main(int argc, char *argv[])
{
	unsigned char	c;

	if (argc == 2)
	{
		c = argv[1][0];
		printf("char before the function application: %c\n\n", c);
		printf("ft_tolower: %c\n", ft_tolower(c));
		printf("tolower: %c", tolower(c));
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---
	This function converts uppercase letters to lowercase.

    If c is an uppercase letter, tolower() returns its lowercase equivalent,
	if a lowercase representation exists in the current locale.
	Otherwise, it returns c.

	---RETURN VALUE---
	The value returned is that of the converted letter,
	or c if the conversion was not possible.
*/