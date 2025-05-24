/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:13:04 by ade-ross          #+#    #+#             */
/*   Updated: 2025/05/24 21:08:38 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_minus_n(int *i, int *put_n, char **args)
{
	int	j;

	while (ft_strncmp(args[*i], "-n", 2) == 0)
	{
		j = 2;
		while (args[*i][j] == 'n')
			j++;
		if (args[*i][j] == '\0')
		{
			*put_n = 1;
			(*i)++;
		}
		else
			break ;
	}
}

void	ft_echo(char **args)
{
	int	i;
	int	put_n;
	int	flag;

	i = 0;
	put_n = 0;
	if (args && args[0] && args[0][0] != '\0')
	{
		handle_minus_n(&i, &put_n, args);
		flag = i;
		while (args[i])
		{
			if (i != flag)
				write(1, " ", 1);
			ft_printf("%s", args[i]);
			i++;
		}
	}
	if (put_n == 0)
		write(1, "\n", 1);
}
