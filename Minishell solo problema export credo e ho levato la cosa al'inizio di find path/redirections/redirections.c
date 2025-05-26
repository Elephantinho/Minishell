/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:15:56 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/26 17:41:37 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_heredoc(char *limiter, char **env)
{
	char	*line;
	int		pipefd[2];
	t_token	*temp;
	int		save_fd_in;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	save_fd_in = dup(STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			dup2(save_fd_in, STDIN_FILENO);
			if (g_exit_status == 0)
			{
				write(2, "Minishell: warning: here-document ", 34);
				write(2, "delimited by end-of-file (wanted `", 34);
				write(2, limiter, ft_strlen(limiter));
				write(2, "')\n", 3);
			}
			break ;
		}
		if (strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		temp = ft_lstnew_tok(line, NORMAL);
		expand_dollar(&temp, env);
		line = temp->token;
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
		free(temp);
	}
	close(save_fd_in);
	close(pipefd[1]);
	return (pipefd[0]);
}

int	handle_heredocs(t_token **tokens, int *fd, char **env)
{
	t_token	*curr;
	int		heredoc_done;

	curr = *tokens;
	signal(SIGINT, sigint_handler_second);
	heredoc_done = 0;
	*fd = -2;
	while (curr)
	{
		if (curr->e_tk_type == HEREDOC && curr->next \
				&& curr->next->e_tk_type == NORMAL)
		{
			if (*fd >= 0)
				close (*fd);
			*fd = handle_heredoc(curr->next->token, env);
			heredoc_done = 1;
			if (*fd == -1)
				perror("Heredoc error");//qua ci va anche break(?)
			if (g_exit_status != 0)
				break ;
			curr = curr->next->next;
		}
		else
			curr = curr->next;
	}
	return (heredoc_done);
}

void	remove_redir_tokens(t_token **tokens, t_token *prev, t_token *curr)
{
	t_token	*to_free1;
	t_token	*to_free2;

	to_free1 = curr;
	to_free2 = curr->next;
	if (prev == NULL)
		*tokens = curr->next->next;
	else
		prev->next = curr->next->next;
	free(to_free1->token);
	free(to_free1);
	free(to_free2->token);
	free(to_free2);
}

void	free_heredoc_tokens(t_token **tokens)
{
	t_token	*prev;
	t_token	*curr;

	prev = NULL;
	curr = *tokens;
	while (curr)
	{
		if (curr->e_tk_type == HEREDOC && curr->next \
			&& curr->next->e_tk_type == NORMAL)
		{
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

void	update_heredoc_alredy_done(t_token *tokens, int *heredoc_alredy_done)
{
	while (tokens)
	{
		if (tokens->e_tk_type == HEREDOC)
		{
			*heredoc_alredy_done = 1;
		}
		else if (tokens->e_tk_type == INPUT)
		{
			*heredoc_alredy_done = 0;
		}
		tokens = tokens->next;
	}
}

int	handle_redirections(t_token **tokens, \
			int *heredoc_alredy_done, int *exit_code)
{
	t_token	*curr;
	t_token	*prev;
	//t_token	**first;
	int		fd;

	prev = NULL;
	//first = tokens;
	update_heredoc_alredy_done(*tokens, heredoc_alredy_done);
	free_heredoc_tokens(tokens);
	curr = *tokens;
	while (curr)
	{
		if ((curr->e_tk_type == INPUT || curr->e_tk_type == OUTPUT \
			|| curr->e_tk_type == APPEND) \
			&& curr->next && curr->next->e_tk_type == NORMAL)
		{
			fd = -1;
			if (curr->e_tk_type == INPUT)
			{
				fd = open(curr->next->token, O_RDONLY);
				if (fd != -1 && *heredoc_alredy_done == 0)
					dup2(fd, STDIN_FILENO);
			}
			else if (curr->e_tk_type == OUTPUT)
			{
				fd = open(curr->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd != -1)
					dup2(fd, STDOUT_FILENO);
			}
			else if (curr->e_tk_type == APPEND)
			{
				fd = open(curr->next->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd != -1)
					dup2(fd, STDOUT_FILENO);
			}
			if (fd == -1)
			{
				*exit_code = 256;
				write(2, "Minishell: ", 11);
				write(2, curr->next->token, ft_strlen(curr->next->token));
				write(2, ": ", 2);
				perror("");//scrive errore fatto bene, fatto ma e' da ricontrollare
				return (0);
			}
			else
				close(fd);
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
	return (1);
}
