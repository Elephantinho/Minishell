/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_arr_of_matrix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:49:37 by ale               #+#    #+#             */
/*   Updated: 2025/04/20 23:55:54 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_n_of_matrx(t_token *token)
{
	int	len;
	int	flag;

	len = 0;
	flag = 1;
	while(token)
	{
		if(token->e_tk_type == NORMAL && flag == 1)
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
	while (tokens && tokens->e_tk_type == NORMAL)
		{
			n_lines++;
			tokens = tokens->next;
		}
	return (n_lines);
}

void	arr_of_matrx_central_while(t_token **tokens, char ****arr_of_matrx, int *i, int *j)
{
	while (*tokens && (*tokens)->e_tk_type == NORMAL)
		{
			(*arr_of_matrx)[*i][*j] = (*tokens)->token;
			(*j)++;
			*tokens = (*tokens)->next;
	//		if (tokens)
	//		printf("aatoken type: %d, token: %s    \n", tokens->e_tk_type, tokens->token);
		}
}

char	***create_array_of_matrix(t_token *tokens)
{
	char	***arr_of_matrx;
	int		i;
	int		len;
	int		lines;
	int		j;

	len = count_n_of_matrx(tokens);
	i = 0;
//	printf("len: %d\n", len);
	arr_of_matrx = malloc(sizeof(char **) * (len + 1));
	while(i < len && tokens)
	{
//		printf("oooo\n");
//		printf("token type: %d, token: %s    \n", tokens->e_tk_type, tokens->token);
		lines = count_n_of_lines(tokens);
//		printf("lines: %d\n", lines);
//		printf("i: %d   ", i);
		arr_of_matrx[i] = malloc(sizeof(char *) * (lines + 1));
		j = 0;
		arr_of_matrx_central_while(&tokens, &arr_of_matrx, &i, &j);
		arr_of_matrx[i][j] = NULL;
		while (tokens && tokens->e_tk_type == PIPE)
		{
			free(tokens->token);
			tokens = tokens->next;
		}
		i++;
	}
	arr_of_matrx[i] = NULL;
	return (arr_of_matrx);
}
