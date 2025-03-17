/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_parse_types_fill.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:23:04 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:42:32 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_if_var(t_parse *data, t_token *tok)
{
	size_t	i;

	i = 0;
	if ((!data || !data->value) || data->type == T_QUOTE)
		return (0);
	while (data->value[i])
	{
		if (data->value[i] == '$')
		{
			if ((data->value[i + 1] && data->value[i + 1] == '?'))
				data->type = T_EXIT_STAT;
			else if (!data->value[i + 1])
				return (0);
			else
			{
				manage_var(data, tok, i + 1);
				i = 0;
			}
		}
		i++;
	}
	return (0);
}

static int	check_if_command(t_token *tok, char *value)
{
	char	*path_env;
	char	**dir;
	size_t	i;
	size_t	found;

	path_env = ft_getenv(tok->env->var, "PATH");
	if (!path_env)
		return (0);
	found = 0;
	dir = ft_split(path_env, ':');
	free(path_env);
	i = 0;
	while (dir[i])
	{
		if (check_path_access(dir[i++], value))
		{
			found = 1;
			break ;
		}
	}
	i = 0;
	while (dir[i])
		free (dir[i++]);
	free (dir);
	return (found);
}

int	check_if_builtin(char *value)
{
	const char	**builtins;
	size_t		i;

	builtins = malloc(sizeof(char *) * 8);
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	i = 0;
	while (builtins[i] && value)
	{
		if (!ft_strcmp(value, builtins[i++]))
		{
			free (builtins);
			return (1);
		}
	}
	free (builtins);
	return (0);
}

static int	check_if_quote(t_parse *data)
{
	if (data->value[0] == '\'')
		data->type = T_QUOTE;
	else if (data->value[0] == '\"')
		data->type = T_DQUOTE;
	else if (data->next && data->value[0] == '<')
	{
		if (data->value[1] == '<')
			data->type = T_DELIM;
		else
			data->type = T_RED_IN;
	}
	else if (data->next && data->value[0] == '>')
	{
		if (data->value[1] == '>')
			data->type = T_RED_APPEN;
		else
			data->type = T_RED_OUT;
	}
	if (data->type == T_GENERAL)
		return (0);
	else if (data->next && (data->type >= T_RED_IN && data->type <= T_DELIM))
		data->next->type = T_LIM;
	return (1);
}

int	fill_t_parse_types(t_parse *data, t_token *tok)
{
	if (!data->value)
		return (0);
	while (data)
	{
		if (!check_if_quote(data))
		{
			if (check_if_builtin(data->value))
				data->type = T_BUILTIN;
			else if (check_if_command(tok, data->value))
				data->type = T_COMMAND;
			else if (data->value[0] == '|' && !data->value[1])
				data->type = T_PIPE;
		}
		if (check_if_var(data, tok))
			data->type = T_VAR;
		remove_quotes(data);
		if (!data->value)
			return (0);
		data = data->next;
		if (data && data->type != T_GENERAL)
			data = data->next;
	}
	return (1);
}
