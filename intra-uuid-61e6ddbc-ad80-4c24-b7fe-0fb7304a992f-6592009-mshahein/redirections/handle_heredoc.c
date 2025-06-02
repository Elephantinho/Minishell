/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:34:18 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/27 16:47:35 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_heredoc_warning(char *limiter)
{
	write(2, "Minishell: warning: here-document ", 34);
	write(2, "delimited by end-of-file (wanted `", 34);
	write(2, limiter, strlen(limiter));
	write(2, "')\n", 3);
}

int	should_stop_heredoc(char *line, char *limiter, int save_fd)
{
	if (!line)
	{
		dup2(save_fd, STDIN_FILENO);
		return (1);
	}
	if (strcmp(line, limiter) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

void	write_expanded_line_to_pipe(char *line, char **env, int pipefd)
{
	t_token	*temp;

	temp = ft_lstnew_tok(line, NORMAL);
	expand_dollar(&temp, env);
	line = temp->token;
	write(pipefd, line, strlen(line));
	write(pipefd, "\n", 1);
	free(line);
	free(temp);
}

int	handle_heredoc(char *limiter, char **env)
{
	char	*line;
	int		pipefd[2];
	int		save_fd;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	save_fd = dup(STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		if (should_stop_heredoc(line, limiter, save_fd))
		{
			if (!line && g_exit_status == 0)
				print_heredoc_warning(limiter);
			break ;
		}
		write_expanded_line_to_pipe(line, env, pipefd[1]);
	}
	close(save_fd);
	close(pipefd[1]);
	return (pipefd[0]);
}
