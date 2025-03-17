/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:42:08 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:42:10 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_env_var(char **env, char *var)
{
	char	**new_env;
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
	return (new_env);
}

char	**update_env_var(char **env, char *var_name, char *value)
{
	char	**temp_env;
	char	**new_env;
	size_t	i;

	temp_env = ft_unset(env, var_name);
	i = 0;
	while (temp_env[i])
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (temp_env[i])
	{
		new_env[i] = ft_strdup(temp_env[i]);
		i++;
	}
	new_env[i] = ft_strdup(value);
	new_env[i + 1] = NULL;
	i = 0;
	while (temp_env[i])
		free (temp_env[i++]);
	free (temp_env);
	return (new_env);
}

char	**copy_env(char **old_env)
{
	char	**new_env;
	size_t	i;

	i = 0;
	while (old_env[i])
		i++;
	new_env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (old_env[i])
	{
		new_env[i] = ft_strdup(old_env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	*ft_getenv(char **env, char *val)
{
	size_t	i;
	char	*var;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], val, ft_strlen(val))
			&& env[i][ft_strlen(val)] == '=')
		{
			var = ft_substr(env[i], (ft_strlen(val) + 1), ft_strlen(env[i]));
			return (var);
		}
		i++;
	}
	return (NULL);
}

t_environ	*init_env(char **envp)
{
	size_t		count;
	t_environ	*env;

	env = malloc(sizeof(t_environ));
	env->exit_stat = 0;
	count = 0;
	while (envp[count])
		count++;
	env->var = ft_calloc(count + 1, sizeof(char *));
	count = 0;
	while (envp[count])
	{
		env->var[count] = ft_strdup(envp[count]);
		count++;
	}
	env->var[count] = NULL;
	return (env);
}
