/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_division.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 21:29:29 by ale               #+#    #+#             */
/*   Updated: 2025/04/21 00:21:41 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_arr_single(char *s, int **arr, int *i)
{
	(*arr)[*i] = SINGLE_QUOTES;
	(*i)++;
	while (s[*i] != 39 && s[*i] != '\0')
	{
		(*arr)[*i] = SINGLE_QUOTES;
		(*i)++;
	}
	if (s[*i] != '\0')
	{
		(*arr)[*i] = SINGLE_QUOTES;
		(*i)++;
	}
}

void	fill_arr_double(char *s, int **arr, int *i)
{
	(*arr)[*i] = DOUBLE_QUOTES;
	(*i)++;
	while (s[*i] != 34 && s[*i] != '\0')
	{
		(*arr)[*i] = DOUBLE_QUOTES;
		(*i)++;
	}
	if (s[*i] != '\0')
	{
		(*arr)[*i] = DOUBLE_QUOTES;
		(*i)++;
	}
}

void	sep_in_tk_lots_of_ifs(t_str_tk_division *strct, \
		t_token **token_list, char *s, int *arr)
{
	check_quotes(s, strct->i, &(strct->quotes_open));
	if ((s[strct->i] == 32 || (s[strct->i] >= 9 && \
		s[strct->i] <= 13)) && arr[strct->i] == 0)
		create_token_base_case(strct, token_list, s, arr);
	else if (arr[strct->i] == 1 || arr[strct->i] == 2 || \
			(arr[strct->i] == 0 && (s[strct->i] != '|' && \
			s[strct->i] != '>' && s[strct->i] != '<')))
		base_case(strct);
	else if (s[strct->i] == '>' && s[strct->i + 1] == '>' && arr[strct->i] == 0)
		append_case(strct, token_list, s, arr);
	else if (s[strct->i] == '>' && arr[strct->i] == 0)
		redirect_output_case(strct, token_list, s, arr);
	else if (s[strct->i] == '<' && s[strct->i + 1] == '<' && arr[strct->i] == 0)
		heredoc_case(strct, token_list, s, arr);
	else if (s[strct->i] == '<' && arr[strct->i] == 0)
		redirect_output_case(strct, token_list, s, arr);
	else if (s[strct->i] == '|' && arr[strct->i] == 0)
		pipe_case(strct, token_list, s, arr);

}

int	*create_arr(char *s, char **env)
{
	int	*arr;
	int	i;

	arr = malloc(sizeof(int) * ft_strlen(s));
	if (!arr)
	{
		write(2, "malloc failed", 13);
		free_env(env);
		exit(1);//non so se error code su exit va bene e anche se va bene exit o meglio solo return
	}
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 39)
			fill_arr_single(s, &arr, &i);
		else if (s[i] == 34)
			fill_arr_double(s, &arr, &i);
		else
		{
			arr[i] = NO_QUOTES;
			i++;
		}
	}
	return (arr);
}

t_token	*separete_in_tokens(char *s, int *arr)
{
	t_str_tk_division	strct;
	t_token				*token_list;

	strct.i = 0;
	strct.quotes_open = 0;
	strct.start = 0;
	strct.prev_is_whitespace = -1;
	token_list = NULL;
	while (s[strct.i] != '\0')
		sep_in_tk_lots_of_ifs(&strct, &token_list, s, arr);
	if (strct.quotes_open == 1 || strct.quotes_open == 2)
		create_token(ft_substr(s, strct.start, strct.i - strct.start), \
								&token_list, NORMAL, arr);
	else if (!((s[strct.i - 1] == 32 || (s[strct.i - 1] >= 9 && \
					s[strct.i - 1] <= 13)) && arr[strct.i - 1] == 0))
		create_token(ft_substr(s, strct.start, strct.i - strct.start), \
								&token_list, NORMAL, arr);
	return (token_list);
}

void	ft_lstiter_tok(t_token *lst, void (*f)(void *))
{
	//funzione da levare
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f(lst->token);
		printf("token type: %d \n", lst->e_tk_type);
		lst = lst->next;
	}
}

void	prnt(void *s)
{
	static int	i = 0;

	//funzione da levare
	printf("str%d: (%s)", i, (char *)s);
	i++;
}

/* int	main(char **argv, int argc, char** env)
{
	char		*s;
	int			*arr;
	t_token		*tokens;

	//s = "\"\" ahaha \" ohohoh\'ehe\'\"\"  iii\"\"\"ahah\'\"ww\'\'\' |   ";
	s = get_next_line(0);
	arr = create_arr(s);
	tokens = separete_in_tokens(s, arr);
	check_ambig_redirect(&tokens, env);
	//printf("(%s)\n", s);
	//for(int i = 0; i < ft_strlen(s) - 1; i++)
	//	printf("%d", arr[i]);
	printf("\n");
	ft_lstiter_tok(tokens , prnt);
	free(arr);
	free (s);
} */
