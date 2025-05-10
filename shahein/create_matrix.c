/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:39:58 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/10 17:04:27 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	count_n_of_lines(t_token *tokens)
{
	int	n_lines;

	n_lines = 0;
	while (tokens /* && tokens->e_tk_type != PIPE */)
	{
		n_lines++;
		tokens = tokens->next;
	}
	return (n_lines);
}

//void	create_matrx_free(t_token **tokens, t_token **first, \
//	char ****arr_of_matrx)
//{
	//da modificare (o levare)
	/* free_cmnds(*arr_of_matrx);
	ft_lstclear_tok(&(*tokens)->next);
	(*tokens)->next = NULL;
	free((*tokens)->token);
	ft_lstclear_tok_mod(first);*/
//}

char **create_matrix(t_token **tokens, t_token **first, char ***arr_of_matrx)
{
	int	j;
	int	lines;

	lines = count_n_of_lines(*tokens);
	(*arr_of_matrx)= malloc(sizeof(char *) * (lines + 1));
	if ((!(*arr_of_matrx)))
	{
		(void) first;
		//create_matrx_free(tokens, first, arr_of_matrx); // da fare
		return (0);
	}
	j = 0;
	while (*tokens /* && (*tokens)->e_tk_type != PIPE */)
	{
		(*arr_of_matrx)[j] = (*tokens)->token;
		j++;
		*tokens = (*tokens)->next;
	}
	(*arr_of_matrx)[j] = NULL;
	while (*tokens /* && (*tokens)->e_tk_type == PIPE */)
	{
		free((*tokens)->token);
		*tokens = (*tokens)->next;
	}
	return (*arr_of_matrx);
}
