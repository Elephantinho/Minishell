/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:18:27 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/30 14:01:39 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	size;

	if (!s)
		return (0);
	size = 0;
	while (s[size])
		size++;
	return (size);
}

/*int	main(int argc, char *argv[])
{
	if (argc == 2)
	{
		printf("Length of the string %s\n\n", argv[1]);
		printf("ft_strlen: %ld\n", ft_strlen(argv[1]));
		printf("strlen: %ld", strlen(argv[1]));
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---
	The strlen() function calculates the length of the string
	pointed to by s, excluding the terminating null byte ('\0').

	---RETURN VALUE---
    The strlen() function returns the number of bytes in the
	string pointed to by s.
*/