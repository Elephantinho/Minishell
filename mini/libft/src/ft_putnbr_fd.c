/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:32:18 by mchiaram          #+#    #+#             */
/*   Updated: 2023/10/31 15:29:54 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nbr;
	char		c;

	if (fd < 0)
		return ;
	nbr = (long int)n;
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr *= -1;
	}
	if (nbr > 9)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putnbr_fd(nbr % 10, fd);
	}
	if (nbr <= 9)
	{
		c = (nbr + '0');
		write(fd, &c, 1);
	}
}

/*int	main(int argc, char *argv[])
{
	int	fd;
	
	if (argc == 2)
	{
		fd = open("putnbr_fd.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			printf("Error!");
			return (1);
		}
		ft_putnbr_fd(ft_atoi(argv[1]), fd);
	}
	return (0);
}*/

/*				---MAN DESCRIPTION---
	Outputs the integer ’n’ to the given file
	descriptor.

	---RETURN VALUE---
	None
*/