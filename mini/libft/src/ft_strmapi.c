/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:22:07 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/30 19:32:30 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	if (!s || !f)
		return (NULL);
	str = ft_calloc(sizeof(char), (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	return (str);
}

/*char	extFunct(unsigned int index, char c)
{
	index++;
	return (ft_toupper(c));
}

int	main(int argc, char *argv[])
{
	if (argc == 2)
	{
		printf("Applied the external function to '%s'\n\n", argv[1]);
		printf("ft_strmapi: %s", ft_strmapi(argv[1], extFunct));
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---

	Applies the function ’f’ to each character of the
	string ’s’, and passing its index as first argument
	to create a new string (with malloc(3)) resulting
	from successive applications of ’f’.

	---RETURN VALUE---
	The string created from the successive applications
	of ’f’.
	Returns NULL if the allocation fails.
*/