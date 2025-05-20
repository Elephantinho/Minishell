/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_special_cases.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:55:23 by ale               #+#    #+#             */
/*   Updated: 2025/05/20 19:08:59 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_last_exit_code(char **env)
{
	int		exit_code;

	if (ft_getenv("last_ex_cd", env))
	{
		exit_code = ft_atoi(ft_getenv("last_ex_cd", env));
	}
	else
		exit_code = 0;//se cancellano la variabile ritorno 0(?)
	if (WIFEXITED(exit_code))
	{
		// Child terminated normally
		exit_code = WEXITSTATUS(exit_code);
		return (exit_code); // You can propagate the same exit code
	}
	else if (WIFSIGNALED(exit_code))
	{
		// Child terminated by a signal
		exit_code = WTERMSIG(exit_code);
		return (128 + exit_code);
	}
	else if (WIFSTOPPED(exit_code))
	{
		// Child was stopped (not terminated)
		exit_code = WSTOPSIG(exit_code);
		return (128 + exit_code); // Similar convention
	}
	else if (WIFCONTINUED(exit_code))
	{
		return (0); // No error
	}
	else
	{
		// This should rarely happen
		return (1); // Generic error
	}
}

void	double_dollar_case(t_str *st, char **env)
{
	st->env_content = ft_itoa(0);//boh se riesci capisci come prendere pid senza getpid()
	if (!(st->env_content))
	{
		write(2, "malloc failed\n", 14);
		free_env(env);//da levare credo
		ft_lstclear_tok(&(st->first));
		exit(1);//exit cosi va bene?
	}
	(st->i)++;
//		printf("env_cont1: %s\n", *env_content);
}

void	dollar_qmark_case(t_str *st, char **env)
{
	st->env_content = ft_itoa(get_last_exit_code(env));
	if (!(st->env_content))
	{
		write(2, "malloc failed\n", 14);
		free_env(env);//da levare credo
		ft_lstclear_tok(&(st->first));
		exit(1);//exit cosi va bene?
	}
	(st->i)++;
//	printf("env_cont2: %s\n", *env_content);
}

int	special_cases(t_str *st, char **env)
{
	if (st->s[st->i] == '$' && \
		!(st->prev && st->prev->e_tk_type == HEREDOC))
	{
		double_dollar_case(st, env);
	}
	else if (st->s[st->i] == '?' && \
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
			exit(1);//exit cosi va bene?
		}
		return (0);
	}
	else // messo quest caso strano delle virgolette dopo il $ ma non so se lasciarlo
		st->env_content = NULL;
	return (1);
}
