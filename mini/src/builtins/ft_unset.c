/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:40:51 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:40:53 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**remove_var(char **env, size_t i)
{
	size_t	j;
	char	**new_env;

	j = 0;
	while (env[j])
		j++;
	new_env = ft_calloc(j, sizeof(char *));
	j = 0;
	while (env[j] && j < i)
	{
		new_env[j] = ft_strdup(env[j]);
		j++;
	}
	j++;
	while (env[j])
	{
		new_env[i++] = ft_strdup(env[j]);
		j++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**ft_unset(char **env, char *remove)
{
	size_t	i;
	size_t	j;
	char	**new_env;

	i = 0;
	new_env = copy_env(env);
	while (env[i])
	{
		if (!ft_strncmp(env[i], remove, ft_strlen(remove))
			&& (env[i][ft_strlen(remove)] == '=' || !env[i][ft_strlen(remove)]))
		{
			j = 0;
			while (new_env[j])
				free (new_env[j++]);
			free (new_env);
			new_env = remove_var(env, i);
			return (new_env);
		}
		i++;
	}
	return (new_env);
}
