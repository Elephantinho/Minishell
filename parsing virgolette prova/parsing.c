/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:33:16 by ade-ross          #+#    #+#             */
/*   Updated: 2025/04/08 01:23:22 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* char	*skip_whitespaces(t_token_quotes **tok_list_q)
{

	while (*tok_list_q != NULL)
	while (*s == 32 || (*s >= 9 && *s <= 13))
	{
		s++;
	}
	return (s);
}
 */
char	*skip_whitespaces_h(char *s)
{
	//funzione non ancora testata, controlla che
	//siano giusti i whitespaces e che
	//non ce ne siano anche altri da aggiungere (tipo \n ?)
	while (*s == 32 || (*s >= 9 && *s <= 13))
	{
		s++;
	}
	return (s);
}
/*
//eliminating whitespaces and creating multiple
//tokens in case we are not inside quotes
void	tk_crea(char *s, t_token_quotes **token_list, int token_type)
{
	int	j;

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
} */

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

t_token_quotes	*create_tokens_h(char *s, int tok_type, int start, int *i)
{
	t_token_quotes	*tok_list;

	tok_list = NULL;
	while (s[++(*i)] != '\0')
	{
		if (s[*i] == 39 && tok_type != DOUBLE_QUOTES && *i != 0)
		{
			tk_crea(ft_substr(s, start, (*i - start)), &tok_list, tok_type);
			start = *i + 1;
			update_token_type(&tok_type, SINGLE_QUOTES);
		}
		else if (s[*i] == 34 && tok_type != SINGLE_QUOTES && *i != 0)
		{
			tk_crea(ft_substr(s, start, (*i - start)), &tok_list, tok_type);
			start = *i + 1;
			update_token_type(&tok_type, DOUBLE_QUOTES);
		}
		else if (tok_type == NO_QUOTES && start == *i && \
				(s[*i] == 34 || s[*i] == 39))
			oth_update_token_type(&tok_type, s, *i, &start);
	}
	tk_crea(ft_substr(s, start, (*i - start)), &tok_list, tok_type);
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
/*
void	realloc_s(char **s, char c)
{
	int	len;

	if (*s == NULL)
	{
		s = malloc(sizeof(char *) * 2);
		s[0] = c;
		s[1] = '\0';
		return ;
	}
	//non ideale ricalcolare len ogni volta
	len = ft_strlen(s);

} */

int	init_pr_t_is_w(t_token_quotes **tok_list_q, int *i)
{
	if (((*tok_list_q)->token[0] == 32 || \
	((*tok_list_q)->token[0] >= 9 && (*tok_list_q)->token[0] <= 13)) && \
	(*tok_list_q)->e_token_type_for_quotes == NO_QUOTES)
	{
		*i = 0;
		return (1);
	}
	else
	{
		*i = -1;
		return (0);
	}
}

void	crate_tok(char **buffer, t_token **tok_list, t_token_quotes **tok_list_q, int start, int i)
{
	t_token	*temp;
	char	*tmp;
	char	*old_buf;

	/* if (*buffer != NULL)
	{
		tmp = ft_substr((*tok_list_q)->token, start, i + 1 - start);
		//check malloc
		old_buf = *buffer;
		*buffer = ft_strjoin(*buffer, tmp);
		free(tmp);
		free(old_buf);
	}
	else
		*buffer = ft_substr((*tok_list_q)->token, start, i + 1 - start); //check malloc
	temp = ft_lstnew_tok(*buffer, NORMAL);
	if (temp == NULL)
	{
		ft_lstclear_tok(tok_list);
		write(2, "malloc failed", 13);
		exit(1);
	}
	ft_lstadd_back_tok(tok_list, temp); */
}
void	ft_lstiter_tok(t_token *lst)
{
	static int i = 0;

	if (!lst)
		return ;
	while (lst != NULL)
	{
		printf("bbstr%d: (%s)", i, (char *)lst->token);
		printf("    bbtoken type: %d \n", lst->e_token_type);
		lst = lst->next;
	}
}
void	search_meta_ch(t_token_quotes **tok_list_q)
{
	t_token_quotes	**tok_list_q_st;
	t_token			*tok_list;
	int				start;
	int				i;
	char			*s;
	char			c;//non serve ma fa chiarezza
	int				prev_tok_is_whitesp;
	char			*buffer;
	char			*temp;
	char			*old_buf;

	s = NULL;
	buffer = NULL;
	tok_list_q_st = tok_list_q;
	prev_tok_is_whitesp = init_pr_t_is_w(tok_list_q, &i);
	while (*tok_list_q != NULL)
	{
		while ((*tok_list_q)->token[++i])
		{
			start = 0;
			c = (*tok_list_q)->token[i];
			if (!((c == 32 || (c >= 9 && c <= 13)) && \
				(*tok_list_q)->e_token_type_for_quotes == NO_QUOTES))
				{
					if (prev_tok_is_whitesp == 1)
						start = i;
					if ((*tok_list_q)->e_token_type_for_quotes == NO_QUOTES && \
						(c == '|' || c == '>' || c == '<'))
					{
						//crate_tok();
					}
					prev_tok_is_whitesp = 0;
				}
			else
				{
					if (prev_tok_is_whitesp == 0);
						//crate_tok(&buffer, &tok_list, tok_list_q, start, i);
					prev_tok_is_whitesp = 1;
				}
		}
		/* temp = ft_substr((*tok_list_q)->token, start, ft_strlen((*tok_list_q)->token) - start);
		//controlla malloc?
		old_buf = buffer;
		buffer = ft_strjoin(buffer, temp);
		//controlla malloc
		free(old_buf);
		free(temp); */
		*tok_list_q = (*tok_list_q)->next;
		i = -1;
	}
	ft_lstiter_tok(tok_list);
}

int	main(void)
{
	t_token_quotes	*token_list;
	char		*s;

	s = "\"\" ahaha \" ohohoh\'ehe\'\"\"  iii\"\"\"ahah\'\"ww\'\'\'";
	//s = get_next_line(0);
	token_list = create_tokens(s);
	//ft_lstiter_quotes(token_list, prnt);
	//printf("\n\n");
	search_meta_ch(&token_list);

	ft_lstclear_quotes(&token_list);
	//free (s);
}
