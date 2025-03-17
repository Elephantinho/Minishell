/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:28:24 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:39:02 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!s1 || !s2 || n == 0)
		return (0);
	while ((*s1 != '\0' || *s2 != '\0') && n > 1)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
		n--;
	}
	return ((int)((unsigned char)*s1 - (unsigned char)*s2));
}

/*int	main(int argc, char *argv[])
{
	if (argc == 4)
	{
		printf("Comparison of %d between s1 and s2:\n\n", ft_atoi(argv[3]));
		printf("ft_strncmp: %d\n", ft_strncmp(argv[1], 
		argv[2], ft_atoi(argv[3])));
		printf("strncmp: %d", strncmp(argv[1], argv[2], ft_atoi(argv[3])));
	}
}*/

/*				---MAN DESCRIPTION---
	The strncmp() function compares the two strings s1 and s2.
	It compares only the first (at most) n bytes of s1 and s2.
	The locale is not taken into account. 

    The strncmp() function is similar, except
	
	---RETURN VALUE---
	It returns an integer less than, equal to, or greater 
	than zero if s1 is found, respectively, to be less than,
	to match, or be greater than s2.
*/