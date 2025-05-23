/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:12:05 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/23 17:28:36 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getenv(char *name, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	ft_setenv(char *name, char *value, char ***env)
{
	int		i;
	int		len;
	char	*new_env;
	char	*temp;

	i = 0;
	len = ft_strlen(name);
	new_env = NULL;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], name, len) && (*env)[i][len] == '=')
		{
			free((*env)[i]);
			if (value == NULL)
				new_env = ft_strdup(name);
			else
			{
				temp = ft_strjoin(name, "=");
				temp = new_env;
				new_env = ft_strjoin(new_env, value);
				free(temp);
				(*env)[i] = new_env;
			}
			return ;
		}
		i++;
	}
}
