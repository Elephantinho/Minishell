/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:15:56 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/29 21:12:39 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_and_dup_redir_fd(t_token *curr, int heredoc_already_done)
{
	int	fd;

	fd = -1;
	if (curr->e_tk_type == INPUT)
	{
		fd = open(curr->next->token, O_RDONLY);
		if (fd != -1 && heredoc_already_done == 0)
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
	return (fd);
}

int	print_redir_error(char *filename)
{
	write(2, "Minishell: ", 11);
	write(2, filename, ft_strlen(filename));
	write(2, ": ", 2);
	perror("");
	return (0);
}

int	handle_single_redirection(t_redirections *str, t_token **curr, \
														t_token **prev)
{
	int	fd;

	fd = open_and_dup_redir_fd(*curr, *(str->heredoc_done));
	if (fd == -1)
	{
		if (str->is_inside_pipe == 1)
			*(str->exit_code) = 1;
		else
			*(str->exit_code) = 256;
		return (print_redir_error((*curr)->next->token));
	}
	close(fd);
	remove_redir_tokens(str->tokens, *prev, *curr);
	if (*prev == NULL)
		*curr = *(str->tokens);
	else
		*curr = (*prev)->next;
	return (1);
}

void	init_for_redirections(t_redirections *str, int *heredoc_done, \
									int *exit_code, int is_inside_pipe)
{
	str->heredoc_done = heredoc_done;
	str->exit_code = exit_code;
	str->is_inside_pipe = is_inside_pipe;
}

int	handle_redirections(t_token **tokens, int *heredoc_done, \
							int *exit_code, int is_inside_pipe)
{
	t_redirections	str;
	t_token			*curr;
	t_token			*prev;

	prev = NULL;
	init_for_redirections(&str, heredoc_done, exit_code, is_inside_pipe);
	str.tokens = tokens;
	update_heredoc_alredy_done(*tokens, heredoc_done);
	free_heredoc_tokens(tokens);
	curr = *tokens;
	while (curr)
	{
		if ((curr->e_tk_type == INPUT || curr->e_tk_type == OUTPUT || \
	curr->e_tk_type == APPEND) && curr->next && curr->next->e_tk_type == NORMAL)
		{
			if (!handle_single_redirection(&str, &curr, &prev))
				return (0);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return (1);
}
