/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:40:04 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:40:06 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**null_var(char **env, char *var_name)
{
	size_t	i;
	char	**new_env;

	i = 0;
	new_env = copy_env(env);
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, ft_strlen(var_name))
			&& !env[i][ft_strlen(var_name)])
			return (new_env);
		i++;
	}
	i = 0;
	while (new_env[i])
		free (new_env[i++]);
	free (new_env);
	new_env = add_env_var(env, var_name);
	return (new_env);
}

static char	**value_var(char **env, char *var, char *var_name)
{
	size_t	i;
	char	**new_env;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, ft_strlen(var_name))
			&& (env[i][ft_strlen(var_name)] == '='
			|| !env[i][ft_strlen(var_name)]))
		{
			new_env = update_env_var(env, var_name, var);
			return (new_env);
		}
		i++;
	}
	new_env = add_env_var(env, var);
	return (new_env);
}

char	**export_var(char **env, char *var)
{
	size_t	i;
	char	*var_name;
	char	**new_env;

	if (!valid_var_name(var))
		return (NULL);
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	var_name = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (var[i] && var[i] != '=')
	{
		var_name[i] = var[i];
		i++;
	}
	if (var[i] == '=')
		new_env = value_var(env, var, var_name);
	else
		new_env = null_var(env, var_name);
	free (var_name);
	return (new_env);
}

int	ft_export(t_token *data, int fd)
{
	char	**new_env;
	size_t	i;
	size_t	j;

	if (!data->value[1])
	{
		print_export_env(data->env->var, fd);
		return (1);
	}
	i = 1;
	while (data->value[i])
	{
		new_env = export_var(data->env->var, data->value[i++]);
		if (!new_env)
			return (0);
		free_environment(data->env, 0);
		data->env->var = copy_env(new_env);
		j = 0;
		while (new_env[j])
			free (new_env[j++]);
		free (new_env);
	}
	return (1);
}
