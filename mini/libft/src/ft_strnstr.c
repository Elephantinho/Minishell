/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:28:36 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/30 16:41:00 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;

	if (!big)
		return (NULL);
	if (*little == '\0')
		return ((char *)big);
	while (*big != '\0' && len != 0)
	{
		i = 0;
		while (*big == little[i] && little[i] != '\0' && (len - i) != 0)
		{
			i++;
			big++;
		}
		if (little[i] == '\0')
			return ((char *)(big - i));
		big -= i;
		len--;
		big++;
	}
	return (NULL);
}

/*int	main(int argc, char *argv[])
{
	if (argc == 4)
	{
		printf("Found %s in %s at:\n", argv[1], argv[2]);
		printf("ft_strnstr: %s", ft_strnstr(argv[1], argv[2],
				ft_atoi(argv[3])));
	}
}*/

/*				---MAN DESCRIPTION---
	The strnstr() function locates the first occurrence of the null-terminated
	string little in the string big, where not more than len characters
	are searched. 
	Characters that appear after a ‘\0’ character are not searched.

	---RETURN VALUE---
	If little is an empty string, big is returned;
	if little occurs nowhere in big, NULL is returned;
	otherwise a pointer to the first character of the first
	occurrence of little is returned.
*/