/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:15:09 by mchiaram          #+#    #+#             */
/*   Updated: 2024/10/22 14:20:08 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *) s);
		s++;
	}
	if (*s == (char)c)
		return ((char *) s);
	return (NULL);
}

/*int	main(int argc, char *argv[])
{
	if (argc == 3)
	{
		printf("First occurence of %c in %s:\n\n", argv[2][0], argv[1]);
		printf("ft_strchr: %s\n", ft_strchr(argv[1], argv[2][0]));
		printf("strchr: %s", strchr(argv[1], argv[2][0]));
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---

	The strchr() function returns a pointer to the first
	occurrence of the character c in the string s.

	---RETURN VALUE---
	The  strchr() function returns a pointer to the matched
	character or NULL if the character is not found.
	The terminating null byte is considered part of the string,
	so that if c is specified as '\0',
	this function returns a pointer to the terminator.
*/