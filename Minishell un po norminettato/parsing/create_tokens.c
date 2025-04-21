/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:13:01 by ale               #+#    #+#             */
/*   Updated: 2025/04/21 03:19:02 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_token(char *s, t_token **token_list, int token_type, int *arr)
{
	t_token	*temp;
	//non so se error code su exit va bene e anche
	//se va bene come messaggio d'errore malloc failed
	//e se va bene sia scritto con write (meglio perror o strerror? o no?)

	if (s == NULL)
	{
		ft_lstclear_tok(token_list);
		free(arr);
		write(2, "malloc failed", 13);
		exit(1);
	}
	/* if (s[0] == '\0' && token_type == NO_QUOTES)
	{
		free(s);
		return ;
	} */
	temp = ft_lstnew_tok(s, token_type);
	if (temp == NULL)
	{
		ft_lstclear_tok(token_list);
		free(s);
		free(arr);
		write(2, "malloc failed", 13);
		exit(1);
	}
	ft_lstadd_back_tok(token_list, temp);
}

void	check_synt_err_redirect(char *s, int i, t_token **token_list, int *arr)
{
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		(i)++;
	if (s[i] == '>' || s[i] == '<' || s[i] == '|')
	{
		ft_lstclear_tok(token_list);
		free(arr);
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, &s[i], 1);
		if (s[i + 1] == '>' || s[i + 1] == '<')
			write(2, &s[i + 1], 1);
		write(2, "'\n", 2);
		free(s);
		exit(1);// non so se va bene cosi
	}
	if (s[i] == '\0')
	{
		ft_lstclear_tok(token_list);
		free(arr);
		write(2, "minishell: syntax error near unexpected token '", 47);
		if (s[i - 1] == '\n')
			write(2, "newline", 7);
		else
			write(2, &s[i - 1], 1);//stampo sempre solo un char che non e il massimo
		write(2, "'\n", 2);
		free(s);
		exit(1);// non so se va bene cosi
	}
}

void	check_synt_err_pipe(char *s, int i, t_token **token_list, int *arr)
{
	i++;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '|')
	{
		ft_lstclear_tok(token_list);
		free(arr);
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, &s[i], 1);
		write(2, "'\n", 2);
		free(s);
		exit(2);// non so se va bene cosi
	}
	if (s[i] == '\0')
	{
		ft_lstclear_tok(token_list);
		free(arr);
		write(2, "minishell: syntax error near unexpected token '", 47);
		if (s[i - 1] == '\n')
			write(2, "newline", 7);
		else
			write(2, &s[i - 1], 1);//se c"e a capo qua lo stampa che non e il massimo
		write(2, "'\n", 2);
		free(s);
		exit(2);// non so se va bene cosi
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
