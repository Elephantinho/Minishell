/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_from_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:58:26 by ale               #+#    #+#             */
/*   Updated: 2025/05/21 23:23:15 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_variable_from_env(t_str *st, char **env, char *temp)
{
	temp = ft_substr(st->s, st->start, st->i - st->start);
	if (!temp)
	{
		write(2, "malloc failed\n", 14);
		if (st->new_tok)
				free(st->new_tok);
		free_env(env);
		ft_lstclear_tok(&(st->first));
		close_basic_fds_and_exit(1);
	}
	st->env_content = ft_getenv(temp, env);
	free(temp);
	if (st->env_content)
	{
		st->env_content = ft_strdup(st->env_content);
		if (!(st->env_content))
		{
			write(2, "malloc failed\n", 14);
			if (st->new_tok)
				free(st->new_tok);
			free_env(env);
			ft_lstclear_tok(&(st->first));
			close_basic_fds_and_exit(1);//exit cosi va bene?
		}
	}
}

void	get_part_before_the_dollar(t_str *st, char **env)
{
	char	*temp;

	if (st->start > 1)
	{
		temp = ft_substr(st->s, 0, st->start - 1);
		if (!temp)
		{
			free(st->env_content);
			write(2, "malloc failed\n", 14);
			free_env(env);
			ft_lstclear_tok(&(st->first));
			close_basic_fds_and_exit(1);//exit cosi va bene?
		}
		st->new_tok = ft_strjoin(temp, st->env_content);
//		printf("*new_tok: %s\n", *new_tok);
		free(st->env_content);
		free(temp);
	}
	else
	{
		st->new_tok = st->env_content;
	}
}

int	get_part_after_the_dollar(t_str *st, char **env, char *temp)
{
	if (st->s[st->i] != '\0')
	{
		temp = ft_substr(st->s, st->i, st->i - ft_strlen(st->s));
		if (!temp)
		{
			write(2, "malloc failed\n", 14);
			free_env(env);
			if (st->new_tok)
				free(st->new_tok);
			ft_lstclear_tok(&(st->first));
			close_basic_fds_and_exit(1);//exit cosi va bene?
		}
		st->env_content = ft_strjoin(st->new_tok, temp);
		free(temp);
		st->i = ft_strlen(st->new_tok);
		free(st->new_tok);
	}
	else
	{
		st->i = ft_strlen(st->new_tok);
		return (1);
	}
	return (0);
}

char	*expand_dollar_h(t_str *st, char **env)
{
	st->i = st->i + 1;
	st->start = st->i;
	st->new_tok = NULL;
	while ((st->s[st->i] >= 'a' && st->s[st->i] <= 'z') || \
			(st->s[st->i] >= 'A' && st->s[st->i] <= 'Z') || \
			(st->s[st->i] >= '0' && st->s[st->i] <= '9') || \
			st->s[st->i] == '_' )
		(st->i)++;
//	printf("start: %d   i: %d\n", start, st->i);
	if (st->i <= st->start  || (st->prev && st->prev->e_tk_type == HEREDOC)) //basta == in teoria
	{
		if (special_cases(st, env) == 0)
			return (st->new_tok);
	}
	else if (st->i > st->start)
	{
		get_variable_from_env(st, env, NULL);
	}
	get_part_before_the_dollar(st, env);
	if (get_part_after_the_dollar(st, env, NULL) == 1)
		return (st->new_tok);
	return (st->env_content);
}
