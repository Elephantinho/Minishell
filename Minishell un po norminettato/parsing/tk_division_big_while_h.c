/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_division_big_while_h.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:15:59 by ale               #+#    #+#             */
/*   Updated: 2025/04/19 21:17:58 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_case(t_str_tk_division *strct, t_token **token_list, char *s, int *arr)
{
	strct->i = strct->i + 2;
	if (strct->prev_is_whitespace == 0)
		create_token(ft_substr(s, strct->start, strct->i - 2 - strct->start), token_list, NORMAL, arr);
	create_token(ft_substr(s, strct->i - 2, 2), token_list, HEREDOC, arr);
	check_synt_err_redirect(s, strct->i, token_list, arr);
	strct->prev_is_whitespace = 1;
}

void	redirect_input_case(t_str_tk_division *strct, t_token **token_list, char *s, int *arr)
{
	(strct->i)++;
	if (strct->prev_is_whitespace == 0)
		create_token(ft_substr(s, strct->start, strct->i - 1 - strct->start), token_list, NORMAL, arr);
	create_token(ft_substr(s, strct->i - 1, 1), token_list, INPUT, arr);
	check_synt_err_redirect(s, strct->i, token_list, arr);
	strct->prev_is_whitespace = 1;
}
