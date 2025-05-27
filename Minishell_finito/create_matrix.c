/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:39:58 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/25 18:44:48 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	count_n_of_lines(t_token *tokens)
{
	int	n_lines;

	n_lines = 0;
	while (tokens)
	{
		n_lines++;
		tokens = tokens->next;
	}
	return (n_lines);
}

void	create_matrx_free(t_token **tokens, t_token **first, \
										char ***matrx)
{
	//da modificare (o levare)
	free_cmnds(matrx);
	ft_lstclear_tok(&(*tokens)->next);
	(*tokens)->next = NULL;
	free((*tokens)->token);
	ft_lstclear_tok_mod(first);
}

char	**create_matrix_and_free_list(t_token **tokens, t_token **first, char ***matrx)
{
	int		j;
	int		lines;
	t_token	*temp;

	lines = count_n_of_lines(*tokens);
	if (lines > 0)
	{
		(*matrx)= malloc(sizeof(char *) * (lines + 1));
		if (!((*matrx)))
		{
			(void) first;
			free(*matrx);
			//create_matrx_free(tokens, first, matrx); // da fare
			return (0);
		}
		j = 0;
		while (*tokens)
		{
			(*matrx)[j] = (*tokens)->token;
			(*tokens)->token = NULL;
			j++;
			temp = (*tokens)->next;
			free (*tokens);
			*tokens = temp;
		}
		(*matrx)[j] = NULL;
	}
	else
		(*matrx) = NULL;
	*tokens = *first;
	return (*matrx);
}
