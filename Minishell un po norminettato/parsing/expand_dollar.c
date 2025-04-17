/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 01:57:50 by ale               #+#    #+#             */
/*   Updated: 2025/04/17 21:52:39 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_code;

int	handle_handle_dollar_qmark(void)
{
	int		exit_code;

	if (WIFEXITED(error_code))
	{
		// Child terminated normally
		exit_code = WEXITSTATUS(error_code);
		return (exit_code); // You can propagate the same exit code
	}
	else if (WIFSIGNALED(error_code))
	{
		// Child terminated by a signal
		exit_code = WTERMSIG(error_code);
		return (128 + exit_code);
	}
	else if (WIFSTOPPED(error_code))
	{
		// Child was stopped (not terminated)
		exit_code = WSTOPSIG(error_code);
		return (128 + exit_code); // Similar convention
	}
	else if (WIFCONTINUED(error_code))
	{
		return (0); // No error
	}
	else
	{
		// This should rarely happen
		return (1); // Generic error
	}
}

void	take_out_quotes_h(char **new_tk, int *i, int *len, int *end_of_doll_st)
{
	int	j;

	j = *i - 1;
	while ((*new_tk)[++j] != '\0')
		(*new_tk)[j] = (*new_tk)[j + 1];
	*len = *len -1;
	*end_of_doll_st = *end_of_doll_st - 1;
	*i = *i - 1;
}

void	take_out_quotes(char **new_tok, int i, int len, int *end_of_doll_st)
{
	static int	quotes_open = 0;

	if (len == -2)
	{
		quotes_open = 0;
		return ;
	}
//	printf("len: %d\n", len);
	while ((*new_tok) != NULL && (*new_tok)[i] != '\0' && i < len)
	{
		check_quotes(*new_tok, i, &quotes_open);
		//printf("000(*new_tok)[i]: %c i: %d, quotes_open: %d\n", (*new_tok)[i], i, quotes_open);
		if (((*new_tok)[i] == 39) && quotes_open != 2)
		{
			take_out_quotes_h(new_tok, &i, &len, end_of_doll_st);
		}
		else if (((*new_tok)[i] == 34) && quotes_open != 1)
		{
			take_out_quotes_h(new_tok, &i, &len, end_of_doll_st);
		}
		i++;
	//	printf("(*new_tok)[i]: %c i: %d, quotes_open: %d\n", (*new_tok)[i], i, quotes_open);
	}
}

void	single_dollar_case(int *i, t_token **tks, char **env, char **env_cont)
{
	*env_cont = ft_itoa(getpid());
	if (!(*env_cont))
	{
		write(2, "malloc failed\n", 14);
		free_env(env);//da levare credo
		ft_lstclear_tok(tks);
		exit(1);//exit cosi va bene?
	}
	(*i)++;
//		printf("env_cont1: %s\n", *env_content);
}

void	dollar_qmark_case(int *i, t_token **tks, char **env, char **env_content)
{
	*env_content = ft_itoa(handle_dollar_qmark());
	if (!(*env_content))
	{
		write(2, "malloc failed\n", 14);
		free_env(env);//da levare credo
		ft_lstclear_tok(tks);
		exit(1);//exit cosi va bene?
	}
	(*i)++;
//	printf("env_cont2: %s\n", *env_content);
}

int	expand_dollar_hh(t_str *st, t_token **tks, char **env)
{
	if (st->s[st->i] == '$')
	{
		single_dollar_case(&(st->i), tks, env, &(st->env_content));
	}
	else if (st->s[st->i] == '?')
	{
		dollar_qmark_case(&(st->i), tks, env, &(st->env_content));
	}
	else
	{
		st->new_tok = ft_strdup(st->s);
		if (!(st->new_tok))
		{
			write(2, "malloc failed\n", 14);
			free_env(env);//da levare credo
			ft_lstclear_tok(tks);
			exit(1);//exit cosi va bene?
		}
		return (0);
	}
	return (1);
}

void	expand_dollar_hhh(t_str *st, t_token **tks, char **env)
{
	char	*temp;

	temp = ft_substr(st->s, st->start, st->i - st->start);
	if (!temp)
	{
		write(2, "malloc failed\n", 14);
		free_env(env);//da levare credo
		ft_lstclear_tok(tks);
		exit(1);//exit cosi va bene?
	}
//	printf("temp: %s\n", temp);
	st->env_content = ft_getenv(temp, env);
	free(temp);
	if (st->env_content)
	{
		st->env_content = ft_strdup(st->env_content);
		if (!(st->env_content))
		{
			write(2, "malloc failed\n", 14);
			free_env(env);//da levare credo
			ft_lstclear_tok(tks);
			exit(1);//exit cosi va bene?
		}
	}
//		printf("env_cont: %s\n", *env_content);
}

void	expand_dollar_hhhh(t_str *st, t_token **tks, char **env)
{
	char	*temp;

	if (st->start > 1)
	{
		temp = ft_substr(st->s, 0, st->start - 1);
		if (!temp)
		{
			free(st->env_content); //credo ci vada
			write(2, "malloc failed\n", 14);
			free_env(env);//da levare credo
			ft_lstclear_tok(tks);
			exit(1);//exit cosi va bene?
		}
//		printf("temp2: %s\n", temp);
		st->new_tok = ft_strjoin(temp, st->env_content);
//		printf("*new_tok: %s\n", *new_tok);
		free(st->env_content);
		free(temp);
	//	take_out_quotes(new_tok); //da levare
//		printf("*new_tok1: %s\n", *new_tok);
	}
	else
	{
		st->new_tok = st->env_content;
	}
}

int	expand_dollar_hhhhh(t_str *st, t_token **tks, char **env)
{
	char	*temp;

	if (st->s[st->i] != '\0')
	{
		temp = ft_substr(st->s, st->i, st->i - ft_strlen(st->s));
		if (!temp)
		{
			write(2, "malloc failed\n", 14);
			free_env(env);//da levare credo
			ft_lstclear_tok(tks);
			exit(1);//exit cosi va bene?
		}
		st->env_content = ft_strjoin(st->new_tok, temp);
		free(temp);
		st->i = ft_strlen(st->new_tok);
		free(st->new_tok);
	//	take_out_quotes(&env_content); // da levare
	}
	else
	{
		st->i = ft_strlen(st->new_tok);
		return (1);
	}
	return (0);
}

char	*expand_dollar_h(t_str *st, t_token **tks, char **env)
{
	st->i = st->i + 1;
	st->start = st->i;
	while ((st->s[st->i] >= 'a' && st->s[st->i] <= 'z') || \
			(st->s[st->i] >= 'A' && st->s[st->i] <= 'Z') || \
			(st->s[st->i] >= '0' && st->s[st->i] <= '9') || \
			st->s[st->i] == '_' )
		(st->i)++;
//	printf("start: %d   i: %d\n", start, st->i);
	if (st->i <= st->start) //basta == in teoria
	{
		if (expand_dollar_hh(st, tks, env) == 0)
			return (st->new_tok);
	}
	else if (st->i > st->start)
	{
		expand_dollar_hhh(st, tks, env);
	}
//	printf("start: %d   i: %d\n", start, st->i);
	expand_dollar_hhhh(st, tks, env);
	if (expand_dollar_hhhhh(st, tks, env) == 1)
		return (st->new_tok);
	//printf("FINenv_cont: %s\n", env_content);
	return (st->env_content);
}

void	expand_dollar_sec_h(t_str *st, t_token **tks)
{
	if (st->s == NULL || st->s[0] == '\0')
	{
//		printf("000\n");
		if (st->prev != NULL)
		{
			st->prev->next = (*tks)->next;
			ft_lstdelone_tok(*tks);
			*tks = st->prev;
		}
		else
		{
			(*tks) = (*tks)->next;
			ft_lstdelone_tok(st->first);
			st->first = NULL;
		}
//		printf("aa\n");
	}
	else
	{
		free((*tks)->token);
		(*tks)->token = st->s;
		take_out_quotes(&((*tks)->token), \
			st->deleted_quotes_until, st->i_before_dollar, &(st->i));
		st->deleted_quotes_until = st->i;
	}
}

void	expand_dollar_first_h(t_str *st, t_token **tks, char **env)
{
	st->s = (*tks)->token;
	st->deleted_quotes_until = 0;
	st->quotes_open = 0;
	take_out_quotes(&((*tks)->token), 0, -2, &(st->i));//serve solo ad azzerare quotes_open
	while (st->s != NULL && st->s[st->i] != '\0')
	{
		while (st->s[st->i] != '$' && st->s[st->i] != '\0')
		{
			check_quotes(st->s, st->i, &(st->quotes_open));
			//printf("i: %d, quotes_open: %d\n", i, quotes_open);
			st->i = st->i + 1;
		}
		if (st->s[st->i] == '$' && st->quotes_open != SINGLE_QUOTES)
		{
			st->i_before_dollar = st->i;
			st->s = expand_dollar_h(st, tks, env);
	//		printf("S: %s\n", st->s);
			expand_dollar_sec_h(st, tks);
		}
		if (st->s != NULL && st->s[st->i] == '$' && \
			st->quotes_open == SINGLE_QUOTES)
			st->i = st->i + 1;
	}
//	printf("S0: %s\n", st->s);
//	printf("((*tks)->token): %s\n", ((*tks)->token));
	if (st->s != NULL)
		take_out_quotes(&((*tks)->token), st->deleted_quotes_until, \
		ft_strlen((*tks)->token), &(st->i));
//	printf("S1: %s\n", st->s);
}

void	expand_dollar(t_token **tks, char **env)
{
/* 	char	*s;
	int		i;
	t_token	*first;
	int		quotes_open;
	int		i_before_$;
	int		deleted_quotes_until;
	t_token	*prev; */
	t_str	st;

	st.prev = NULL;
	st.first = *tks;
	while (*tks)
	{
		st.i = 0;
		if ((*tks)->e_tk_type == NORMAL) //forse si puo anche levare questo if
		{
			expand_dollar_first_h(&st, tks, env);
		}
		st.prev = *tks;
		if (st.first != NULL)
			*tks = (*tks)->next;
		else
			st.first = *tks;
	}
	*tks = st.first;
}
