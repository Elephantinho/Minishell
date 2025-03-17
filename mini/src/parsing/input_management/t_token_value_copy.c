/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_value_copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:22:57 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:42:43 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path_loop(char **dir, char *value, char **path_env)
{
	size_t	i;

	if (value && !*value)
	{
		free(*(path_env));
		*(path_env) = ft_strdup("\0");
		return (*(path_env));
	}
	i = 0;
	while (dir[i])
	{
		if (check_path_access(dir[i], value))
		{
			free(*(path_env));
			*(path_env) = ft_strjoin(dir[i], "/");
			*(path_env) = ft_freejoin(*(path_env), value);
			break ;
		}
		i++;
	}
	return (*(path_env));
}

static char	*find_path(t_token *tok, char **value)
{
	char	*path_env;
	char	**dir;
	int		i;

	path_env = ft_getenv(tok->env->var, "PATH");
	if (!ft_strncmp(*(value), "./", 2) || !path_env)
	{
		free (path_env);
		path_env = ft_strdup(*(value));
		free (*(value));
		return (path_env);
	}
	dir = ft_split(path_env, ':');
	path_env = ft_freelcopy(&path_env, *(value), ft_strlen(*(value)));
	path_env = find_path_loop(dir, *(value), &path_env);
	i = 0;
	while (dir[i])
		free (dir[i++]);
	free (dir);
	free (*(value));
	return (path_env);
}

static void	*expand_exit_stat(t_parse *data, t_token *tok)
{
	int		i;
	char	*str;
	char	*temp;
	char	*temp2;

	str = ft_strdup(data->value);
	i = -1;
	while (str[++i] && data->type != T_QUOTE)
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			temp = ft_substr(str, 0, i);
			temp2 = ft_itoa(tok->env->exit_stat);
			temp = ft_freejoin(temp, temp2);
			free (temp2);
			temp2 = ft_substr(str, (i + 2), ft_strlen(str));
			temp = ft_freejoin(temp, temp2);
			free (temp2);
			free (str);
			str = ft_strdup(temp);
			free (temp);
			i = -1;
		}
	}
	return (str);
}

size_t	get_tok(t_parse *data, t_token *new_tok, t_redir *rd, size_t i)
{
	if (data && (data->type >= T_GENERAL && data->type <= T_COMMAND))
	{
		if (data->value)
		{
			new_tok->value[i] = expand_exit_stat(data, new_tok);
			if (i == 0 && data->type != T_BUILTIN)
				new_tok->value[i] = find_path(new_tok, &new_tok->value[i]);
			i++;
		}
	}
	else if (data && (data->type >= T_RED_IN && data->type <= T_DELIM))
		manage_new_rd(rd, data, new_tok);
	return (i);
}

size_t	first_tok_copy(t_parse *data, t_token *tok, t_redir *rd, size_t i)
{
	if (data && (data->type >= T_GENERAL && data->type <= T_COMMAND))
	{
		if (data->value)
		{
			tok->value[i] = expand_exit_stat(data, tok);
			if (i == 0 && data->type != T_BUILTIN)
				tok->value[i] = find_path(tok, &(tok->value[i]));
			i++;
		}
	}
	else if (data && (data->type >= T_RED_IN && data->type <= T_DELIM))
		manage_new_rd(rd, data, tok);
	return (i);
}
