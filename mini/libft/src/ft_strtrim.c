/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:31:26 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/30 18:49:57 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	len;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	len = 0;
	while (*s1 != '\0' && ft_strchr(set, *s1) != NULL)
		s1++;
	if (*s1 != '\0')
	{
		while (*s1++ != '\0')
			len++;
		s1 -= 2;
		while (ft_strchr(set, *s1) != NULL && s1--)
			len--;
	}
	str = ft_calloc(sizeof(char), (len + 1));
	if (!str)
		return (NULL);
	while (len != 0)
		str[--len] = *s1--;
	return (str);
}

/*int	main(int argc, char *argv[])
{
	if (argc == 3)
	{
		printf("Trimmed the string %s\n\n", argv[1]);
		printf("ft_strtrim: %s", ft_strtrim(argv[1], argv[2]));
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---

	Allocates (with malloc(3)) and returns a copy of
	’s1’ with the characters specified in ’set’ removed
	from the beginning and the end of the string.

	---RETURN VALUE---
	The trimmed string.
	NULL if the allocation fails.
*/