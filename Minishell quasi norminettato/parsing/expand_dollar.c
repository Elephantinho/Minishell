/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 01:57:50 by ale               #+#    #+#             */
/*   Updated: 2025/04/22 23:41:26 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_dollar_sec_h(t_str *st, t_token **tks)
{
	if (st->s == NULL || st->s[0] == '\0')
	{
//		printf("000\n");
		if (st->prev != NULL)
		{
			st->prev->next = (*tks)->next;
			ft_lstdelone_tok(*tks);
			*tks = st->prev;
		}
		else
		{
			(*tks) = (*tks)->next;
			ft_lstdelone_tok(st->first);
			st->first = NULL;
		}
//		printf("aa\n");
	}
	else
	{
		free((*tks)->token);
		(*tks)->token = st->s;
		take_out_quotes(&((*tks)->token), \
			st->deleted_quotes_until, st->i_before_dollar, &(st->i));
		st->deleted_quotes_until = st->i;
	}
}

void	expand_dollar_first_h(t_str *st, t_token **tks, char **env)
{
	st->s = (*tks)->token;
	st->deleted_quotes_until = 0;
	st->quotes_open = 0;
	take_out_quotes(&((*tks)->token), 0, -2, &(st->i));
	while (st->s != NULL && st->s[st->i] != '\0')
	{
		while (st->s[st->i] != '$' && st->s[st->i] != '\0')
		{
			check_quotes(st->s, st->i, &(st->quotes_open));
			//printf("i: %d, quotes_open: %d\n", i, quotes_open);
			st->i = st->i + 1;
		}
		if (st->s[st->i] == '$' && st->quotes_open != SINGLE_QUOTES)
		{
			st->i_before_dollar = st->i;
			st->s = expand_dollar_h(st, env);
			expand_dollar_sec_h(st, tks);
		}
		if (st->s != NULL && st->s[st->i] == '$' && \
			st->quotes_open == SINGLE_QUOTES)
			st->i = st->i + 1;
	}
//	printf("S0: %s\n", st->s);
	if (st->s != NULL)
		take_out_quotes(&((*tks)->token), st->deleted_quotes_until, \
		ft_strlen((*tks)->token), &(st->i));
//	printf("S1: %s\n", st->s);
}

void	expand_dollar(t_token **tks, char **env)
{
	t_str	st;

	st.prev = NULL;
	st.first = *tks;
	while (*tks)
	{
		st.i = 0;
		if ((*tks)->e_tk_type == NORMAL) //forse si puo anche levare questo if
		{
			expand_dollar_first_h(&st, tks, env);
		}
		st.prev = *tks;
		if (st.first != NULL)
			*tks = (*tks)->next;
		else
			st.first = *tks;
	}
	*tks = st.first;
}
