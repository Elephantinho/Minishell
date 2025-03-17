/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:14:53 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/30 16:08:44 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	while (i >= 0)
	{
		if (*s == (char)c)
			return ((char *) s);
		s--;
		i--;
	}
	return (NULL);
}

/*int	main(int argc, char *argv[])
{
	if (argc == 3)
	{
		printf("Last occurence of %c in %s:\n\n", argv[2][0], argv[1]);
		printf("ft_strrchr: %s\n", ft_strrchr(argv[1], argv[2][0]));
		printf("strrchr: %s", strrchr(argv[1], argv[2][0]));
	}
}*/

/*				---MAN DESCRIPTION---
	The strrchr() function returns a pointer to the last
	occurrence of the character c in the string s.

	---RETURN VALUE---
	The () function returns a pointer to the matched character
	or NULL if the character is not found.
	The terminating null byte is considered part of the string,
	so that if c is specified as '\0',
	this function returns a pointer to the terminator.
*/