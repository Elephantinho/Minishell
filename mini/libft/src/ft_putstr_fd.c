/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:37:05 by mchiaram          #+#    #+#             */
/*   Updated: 2024/01/29 14:35:15 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0 || !s)
		return ;
	while (*s)
		ft_putchar_fd(*s++, fd);
}

/*int	main(int argc, char *argv[])
{
	int	fd;
	
	if (argc == 2)
	{
		fd = open("putstr_fd.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			printf("Error!");
			return (1);
		}
		ft_putstr_fd(argv[1], fd);
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---

	Outputs the string ’s’ to the given file
	descriptor.

	---RETURN VALUE---
	None
*/