/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:13:04 by ade-ross          #+#    #+#             */
/*   Updated: 2025/05/30 21:52:21 by ade-ross         ###   ########.fr       */
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

//echo base (la flag serve per saltare spazio prima del primo arg)
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
/*
int main()
{
	char **args;

	args = malloc(4 * sizeof(char *));
	args[1] = ft_strdup("ciao");
	args[2] = ft_strdup("come");
	args[3] = ft_strdup("va");
	args[4] = NULL;
	ft_echo(args);
} */
