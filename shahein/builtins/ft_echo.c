/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:13:04 by ade-ross          #+#    #+#             */
/*   Updated: 2025/04/21 11:32:20 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//echo base (la flag serve per saltare spazio prima del primo arg)
void	ft_echo(char **args)
{
	int	i;
	int	put_n;
	int	flag;

	i = 0;
	put_n = 0;
	flag = 0;
	if (args && args[0] && args[0][0] != '\0')
	{
		while (ft_strcmp(args[i], "-n") == 0)
		{
			put_n = 1;
			i++;
		}
		while (args[i])
		{
			if (flag != 0)
				write(1, " ", 1);
			else
				flag = 1;
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
