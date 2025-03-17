/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:42:01 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:42:03 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirect(t_redir *rd)
{
	t_redir	*current;

	current = rd;
	while (current && current->name)
	{
		rd = rd->next;
		free(current->name);
		free(current);
		current = NULL;
		current = rd;
	}
}

static void	free_values(char **value)
{
	size_t	i;

	i = 0;
	while (value[i])
		free(value[i++]);
	free (value);
	value = NULL;
}

void	free_token(t_token *tok)
{
	t_token	*current;

	current = tok;
	while (current)
	{
		if (current->value)
			free_values(current->value);
		if (current->rd)
			free_redirect(current->rd);
		tok = tok->next;
		free (current);
		current = NULL;
		current = tok;
	}
}
