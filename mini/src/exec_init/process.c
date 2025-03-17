/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:56:08 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:41:10 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_bin_bash(t_token *data, t_token *head)
{
	char	*bash_args[4];

	bash_args[0] = "bin/bash";
	bash_args[1] = data->value[0];
	bash_args[2] = NULL;
	if ((!ft_strcmp(data->value[0], "+")
			|| !ft_strcmp(data->value[0], "-"))
		|| execve("/bin/bash", bash_args, data->env->var) == -1)
	{
		ft_putstr_fd(data->value[0], 2);
		ft_putstr_fd(": Command not found\n", 2);
		free(*(head->fvar->fd));
		free_process_memory(head, head->env, head->fvar);
		exit(EXIT_FAILURE);
	}
	free(*(head->fvar->fd));
	free_process_memory(head, head->env, head->fvar);
	exit(EXIT_SUCCESS);
}

static void	child_process(t_token *data, int *fd, int i, t_token *head)
{
	fd = handle_redir(data, fd, i, head);
	if (check_if_builtin(data->value[0]))
	{
		if (!execute_builtin(data, data->value[0], fd[1]))
		{
			free(*(head->fvar->fd));
			free_process_memory(head, head->env, head->fvar);
			exit(EXIT_FAILURE);
		}
		free(*(head->fvar->fd));
		free_process_memory(head, head->env, head->fvar);
		exit(0);
	}
	check_ndup_fd(fd[0], fd[1]);
	if (data->value[0]
		&& execve(data->value[0], data->value, data->env->var) == -1)
		execute_bin_bash(data, head);
	free(*(head->fvar->fd));
	free_process_memory(head, head->env, head->fvar);
	exit(EXIT_SUCCESS);
}

static void	parent_process(t_token *data, int *pid, int ncommand)
{
	int	status;
	int	i;

	i = 0;
	if (data->env->exit_stat == SIGKILL)
		return ;
	while (i < ncommand)
	{
		waitpid(pid[i], &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 3)
			{
				ft_putstr_fd("Quit (core dumped)\n", 2);
				data->env->exit_stat = 131;
			}
			else if (WTERMSIG(status) == 2)
				data->env->exit_stat = 130;
		}
		else
			data->env->exit_stat = WEXITSTATUS(status);
		i++;
	}
}

static void	handle_process(t_token *cmd, int **pipes, int *pids, int ncommand)
{
	int		i;
	t_token	*cmd_head;
	int		*fd;

	cmd_head = cmd;
	fd = check_heredoc(cmd);
	if (!fd)
		return ;
	cmd->fvar->fd = &fd;
	i = -1;
	cmd = cmd_head;
	while (++i < ncommand)
	{
		fd = first_check_pipes(fd, ncommand, i, pipes);
		pids[i] = fork();
		check_pid(cmd, pids[i]);
		if (pids[i] == 0)
		{
			close_pipes_for_child(pipes, i, ncommand);
			child_process(cmd, fd, i, cmd_head);
		}
		close_pipes_for_parent(pipes, i, ncommand);
		cmd = cmd->next;
	}
	free (fd);
}

void	do_command(t_token *data)
{
	int			**pipes;
	int			*pids;
	t_token		*cmd;
	t_free		*fvar;

	pipes = NULL;
	pids = NULL;
	cmd = data;
	data->env->exit_stat = 0;
	data->ncommand = num_command(cmd);
	if (!first_check_command(data))
		return ;
	pipes = handle_pipes(data, data->ncommand);
	pids = create_pid(data->ncommand);
	fvar = malloc(sizeof(t_free));
	fvar->pids = &pids;
	fvar->pipes = pipes;
	fvar->fd = NULL;
	data->fvar = fvar;
	cmd = data;
	handle_process(cmd, pipes, pids, cmd->ncommand);
	parent_process(data, pids, data->ncommand);
	free_process_memory(NULL, NULL, data->fvar);
	unlink("heredoc_tmp.txt");
}
