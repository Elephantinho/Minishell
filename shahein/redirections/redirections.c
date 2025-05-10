/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:15:56 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/08 12:09:01 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_heredoc(char *limiter)
 {
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) == -1) 
	{
		perror("pipe");
		return -1;
	}
	while (1) 
	{
		line = readline("> ");
		if (!line)
			break;
		if (strcmp(line, limiter) == 0) 
		{
			free(line);
			break;
		}
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return pipefd[0];
}

void	remove_redir_tokens(t_token **tokens, t_token *prev, t_token *curr) 
{
	t_token	*to_free1 = curr;
	t_token	*to_free2 = curr->next;

	if (prev == NULL)
		*tokens = curr->next->next;
	else
		prev->next = curr->next->next;

	free(to_free1->token);
	free(to_free1);
	free(to_free2->token);
	free(to_free2);
}

void	handle_redirections(t_token **tokens, int *fd_in, int *fd_out) 
{
	t_token *curr = *tokens;
	t_token *prev = NULL;

	while (curr) 
	{
		if ((curr->e_tk_type == INPUT || curr->e_tk_type == OUTPUT ||
				curr->e_tk_type == APPEND || curr->e_tk_type == HEREDOC) &&
			curr->next && curr->next->e_tk_type == NORMAL) 
			{

			int fd = -1;
			if (curr->e_tk_type == INPUT)
				fd = open(curr->next->token, O_RDONLY);
			else if (curr->e_tk_type == OUTPUT)
				fd = open(curr->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (curr->e_tk_type == APPEND)
				fd = open(curr->next->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else if (curr->e_tk_type == HEREDOC)
				fd = handle_heredoc(curr->next->token);

			if (fd == -1)
				perror("redirection error");
			else 
			{
				if (curr->e_tk_type == INPUT || curr->e_tk_type == HEREDOC)
					*fd_in = fd;
				else
					*fd_out = fd;
			}
			remove_redir_tokens(tokens, prev, curr);
			if (prev == NULL)
				curr = *tokens;
			else
				curr = prev->next;
		}
		else 
		{
			prev = curr;
			curr = curr->next;
		}
	}
}



