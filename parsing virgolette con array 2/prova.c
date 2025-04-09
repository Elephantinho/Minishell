/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prova.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 21:29:29 by ale               #+#    #+#             */
/*   Updated: 2025/04/09 20:00:05 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	fill_arr_single(char *s, int **arr, int *quotes_left_open, int *i)
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
	else
		*quotes_left_open = 1;
}

void	fill_arr_double(char *s, int **arr, int *quotes_left_open, int *i)
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
	else
		*quotes_left_open = 1;
}

int	*create_arr(char *s)
{
	int	*arr;
	int	quotes_left_open;
	int	i;


	quotes_left_open = 0;
	arr = malloc(sizeof(int) * ft_strlen(s));
	if (!arr)
	{
		write(2, "malloc failed", 13);
		exit(1);//non so se error code su exit va bene e anche se va bene exit o meglio solo return
	}
	i = 0;
	//printf("s0: %c\n", s[0]);
	while (s[i] != '\0')
	{
		if (s[i] == 39)
			fill_arr_single(s, &arr, &quotes_left_open, &i);
		else if (s[i] == 34)
			fill_arr_double(s, &arr, &quotes_left_open, &i);
		else
		{
			arr[i] = NO_QUOTES;
			i++;
		}
	}
	return (arr);
}
void	create_token(char *s, t_token **token_list, int token_type)
{
	t_token	*temp;
	//non so se error code su exit va bene e anche
	//se va bene come messaggio d'errore malloc failed
	//e se va bene sia scritto con write (meglio perror o strerror? o no?)

	if (s == NULL)
	{
		ft_lstclear_tok(token_list);
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
		write(2, "malloc failed", 13);
		exit(1);
	}
	ft_lstadd_back_tok(token_list, temp);
}
char	*skip_whitespaces(char *s, int *i)
{

	while (s[*i] == 32 || (s[*i] >= 9 && s[*i] <= 13))
	{
		(*i)++;
	}
	if (s[*i] == '\0')
	{
		write(2, "minishell: syntax error near unexpected token '", 46);
		write(2, &s[*i - 1], 1);//stampo sempre solo un char che non e il massimo
		write(2, "'", 1);
		exit(1);// non so se va bene cosi
	}
	return (s);
}

t_token	*separete_in_tokens(char *s, int *arr)
{
	int	i;
	int	prev_is_whitespace;
	int	start;
	t_token	*token_list;

	i = 0;
	token_list = NULL;
	prev_is_whitespace = -1;
	while (s[i] != '\0')
	{
		if ((s[i] == 32 || (s[i] >= 9 && s[i] <= 13)) && arr[i] == NO_QUOTES)
		{
			if (prev_is_whitespace == 0)
				create_token(ft_substr(s, start, i - start), &token_list, NORMAL);
			prev_is_whitespace = 1;
			i++;
		}
		else if (s[i] != '|')
		{
			if (prev_is_whitespace == 1)
				start = i;
			prev_is_whitespace = 0;
			i++;
		}
		if (s[i] == '|')
		{
			create_token(ft_substr(s, i, 1), &token_list, PIPE);
			i++;
		}
		/* if (s[i] == '>' && s[i + 1] == '<')
		{
			skip_whitespaces(s, &i);
			create_token(ft_substr(s, i - 1, 1), &token_list, PIPE);
			i++
		}
		else if (s[i] == '>')

		if (s[i] == '<' && s[i + 1] == '<')
		else if (s[i] == '<') */
	}
	return (token_list);
}

void	ft_lstiter_tok(t_token *lst, void (*f)(void *))
{
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

int	main(void)
{
	char		*s;
	int			*arr;
	t_token		*tokens;

	//s = "\"\" ahaha \" ohohoh\'ehe\'\"\"  iii\"\"\"ahah\'\"ww\'\'\'";
	s = get_next_line(0);
	arr = create_arr(s);
	tokens = separete_in_tokens(s, arr);

	printf("(%s)\n", s);
	for(int i = 0; i < ft_strlen(s) - 1; i++)
		printf("%d", arr[i]);
	printf("\n");
	ft_lstiter_tok(tokens , prnt);
	free(arr);
	free (s);
}
