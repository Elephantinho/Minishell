/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:02:58 by mshahein          #+#    #+#             */
/*   Updated: 2025/04/23 11:40:15 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../parsing/parsing.h"

void free_token_list(t_token *head)
{
	t_token *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->token)
			free(tmp->token);
		free(tmp);
	}
}

void free_two_nodes(t_token *first, t_token *second)
{
	if (first)
	{
		if (first->token)
			free(first->token);
		free(first);
	}
	if (second)
	{
		if (second->token)
			free(second->token);
		free(second);
	}
}

void redirections(t_token **head, int *fd_in, int *fd_out)
{
	t_token *tmp = *head;
	t_token *prev = NULL;

	while (tmp)
	{
		if ((tmp->e_tk_type == INPUT || tmp->e_tk_type == OUTPUT) &&
			tmp->next && tmp->next->e_tk_type == NORMAL)
		{
			t_token *file_token = tmp->next;

			// Apertura del file
			if (tmp->e_tk_type == INPUT)
			{
				*fd_in = open(file_token->token, O_RDONLY);
				if (*fd_in == -1)
				{
					perror("open (input)");
					exit(EXIT_FAILURE);
				}
			}
			else if (tmp->e_tk_type == OUTPUT)
			{
				*fd_out = open(file_token->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (*fd_out == -1)
				{
					perror("open (output)");
					exit(EXIT_FAILURE);
				}
			}
			// Aggiorna i collegamenti della lista
			if (prev != NULL)
				prev->next = file_token->next;
			else
				*head = file_token->next;

			// Libera i due nodi
			free_two_nodes(tmp, file_token);

			// Prossimo nodo
			if (prev != NULL)
				tmp = prev->next;
			else
				tmp = *head;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void    close_redirections(int fd_in, int fd_out)
{
    if (fd_in != -1)
        close(fd_in);
    if (fd_out != -1)
        close(fd_out);
}