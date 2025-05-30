/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:21:43 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/29 21:00:48 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	sing_heredoc(t_token **curr, int *fd, char **env, int *heredoc_done)
{
	if (*fd >= 0)
		close(*fd);
	*fd = handle_heredoc((*curr)->next->token, env);
	*heredoc_done = 1;
	if (*fd == -1)
		perror("Heredoc error");
	if (g_exit_status != 0)
		return (1);
	*curr = (*curr)->next->next;
	return (0);
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
		if (curr->e_tk_type == HEREDOC
			&& curr->next
			&& curr->next->e_tk_type == NORMAL)
		{
			if (sing_heredoc(&curr, fd, env, &heredoc_done))
				break ;
		}
		else
			curr = curr->next;
	}
	return (heredoc_done);
}
