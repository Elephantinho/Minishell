/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_print_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:55:39 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/23 16:12:01 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**copy_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	env = NULL;
	if (!envp)
		return (NULL);
	while (envp[i])
		i++;
	env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			while (i >= 0)
				free(env[i--]);
			free(env);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	print_env(char **env)
{
	int		i = 0;
	char	*equal_pos;

	while (env[i])
	{
		equal_pos = ft_strchr(env[i], '=');
		if (equal_pos && *(equal_pos + 1) != '\0')
			ft_putendl_fd(env[i], 1);
		i++;
	}
}
