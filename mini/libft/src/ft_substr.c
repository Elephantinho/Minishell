/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:17:29 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:39:11 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sstr;
	size_t	slen;
	size_t	i;

	slen = ft_strlen(s);
	if (!s || start > slen)
	{
		sstr = ft_calloc(sizeof(char), 1);
		if (!sstr)
			return (NULL);
		return (sstr);
	}
	if (len > slen)
		len = slen;
	if ((slen - start) < len)
		len = (slen - start);
	sstr = ft_calloc((len + 1), sizeof(char));
	if (!sstr)
		return (NULL);
	len += start;
	i = 0;
	while (s[start] && start < len)
		sstr[i++] = s[start++];
	return (sstr);
}

/*int	main(int argc, char *argv[])
{
	if (argc == 4)
	{
		printf("Crated a substring of %s", argv[1]);
		printf("starting at pos %s and of length %s: \n\n", argv[2], argv[3]);
		printf("ft_substr: %s", ft_substr(argv[1], ft_atoi(argv[2]),
				ft_atoi(argv[3])));
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---
	Allocates (with malloc(3)) and returns a substring
	from the string ’s’.
	
	The substring begins at index ’start’ and is of
	maximum size ’len’.

	---RETURN VALUE---
	The substring.
	NULL if the allocation fails.
*/