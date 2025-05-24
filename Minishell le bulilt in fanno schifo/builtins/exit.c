/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:21:28 by ade-ross          #+#    #+#             */
/*   Updated: 2025/05/24 21:09:55 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_for_exit(char ***args, char *s, char **env)
{
	if (s)
		free(s);
	free_cmnds(args);
	free_env(env);
}

int	check_if_arg_of_exit_is_numeric(char ***args, char *s, char **env, int j)
{
	j = 0;
	if ((!(args[0][1][j] >= '0' && args[0][1][j] <= '9') && \
		(args[0][1][j] != '-' && args[0][1][j] != '+')) ||
		((args[0][1][j] == '-' || args[0][1][j] == '+') && !(args[0][1][j + 1])))
	{
		write(2, "minishell: exit: ", 17);
		write(2, args[0][1], ft_strlen(args[0][1]));
		write(2, ": numeric argument required\n", 28);
		free_for_exit(args, s, env);
		return (0);
	}
	j++;
	while (args[0][1][j] && args[0][1][j] != '\0')
	{
		if (!(args[0][1][j] >= '0' && args[0][1][j] <= '9'))
		{
			write(2, "minishell: exit: ", 17);
			write(2, args[0][1], ft_strlen(args[0][1]));
			write(2, ": numeric argument required\n", 28);
			free_for_exit(args, s, env);
			return (0);
		}
		j++;
	}
	return (1);
}

void	ft_exit(char ***args, char *s, char **env, int *exit_code)
{
	char	ex_code;
	
	write(2, "exit\n", 5);
	if (args[0][1] && args[0][1][0] && args[0][1][0] != '\0')
	{
		if (check_if_arg_of_exit_is_numeric(args, s, env, 0) == 0)
			exit(2);
		if (args[0][2] != NULL)
		{
			*exit_code = 256;
			write(2, "minishell: exit: too many arguments\n", 36);
			return ;
		}
		else
		{
			ex_code = (char) ft_atoi(args[0][1]);
			free_for_exit(args, s, env);
			exit(ex_code);
		}
	}
	else
	{
		free_for_exit(args, s, env);
		ex_code = (char) get_last_exit_code(env);
		exit(ex_code);
	}
}
