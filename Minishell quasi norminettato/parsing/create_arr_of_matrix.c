/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_arr_of_matrix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:49:37 by ale               #+#    #+#             */
/*   Updated: 2025/04/23 20:27:26 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_n_of_matrx(t_token *token)
{
	int	len;
	int	flag;

	len = 0;
	flag = 1;
	while (token)
	{
		if (token->e_tk_type == NORMAL && flag == 1)
		{
			len++;
			flag = 0;
		}
		else if (token->e_tk_type == PIPE)
			flag = 1;
		token = token->next;
	}
	return (len);
}

int	count_n_of_lines(t_token *tokens)
{
	int	n_lines;

	n_lines = 0;
	while (tokens && tokens->e_tk_type != PIPE)
	{
		n_lines++;
		tokens = tokens->next;
	}
	return (n_lines);
}

int	arr_of_matrx_h(t_token **tokens, t_token **first, \
							char ****arr_of_matrx, int *i)
{
	int	j;
	int	lines;

	lines = count_n_of_lines(*tokens);
	(*arr_of_matrx)[*i] = malloc(sizeof(char *) * (lines + 1));
	if ((!(*arr_of_matrx)[*i]))
	{
		arr_of_matrx_h_free(tokens, first, arr_of_matrx);
		return (0);
	}
	j = 0;
	while (*tokens && (*tokens)->e_tk_type != PIPE)
	{
		(*arr_of_matrx)[*i][j] = (*tokens)->token;
		j++;
		*tokens = (*tokens)->next;
	}
	(*arr_of_matrx)[*i][j] = NULL;
	while (*tokens && (*tokens)->e_tk_type == PIPE)
	{
		free((*tokens)->token);
		*tokens = (*tokens)->next;
	}
	(*i)++;
	return (1);
}

char	***create_array_of_matrix(char *s, char **env, t_token *tokens)
{
	char	***arr_of_matrx;
	int		i;
	int		len;
	t_token	*first;

	len = count_n_of_matrx(tokens);
	i = 0;
	first = tokens;
	arr_of_matrx = malloc(sizeof(char **) * (len + 1));
	if (!arr_of_matrx)
	{
		ft_lstclear_tok(&tokens);
		arr_of_matrx_free(s, env);
	}
	while (i < len && tokens)
	{
		if (arr_of_matrx_h(&tokens, &first, &arr_of_matrx, &i) == 0)
			arr_of_matrx_free(s, env);
	}
	arr_of_matrx[i] = NULL;
	return (arr_of_matrx);
}
