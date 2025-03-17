/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:15:00 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/31 15:21:57 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, (s + i));
		i++;
	}
}

/*void	extFunct(unsigned int index, char *c)
{
	index++;
	*c = ft_tolower(*c);
}

int	main(int argc, char *argv[])
{
	char	str[50];

	if (argc == 2)
	{
		ft_strlcpy(str, argv[1], ft_strlen(argv[1]) + 1);
		printf("Applied the external function to '%s'\n\n", str);
		ft_striteri(str, extFunct);
		printf("ft_striteri: %s", str);
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---

	Applies the function ’f’ on each character of
	the string passed as argument, passing its index
	as first argument. Each character is passed by
	address to ’f’ to be modified if necessary.

	---RETURN VALUE---
	None
*/