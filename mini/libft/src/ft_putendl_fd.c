/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:26:44 by mchiaram          #+#    #+#             */
/*   Updated: 2023/11/03 17:07:31 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (fd < 0 || !s)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s++, fd);
	}
	write(fd, "\n", 1);
}

/*int	main(int argc, char *argv[])
{
	int	fd;

	if (argc == 2)
	{
		fd = open("putendl_fd.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			printf("Error!");
			return (1);
		}
		ft_putendl_fd(argv[1], fd);
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---
	Outputs the string ’s’ to the given file descriptor
	followed by a newline.

	---RETURN VALUE---
	None
*/