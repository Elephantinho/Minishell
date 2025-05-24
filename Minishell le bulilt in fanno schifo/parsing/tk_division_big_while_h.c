/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_division_big_while_h.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:15:59 by ale               #+#    #+#             */
/*   Updated: 2025/05/24 22:34:12 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_case(t_str_tk_division *strct, t_token **token_list)
{
	strct->i = strct->i + 2;
	if (strct->prev_is_whitespace == 0)
		create_token(ft_substr(strct->s, strct->start, \
				strct->i - 2 - strct->start), token_list, NORMAL, strct);
	create_token(ft_substr(strct->s, strct->i - 2, 2), \
											token_list, HEREDOC, strct);
	check_synt_err_redirect(strct->s, strct->i, token_list, strct->arr);
	strct->prev_is_whitespace = 1;
}

void	redirect_input_case(t_str_tk_division *strct, t_token **token_list)
{
	(strct->i)++;
	if (strct->prev_is_whitespace == 0)
		create_token(ft_substr(strct->s, strct->start, \
				strct->i - 1 - strct->start), token_list, NORMAL, strct);
	create_token(ft_substr(strct->s, strct->i - 1, 1), \
												token_list, INPUT, strct);
	check_synt_err_redirect(strct->s, strct->i, token_list, strct->arr);
	strct->prev_is_whitespace = 1;
}

void	syntax_error_at_beginning(char *s, t_token **token_list, int *arr)
{
	write(2, "minishell: syntax error near unexpected token '|'\n", 50);
	check_synt_err_free(s, token_list, arr);
	close_basic_fds_and_exit(2);
}
