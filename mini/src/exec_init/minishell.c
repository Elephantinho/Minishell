/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:40:43 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:41:01 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*init_token(t_token *tok, t_environ *env)
{
	tok = malloc(sizeof(t_token));
	tok->value = NULL;
	tok->env = env;
	tok->rd = NULL;
	tok->nredir = 0;
	tok->next = NULL;
	return (tok);
}

static t_parse	*init_data(t_parse *data)
{
	data = malloc(sizeof(t_parse));
	data->value = NULL;
	data->next = NULL;
	return (data);
}

static int	main_loop(t_parse *data, t_token *tok, char **envp)
{
	char		*input;
	t_environ	*env;

	env = init_env(envp);
	while (1)
	{
		tok = init_token(tok, env);
		input = prompt_init(tok);
		if (input && *input)
		{
			data = init_data(data);
			add_history(input);
			if (input_parse(&input, data, tok))
				do_command(tok);
		}
		else if (!input)
		{
			rl_clear_history();
			free_all(NULL, tok, env, &input);
			return (1);
		}
		free (input);
		free_token(tok);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_parse	*data;
	t_token	*tok;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	data = NULL;
	tok = NULL;
	if (!main_loop(data, tok, envp))
		return (1);
	return (0);
}
