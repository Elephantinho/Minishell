/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:24:56 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/30 16:20:54 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			len;

	if (!s)
		return ;
	ptr = (unsigned char *)s;
	len = 0;
	while (len < n)
	{
		ptr[len] = '\0';
		len++;
	}
}

/*int	main(int argc, char *argv[])
{
	char	str[50];
	size_t	len;
	size_t	j;
	
	if (argc == 3)
	{
		len = ft_strlen(argv[1]);
		ft_memcpy(str, argv[1], (len + 1));
		printf("string before function application: %s\n\n", str);
		ft_bzero(str, ft_atoi(argv[2]));
		printf("ft_bzero: ");
		j = 0;
		while (j < len)
			printf("%c", str[j++]);
		ft_memcpy(str, argv[1], (len + 1));
		bzero(str, ft_atoi(argv[2]));
		printf("\nbzero: ");
		j = 0;
		while (j < len)
			printf("%c", str[j++]);
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---
    The bzero() function erases the data in the n bytes of the memory
	starting at the location pointed to by s, by writing zeros
	(bytes containing '\0') to that area.

	---RETURN VALUE---
    None.
*/