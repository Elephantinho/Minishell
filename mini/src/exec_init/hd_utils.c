/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:15:37 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:40:57 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_tmpfd(t_token *data)
{
	int	fd;

	fd = open ("heredoc_tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
	{
		free_token(data);
		perror("Error heredoc_tmp file");
		return (0);
	}
	return (fd);
}

void	parent_process_hd(t_token *data, int pid)
{
	int		status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		data->env->exit_stat = WTERMSIG(status);
	else
		data->env->exit_stat = WEXITSTATUS(status);
}

int	*check_heredoc(t_token *cmd)
{
	t_token	*head;
	int		i;
	int		*fd;

	i = 0;
	fd = ft_calloc(3, sizeof(int));
	cmd->fvar->fd = &fd;
	head = cmd;
	while (cmd)
	{
		if (cmd->rd && cmd->rd->type == T_DELIM)
		{
			if (!here_doc(cmd, head) || cmd->env->exit_stat == SIGKILL)
			{
				free (fd);
				return (NULL);
			}
			fd[2] = i;
		}
		i++;
		cmd = cmd->next;
	}
	return (fd);
}
