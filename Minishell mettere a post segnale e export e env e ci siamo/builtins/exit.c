/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:21:28 by ade-ross          #+#    #+#             */
/*   Updated: 2025/05/28 01:11:37 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_fds_for_exit_no_pipes(t_exec_no_pipes *st)
{
	close(st->save_fd_in);
	close(st->save_fd_out);
}

int	check_if_arg_of_exit_is_num_no_pipes(char ***args, \
						t_exec_no_pipes *st, char **env, int j)
{
	j = 0;
	if ((!(args[0][1][j] >= '0' && args[0][1][j] <= '9') && \
		(args[0][1][j] != '-' && args[0][1][j] != '+')) || \
	((args[0][1][j] == '-' || args[0][1][j] == '+') && !(args[0][1][j + 1])))
	{
		write(2, "minishell: exit: ", 17);
		write(2, args[0][1], ft_strlen(args[0][1]));
		write(2, ": numeric argument required\n", 28);
		free_for_exit_no_pipes(args, env, st);
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
			free_for_exit_no_pipes(args, env, st);
			return (0);
		}
		j++;
	}
	return (1);
}

void	ft_exit_no_pipes(char ***args, t_exec_no_pipes *st, \
									char **env, int *exit_code)
{
	char	ex_code;

	if (args[0][1] && args[0][1][0] && args[0][1][0] != '\0')
	{
		if (check_if_arg_of_exit_is_num_no_pipes(args, st, env, 0) == 0)
			close_basic_fds_and_exit(2);
		if (args[0][2] != NULL)
		{
			*exit_code = 256;
			write(2, "minishell: exit: too many arguments\n", 36);
			return ;
		}
		else
		{
			ex_code = (char) ft_atoi(args[0][1]);
			free_for_exit_no_pipes(args, env, st);
			close_basic_fds_and_exit(ex_code);
		}
	}
	else
	{
		ex_code = (char) get_last_exit_code(env);
		free_for_exit_no_pipes(args, env, st);
		close_basic_fds_and_exit(ex_code);
	}
}

int	check_if_arg_of_exit_is_numeric(char ***args, \
								t_token **arr_of_lists, char **env, int j)
{
	j = 0;
	if ((!(args[0][1][j] >= '0' && args[0][1][j] <= '9') && \
		(args[0][1][j] != '-' && args[0][1][j] != '+')) ||
	((args[0][1][j] == '-' || args[0][1][j] == '+') && !(args[0][1][j + 1])))
	{
		write(2, "minishell: exit: ", 17);
		write(2, args[0][1], ft_strlen(args[0][1]));
		write(2, ": numeric argument required\n", 28);
		free_for_exit(args, arr_of_lists, env);
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
			free_for_exit(args, arr_of_lists, env);
			return (0);
		}
		j++;
	}
	return (1);
}

void	ft_exit(char ***args, t_token **arr_of_lists, \
								char **env, int *exit_code)
{
	char	ex_code;

	if (args[0][1] && args[0][1][0] && args[0][1][0] != '\0')
	{
		if (check_if_arg_of_exit_is_numeric(args, arr_of_lists, env, 0) == 0)
			close_basic_fds_and_exit(2);
		if (args[0][2] != NULL)
		{
			*exit_code = 1;
			write(2, "minishell: exit: too many arguments\n", 36);
			return ;
		}
		else
		{
			ex_code = (char) ft_atoi(args[0][1]);
			free_for_exit(args, arr_of_lists, env);
			close_basic_fds_and_exit(ex_code);
		}
	}
	else
	{
		ex_code = (char) get_last_exit_code(env);
		free_for_exit(args, arr_of_lists, env);
		close_basic_fds_and_exit(ex_code);
	}
}
