/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_special_cases.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:55:23 by ale               #+#    #+#             */
/*   Updated: 2025/05/24 22:58:53 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_last_exit_code(char **env)
{
	int		exit_code;

	if (ft_getenv("last_ex_cd", env))
		exit_code = ft_atoi(ft_getenv("last_ex_cd", env));
	else
		exit_code = 0;
	if (WIFEXITED(exit_code))
	{
		exit_code = WEXITSTATUS(exit_code);
		return (exit_code);
	}
	else if (WIFSIGNALED(exit_code))
	{
		exit_code = WTERMSIG(exit_code);
		return (128 + exit_code);
	}
	else if (WIFSTOPPED(exit_code))
	{
		exit_code = WSTOPSIG(exit_code);
		return (128 + exit_code);
	}
	else if (WIFCONTINUED(exit_code))
		return (0);
	else
		return (1);
}

void	double_dollar_case(t_str *st, char **env)
{
	st->env_content = ft_itoa(0);
	if (!(st->env_content))
	{
		write(2, "malloc failed\n", 14);
		free_env(env);
		ft_lstclear_tok(&(st->first));
		close_basic_fds_and_exit(1);
	}
	(st->i)++;
}

void	dollar_qmark_case(t_str *st, char **env)
{
	st->env_content = ft_itoa(get_last_exit_code(env));
	if (!(st->env_content))
	{
		write(2, "malloc failed\n", 14);
		free_env(env);
		ft_lstclear_tok(&(st->first));
		close_basic_fds_and_exit(1);
	}
	(st->i)++;
}

int	special_cases(t_str *st, char **env)
{
	if (st->s[st->i] == '?' && \
		!(st->prev && st->prev->e_tk_type == HEREDOC))
	{
		dollar_qmark_case(st, env);
	}
	else if (st->s[st->i] != '"' && st->s[st->i] != '\'')
	{
		st->new_tok = ft_strdup(st->s);
		if (!(st->new_tok))
		{
			write(2, "malloc failed\n", 14);
			free_env(env);
			ft_lstclear_tok(&(st->first));
			close_basic_fds_and_exit(1);
		}
		return (0);
	}
	else
		st->env_content = NULL;
	return (1);
}
/* if (st->s[st->i] == '$' && \
		!(st->prev && st->prev->e_tk_type == HEREDOC))
	{
		double_dollar_case(st, env);
	}
	else  */
