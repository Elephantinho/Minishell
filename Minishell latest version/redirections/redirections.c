/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:15:56 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/18 02:28:00 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_heredoc(char *limiter, char **env)
{
	char	*line;
	int		pipefd[2];
	t_token	*temp;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return -1; // Return -1 on pipe creation failure
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;// da aggiungere messaggio d'errore come quello di bash scrivendolo sul std err con write(2, ...)
		if (strcmp(line, limiter) == 0)
		{
			free(line);
			break;
		}
		temp = ft_lstnew_tok(line, NORMAL);
		expand_dollar(&temp, env);
		line = temp->token;
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
		free(temp);
	}
	close(pipefd[1]);
	return (pipefd[0]); // Return the read end of the pipe
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

int	handle_heredocs(t_token **tokens, int *fd, char **env)
{
	t_token *curr = *tokens;
//	t_token *prev = NULL;

	int		heredoc_done;
	//int		save_fd_out;
	//save_fd_out = dup(STDOUT_FILENO);
	//int		save_fd_in;
	//save_fd_in = dup(STDIN_FILENO);

	*fd = 0;
	heredoc_done = 0;
	while (curr)
	{
		if (curr->e_tk_type == HEREDOC && curr->next && curr->next->e_tk_type == NORMAL)
		{
			//dup2(original_fd_out, STDOUT_FILENO);
			//dup2(original_fd_in, STDIN_FILENO);
			if (heredoc_done == 1)
				close (*fd);//credo ci vada questo
			*fd = handle_heredoc(curr->next->token, env);
			heredoc_done = 1;
			if (*fd != -1)
			{
				//dup2(fd, STDIN_FILENO);//forse qui va chiuso fd dopo ave fatto dup2
			}
			else
				perror("Heredoc error");
		//	remove_redir_tokens(tokens, prev, curr);
			/* if (prev == NULL)
				curr = *tokens;
			else
				curr = prev->next; */
		//	prev = curr->next;
			curr = curr->next->next;
		}
		else
		{
			//prev = curr;
			curr = curr->next;
		}
		//dup2(save_fd_in, STDIN_FILENO);
	}
	if (heredoc_done == 1)
	{
		//dup2(fd, STDIN_FILENO);
		//dup2(save_fd_out, STDOUT_FILENO);
	}
	//close(save_fd_in);//credo vadano qui
	//close(save_fd_out);
	return (heredoc_done);
}

void	handle_redirections(t_token **tokens, int heredoc_alredy_done)
{
	t_token *curr = *tokens;
	t_token *prev = NULL;
	int		fd;

	while (curr)
	{
		if ((curr->e_tk_type == INPUT || curr->e_tk_type == OUTPUT ||
			 curr->e_tk_type == APPEND) &&
			curr->next && curr->next->e_tk_type == NORMAL)
		{
			fd = -1;
			if (curr->e_tk_type == INPUT)
			{
				fd = open(curr->next->token, O_RDONLY);
				if (fd != -1 && heredoc_alredy_done == 0)
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
				perror("Minishell: redirection error");//scrive errore fatto bene sia printa permission denied sia no such file or directory e fare exit
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
}




