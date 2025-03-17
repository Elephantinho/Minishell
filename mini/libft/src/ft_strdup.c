/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:28:47 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:38:37 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s1;
	int		i;

	if (!s)
		return (NULL);
	s1 = ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (!s1)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		s1[i] = s[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

/*int	main(int argc, char *argv[])
{
	if (argc == 2)
	{
		printf("duplicated the string %s:\n\n", argv[1]);
		printf("ft_strdup: %s\n", ft_strdup(argv[1]));
		printf("strdup: %s", strdup(argv[1]));
	}
}*/

/*				---MAN DESCRIPTION---
	The strdup() function returns a pointer to a new string which is
	a duplicate of the string s.
	
	Memory for the new string is obtained with malloc(3),
	and can be freed with free(3).
	
	---RETURN VALUE---
	On success, the strdup() function returns a pointer to the duplicated string.
	It returns NULL if insufficient memory was available,
	with errno set to indicate the cause of the error.
*/