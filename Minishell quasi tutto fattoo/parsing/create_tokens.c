/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:13:01 by ale               #+#    #+#             */
/*   Updated: 2025/05/21 23:25:38 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_token(char *new_s, t_token **token_list, int token_type, \
												t_str_tk_division *strct)
{
	t_token	*temp;

	if (new_s == NULL)
	{
		free(strct->s);
		ft_lstclear_tok(token_list);
		free(strct->arr);
		write(2, "malloc failed\n", 14);
		close_basic_fds_and_exit(1);
	}
	temp = ft_lstnew_tok(new_s, token_type);
	if (temp == NULL)
	{
		free(strct->s);
		ft_lstclear_tok(token_list);
		free(strct->arr);
		write(2, "malloc failed\n", 14);
		close_basic_fds_and_exit(1);
	}
	ft_lstadd_back_tok(token_list, temp);
}
void	check_synt_err_free(char *s, t_token **token_list, int *arr)
{
	ft_lstclear_tok(token_list);
	free(arr);
	free(s);
}

void	check_synt_err_redirect(char *s, int i, t_token **token_list, int *arr)
{
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		(i)++;
	if (s[i] == '>' || s[i] == '<' || s[i] == '|')
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, &s[i], 1);
		if (s[i + 1] == '>' || s[i + 1] == '<')
			write(2, &s[i + 1], 1);
		write(2, "'\n", 2);
		check_synt_err_free(s, token_list, arr);
		close_basic_fds_and_exit(2);// non so se va bene cosi
	}
	if (s[i] == '\0')
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		if (s[i - 1] == '\n')
			write(2, "newline", 7);
		else
			write(2, &s[i - 1], 1);//stampo sempre solo un char che non e il massimo
		write(2, "'\n", 2);
		check_synt_err_free(s, token_list, arr);
		close_basic_fds_and_exit(2);
	}
}

void	check_synt_err_pipe(char *s, int i, t_token **token_list, int *arr)
{
	i++;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '|')
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, &s[i], 1);
		write(2, "'\n", 2);
		check_synt_err_free(s, token_list, arr);
		close_basic_fds_and_exit(2);
	}
	if (s[i] == '\0')
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		if (s[i - 1] == '\n')
			write(2, "newline", 7);
		else
			write(2, &s[i - 1], 1);
		write(2, "'\n", 2);
		check_synt_err_free(s, token_list, arr);
		close_basic_fds_and_exit(2);//exit non so se va bene cosi
	}
}

void	check_quotes(char *s, int i, int *quotes_open)
{
	if ((s[i] == 39) && *quotes_open == 0)
		*quotes_open = 1;
	else if ((s[i] == 34) && *quotes_open == 0)
		*quotes_open = 2;
	else if ((s[i] == 39) && *quotes_open == 1)
		*quotes_open = 0;
	else if ((s[i] == 34) && *quotes_open == 2)
		*quotes_open = 0;
}
