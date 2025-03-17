/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_fill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:23:00 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:42:40 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_structs(t_token *tok, t_token *n_tok, t_redir *n_rd, size_t n)
{
	n_tok->value = malloc(sizeof(char *) * (n + 1));
	n_tok->nredir = 0;
	n_tok->env = tok->env;
	n_rd->name = NULL;
	n_rd->next = NULL;
}

static void	fill_struct(t_parse *data, t_token *tok, size_t ntok)
{
	t_token	*new_tok;
	t_redir	*new_rd;
	size_t	i;

	new_tok = malloc(sizeof(t_token));
	new_rd = malloc(sizeof(t_redir));
	init_structs(tok, new_tok, new_rd, ntok);
	i = 0;
	while (data && data->type != T_PIPE)
	{
		i = get_tok(data, new_tok, new_rd, i);
		data = data->next;
	}
	if (!new_rd->name)
	{
		free (new_rd);
		new_rd = NULL;
	}
	new_tok->rd = new_rd;
	new_tok->value[i] = NULL;
	tok->next = new_tok;
}

static void	first_element(t_parse *data, t_token *tok, size_t ntok)
{
	t_redir	*rd;
	size_t	i;

	tok->value = malloc(sizeof(char *) * (ntok + 1));
	rd = malloc(sizeof(t_redir));
	rd->name = NULL;
	rd->next = NULL;
	i = 0;
	while (data && data->type != T_PIPE)
	{
		i = first_tok_copy(data, tok, rd, i);
		data = data->next;
	}
	if (!rd->name)
	{
		free (rd);
		rd = NULL;
	}
	tok->rd = rd;
	tok->value[i] = NULL;
	tok->next = NULL;
}

static int	n_tokens(t_parse *data)
{
	size_t	ntok;

	ntok = 0;
	while (data && data->type != T_PIPE)
	{
		if (data->type >= T_GENERAL && data->type <= T_COMMAND)
			ntok++;
		data = data->next;
	}
	return (ntok);
}

void	fill_t_token(t_parse *data, t_token *tok)
{
	size_t	ntok;

	ntok = n_tokens(data);
	first_element(data, tok, ntok);
	while (data && data->type != T_PIPE)
		data = data->next;
	if (data)
		data = data->next;
	while (data)
	{
		ntok = n_tokens(data);
		fill_struct(data, tok, ntok);
		while (data && data->type != T_PIPE)
			data = data->next;
		if (data)
			data = data->next;
		tok = tok->next;
		tok->next = NULL;
	}
}
