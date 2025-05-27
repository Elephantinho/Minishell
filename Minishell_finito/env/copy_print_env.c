/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_print_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:55:39 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/27 15:38:49 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

int	copy_env_entries(char **dst, char **src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			while (i >= 0)
				free(dst[i--]);
			return (0);
		}
		i++;
	}
	dst[i] = NULL;
	return (1);
}

char	**copy_env(char **envp)
{
	char	**env;
	int		size;

	if (!envp)
		return (NULL);
	size = count_env_size(envp);
	env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env)
		return (NULL);
	if (!copy_env_entries(env, envp))
	{
		free(env);
		return (NULL);
	}
	return (env);
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
}
