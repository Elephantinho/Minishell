/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:33:16 by ade-ross          #+#    #+#             */
/*   Updated: 2025/04/02 23:23:21 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft/get_next_line_bonus.h"

struct token_quotes;

enum	token_type_for_quotes
{
	NO_QUOTES,
	DOUBLE_QUOTES,
	SINGLE_QUOTES,
};

typedef struct	s_token_quotes
{
	char	*token;
	int		token_type_for_quotes;
	struct	s_token_quotes *next;
}				t_token_quotes;

t_token_quotes	*ft_lstlast_quotes(t_token_quotes *lst)
{
	if (lst == 0)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

t_token_quotes	*ft_lstnew_quotes(void *content, int token_type)
{
	t_token_quotes	*new;

	new = malloc(sizeof(t_token_quotes));
	if (new == 0)
		return (NULL);
	new->next = NULL;
	new->token = content;
	new->token_type_for_quotes = token_type;
	return (new);
}

void	ft_lstadd_back_quotes(t_token_quotes **lst, t_token_quotes *new)
{
	t_token_quotes	*last;

	if (lst == 0 || new == 0)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast_quotes(*lst);
	last->next = new;
}

//here the token is actually created
void	actual_token_creation(char *s, int i, t_token_quotes **token_list, int *last_str_end, int token_type)
{
	t_token_quotes	*temp;

	temp = ft_lstnew_quotes(ft_substr(s, *last_str_end, \
					(i - (*last_str_end))), token_type);
	ft_lstadd_back_quotes(token_list, temp);
	//printf("*last_str_end: %d\n", *last_str_end);
	//printf("i: %d\n", i);
	*last_str_end = i + 1;
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

void	ft_lstiter_quotes(t_token_quotes *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f(lst->token);
		printf("token type: %d \n", lst->token_type_for_quotes);
		lst = lst->next;
	}
}
void	prnt(void *s)
{
	static int i = 0;
	printf("str%d: (%s)", i, (char	*)s);
	i++;
}

//if we were inside quotes updates the token type
//to show we are now out of the quotes(NO_QUOTES)
//otherwise updates token type to show we are inside the quotes
void	update_token_type(int *token_type, int quotes_type)
{
	if (*token_type == quotes_type)
		*token_type = NO_QUOTES;
	else
		*token_type = quotes_type;
}

t_token_quotes	*create_tokens(char *s)
{
	int				i;
	int				last_str_end;
	int				token_type;
	t_token_quotes	*token_list;

	token_list = NULL;
	last_str_end = 0;
	i = 0;
	token_type = NO_QUOTES;
	//s = skip_whitespaces(s);
	while (s[i] != '\0')
	{
		if (s[i] == 39 && token_type != DOUBLE_QUOTES)
		{
			actual_token_creation(s, i, &token_list, &last_str_end, token_type);
			update_token_type(&token_type, SINGLE_QUOTES);
		}
		if (s[i] == 34 && token_type != SINGLE_QUOTES)
		{
			actual_token_creation(s, i, &token_list, &last_str_end, token_type);
			update_token_type(&token_type, DOUBLE_QUOTES);
		}
		//printf("%c\n", s[i]);
		i++;
	}
	//da aggiungere qualcosa per caso di quotes che rimangono aperte volendo
	return (token_list);
}

void	ft_lstclear_quotes(t_token_quotes **lst)
{
	t_token_quotes	*temp;

	if (lst == 0)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->token);
		free(*lst);
		*lst = temp;
	}
	*lst = 0;
}

int main()
{
	t_token_quotes	*token_list;
	char *s;
	//s = "ahaha \" ohohoh\'ehe\'\"";
	s = get_next_line(0);
	token_list = create_tokens(s);
	ft_lstiter_quotes(token_list, prnt);
	ft_lstclear_quotes(&token_list);
	free (s);
}
