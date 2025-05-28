/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:39:58 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/28 02:19:35 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	count_n_of_lines_and_init_j(t_token *tokens, int *j)
{
	int	n_lines;

	*j = 0;
	n_lines = 0;
	while (tokens)
	{
		n_lines++;
		tokens = tokens->next;
	}
	return (n_lines);
}

void	create_matrx_free( t_token **first, t_token **tokens, char ***env)
{
	free_env(*env);
	ft_lstclear_tok(&(*tokens));
	free(first);
	write(2, "malloc failed\n", 14);
	close_basic_fds_and_exit(1);
}

char	**create_matrix_and_free_list(t_token **tokens, \
							t_token **first, char ***matrx, char ***env)
{
	int		j;
	int		lines;
	t_token	*temp;

	lines = count_n_of_lines_and_init_j(*tokens, &j);
	if (lines > 0)
	{
		(*matrx) = malloc(sizeof(char *) * (lines + 1));
		if (!(*matrx))
			create_matrx_free(first, tokens, env);
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
