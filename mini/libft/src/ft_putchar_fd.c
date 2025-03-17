/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:34:19 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/31 15:14:50 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

/*int	main(int argc, char *argv[])
{
	int	fd;
	
	if (argc == 2)
	{
		fd = open("putchar_fd.txt", O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
		{
			printf("Error!");
			return (1);
		}
		ft_putchar_fd(argv[1][0], fd);
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---
	Outputs the character ’c’ to the given file
	descriptor

	---RETURN VALUE---
	None
*/