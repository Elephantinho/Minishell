#include "../includes/minishell.h"

void	arr_of_lists_free(char *s, char **env)
{
	free_env(env);
	if (s)
		free(s);
	write(2, "malloc failed\n", 14);
	exit(1);
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
		printf("token: %s\n", (*tokens)->token);
		prev = *tokens;
		*tokens = (*tokens)->next;
	}
	if (*tokens && (*tokens)->e_tk_type == PIPE)
	{
		(*arr_of_lists)[*i] = *first;
		printf("first %s\n", ((*arr_of_lists)[*i])->token); //segfaulta qui credo
		prev->next = NULL;
		(*tokens) = (*tokens)->next;
		(*first) = *tokens;
	}
	printf("first %s\n", ((*arr_of_lists)[*i])->token);
	printf("aaa\n");
	(*i)++;
}

t_token	**create_arr_of_lists(char *s, char **env, t_token *tokens)
{
	//char	***arr_of_matrx;
	t_token	**arr_of_lists;
	int		i;
	int		len;
	t_token	*first;

	len = count_n_of_lists(tokens);
	printf("len: %d\n", len);
	i = 0;
	first = tokens;
	arr_of_lists = malloc(sizeof(t_token *) * (len + 1));
	if (!arr_of_lists)
	{
		ft_lstclear_tok(&tokens);
		arr_of_lists_free(s, env); //da ricontrollare
	}
	while (i < len && tokens)
	{
		arr_of_lists_h(&tokens, &first, &arr_of_lists, &i);
	}
	arr_of_lists[i] = NULL;
	return (arr_of_lists);
}
