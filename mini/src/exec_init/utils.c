/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:41:34 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:41:36 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_check_command(t_token *data)
{
	int	*fd;

	if (!data->ncommand && !data->rd)
		return (0);
	if (data->ncommand == 1 && data->value[0])
	{
		if (!ft_strcmp(data->value[0], "exit"))
			ft_exit(data);
		else if (check_if_builtin(data->value[0]))
		{
			fd = ft_calloc(2, sizeof(int));
			fd[0] = dup(STDIN_FILENO);
			fd[1] = dup(STDOUT_FILENO);
			fd = handle_redir(data, fd, 0, data);
			execute_builtin(data, data->value[0], fd[1]);
			free (fd);
		}
		else
			return (1);
		return (0);
	}
	return (1);
}

void	check_pid(t_token *data, int pid)
{
	if (pid < 0)
	{
		free_token(data);
		perror("Fork Error");
		exit(EXIT_FAILURE);
	}
}

void	check_ndup_fd(int fd0, int fd1)
{
	if (fd0 != STDIN_FILENO)
	{
		dup2(fd0, STDIN_FILENO);
		close(fd0);
	}
	if (fd1 != STDOUT_FILENO)
	{
		dup2(fd1, STDOUT_FILENO);
		close(fd1);
	}
}

int	*create_pid(int ncommand)
{
	int		*pids;

	pids = ft_calloc(ncommand, sizeof(int));
	if (!pids)
	{
		perror("pids malloc failed");
		exit(EXIT_FAILURE);
	}
	return (pids);
}

int	num_command(t_token *cmd)
{
	int		ncommand;

	if (!cmd || !cmd->value)
		return (0);
	ncommand = 0;
	while (cmd)
	{
		if (cmd->value[0]
			&& ft_strcmp(cmd->value[0], "exit")
			&& (access(cmd->value[0], X_OK)
				&& !check_if_builtin(cmd->value[0])))
		{
			ft_putstr_fd(cmd->value[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			cmd->env->exit_stat = 127;
			return (0);
		}
		if (cmd->value && cmd->value[0])
			ncommand++;
		cmd = cmd->next;
	}
	return (ncommand);
}
