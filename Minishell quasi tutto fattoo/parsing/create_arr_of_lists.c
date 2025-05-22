#include "../includes/minishell.h"

void	arr_of_lists_free(char *s, char **env)
{
	free_env(env);
	if (s)
		free(s);
	write(2, "malloc failed\n", 14);
}

int	count_n_of_lists(t_token *token)
{
	int	len;
	int	flag;

	len = 0;
	flag = 1;
	while (token)
	{
		if (token->e_tk_type == NORMAL && flag == 1)
		{
			len++;
			flag = 0;
		}
		else if (token->e_tk_type == PIPE)
			flag = 1;
		token = token->next;
	}
	return (len);
}

void	arr_of_lists_h(t_token **tokens, t_token **first, \
							t_token ***arr_of_lists, int *i)
{
	t_token	*prev;

	while (*tokens && (*tokens)->e_tk_type != PIPE)
	{
		prev = (*tokens);
		*tokens = (*tokens)->next;
	}
	if (*tokens && (*tokens)->e_tk_type == PIPE)
	{
		(*arr_of_lists)[*i] = (*first);
		prev->next = NULL;
		prev = (*tokens);
		(*tokens) = (*tokens)->next;
		free(prev->token);//credo ci vadano sti 2 free
		free(prev);
		if ((*tokens))//if forse non serve(mafunziona) ((*first) = (*tokens); serve pero solo l'if forse e' inutile)
			(*first) = (*tokens);
	}
	else if (!(*tokens))
	{
		(*arr_of_lists)[*i] = *first;
		prev->next = NULL;
	}
	(*i)++;
}

t_token	**create_arr_of_lists(char *s, char **env, t_token **tokens)
{
	t_token	**arr_of_lists;
	t_token	*first;
	int		i;
	int		len;

	len = count_n_of_lists(*tokens);
	i = 0;
	first = *tokens;
	arr_of_lists = malloc(sizeof(t_token *) * (len + 1));
	if (!arr_of_lists)
	{
		ft_lstclear_tok(tokens);
		arr_of_lists_free(s, env); //da ricontrollare
		return (NULL);
	}
	while (i < len && tokens && *tokens)
	{
		arr_of_lists_h(tokens, &first, &arr_of_lists, &i);
	}
	arr_of_lists[i] = NULL;
	/* i = 0;
	while (arr_of_lists[i])
	{
		printf("\narr_or_lists[%d]\n", i);
		ft_lstiter_tok(arr_of_lists[i], prnt);
		i++;
	}
	printf("\n"); */
	return (arr_of_lists);
}
