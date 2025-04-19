/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_division_big_while.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:07:58 by ale               #+#    #+#             */
/*   Updated: 2025/04/19 21:18:51 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_token_base_case(t_str_tk_division *strct, t_token **token_list, char *s, int *arr)
{
	if (strct->prev_is_whitespace == 0)
		create_token(ft_substr(s, strct->start, strct->i - strct->start), token_list, NORMAL, arr);
	strct->prev_is_whitespace = 1;
	(strct->i)++;
}

void	base_case(t_str_tk_division *strct)
{
	if (strct->prev_is_whitespace == 1)
			strct->start = strct->i;
	strct->prev_is_whitespace = 0;
	(strct->i)++;
}

void	pipe_case(t_str_tk_division *strct, t_token **token_list, char *s, int *arr)
{
	check_synt_err_pipe(s, strct->i, token_list, arr);
	if (strct->prev_is_whitespace == 0)
		create_token(ft_substr(s, strct->start, strct->i - strct->start), token_list, NORMAL, arr);
	create_token(ft_substr(s, strct->i, 1), token_list, PIPE, arr);
	strct->prev_is_whitespace = 1;
	(strct->i)++;
}

void	append_case(t_str_tk_division *strct, t_token **token_list, char *s, int *arr)
{
	strct->i = strct->i + 2;
	if (strct->prev_is_whitespace == 0)
		create_token(ft_substr(s, strct->start, strct->i - 2 - strct->start), token_list, NORMAL, arr);
	create_token(ft_substr(s, strct->i - 2, 2), token_list, APPEND, arr);
	check_synt_err_redirect(s, strct->i, token_list, arr);
	strct->prev_is_whitespace = 1;
}

void	redirect_output_case(t_str_tk_division *strct, t_token **token_list, char *s, int *arr)
{
	(strct->i)++;
	if (strct->prev_is_whitespace == 0)
		create_token(ft_substr(s, strct->start, strct->i - 1 - strct->start), token_list, NORMAL, arr);
	create_token(ft_substr(s, strct->i - 1, 1), token_list, OUTPUT, arr);
	check_synt_err_redirect(s, strct->i, token_list, arr);
	strct->prev_is_whitespace = 1;
}
