/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:33:16 by ade-ross          #+#    #+#             */
/*   Updated: 2025/04/07 15:54:07 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//here the token is actually created
void	tk_crea(char *s, t_token_quotes **token_list, int token_type)
{
	t_token_quotes	*temp;
	//non so se error code su exit va bene e anche
	//se va bene come messaggio d'errore malloc failed
	//e se va bene sia scritto con write (meglio perror o strerror? o no?)

	if (s == NULL)
	{
		ft_lstclear_quotes(token_list);
		write(2, "malloc failed", 13);
		exit(1);
	}
	temp = ft_lstnew_quotes(s, token_type);
	if (temp == NULL)
	{
		ft_lstclear_quotes(token_list);
		write(2, "malloc failed", 13);
		exit(1);
	}
	ft_lstadd_back_quotes(token_list, temp);
}

void	tk_crea_fin(char *s, t_token_quotes **token_list, int token_type)
{
	t_token_quotes	*temp;

	if (s == NULL)
	{
		ft_lstclear_quotes(token_list);
		write(2, "malloc failed", 13);
		exit(1);
	}
	if (s[0] == '\0' && token_type == NO_QUOTES)
	{
		free(s);
		return ;
	}
	temp = ft_lstnew_quotes(s, token_type);
	if (temp == NULL)
	{
		ft_lstclear_quotes(token_list);
		write(2, "malloc failed", 13);
		exit(1);
	}
	ft_lstadd_back_quotes(token_list, temp);
}
/* char	*skip_whitespaces(char *s)
{
	//funzione non ancora testata, controlla che
	//siano giusti i whitespaces e che
	//non ce ne siano anche altri da aggiungere (tipo \n ?)
	while (*s == 32 || (*s >= 9 && *s <= 13))
	{
		s++;
	}
	return (s);
} */
//eliminating whitespaces and creating multiple
//tokens in case we are not inside quotes
/* void	actual_token_creation(char *s, int i, t_token_quotes **token_list, int *last_str_end, int token_type)
{
	int	j;

	if ( i != 0)
	{
		if (token_type == NO_QUOTES)
		{
			while (*last_str_end < i && j < i)
			{
				while (*last_str_end < i && s[*last_str_end] == 32 || \
					(s[*last_str_end] >= 9 && s[*last_str_end] <= 13))
				{
					(*last_str_end)++;
				}
				j = *last_str_end;
				while (j < i && (s[j] != 32 || \
					!(s[j] >= 9 && s[j] <= 13)))
						j++;
				actual_token_creation_h(s, j, token_list, last_str_end, token_type);
			}
		}
		else
			actual_token_creation_h(s, i, token_list, last_str_end, token_type);
	}
} */

t_token_quotes	*create_tokens_h(char *s, int tok_type, int start, int *i)
{
	t_token_quotes	*tok_list;

	tok_list = NULL;
	while (s[++(*i)] != '\0')
	{
		if (s[*i] == 39 && tok_type != DOUBLE_QUOTES && *i != 0 && \
			!(tok_type == NO_QUOTES && start == *i))
		{
			tk_crea(ft_substr(s, start, (*i - start)), &tok_list, tok_type);
			start = *i + 1;
			update_token_type(&tok_type, SINGLE_QUOTES);
		}
		else if (s[*i] == 34 && tok_type != SINGLE_QUOTES && *i != 0 && \
			!(tok_type == NO_QUOTES && start == *i))
		{
			tk_crea(ft_substr(s, start, (*i - start)), &tok_list, tok_type);
			start = *i + 1;
			update_token_type(&tok_type, DOUBLE_QUOTES);
		}
		else if (tok_type == NO_QUOTES && start == *i && \
				(s[*i] == 34 || s[*i] == 39))
			oth_update_token_type(&tok_type, s, *i, &start);
	}
	tk_crea_fin(ft_substr(s, start, (*i - start)), &tok_list, tok_type);
	return (tok_list);
}

t_token_quotes	*create_tokens(char *s)
{
	int				i;
	int				start;
	int				tok_type;
	t_token_quotes	*tok_list;

	i = -1;
	tok_type = init_tok_type(s);
	start = init_start(tok_type);
	tok_list = create_tokens_h(s, tok_type, start, &i);
	return (tok_list);
}

void	ft_lstiter_quotes(t_token_quotes *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f(lst->token);
		printf("token type: %d \n", lst->e_token_type_for_quotes);
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
	t_token_quotes	*token_list;
	char		*s;

	s = "ahaha \" ohohoh\'ehe\'\"\"  iii\"\"\"ahah\'\"ww\'\"";
	//s = get_next_line(0);
	token_list = create_tokens(s);
	ft_lstiter_quotes(token_list, prnt);
	ft_lstclear_quotes(&token_list);
	//free (s);
}
