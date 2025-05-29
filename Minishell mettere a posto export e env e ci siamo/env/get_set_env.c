/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:12:05 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/29 15:44:10 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		len;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len) &&
			(env[i][len] == '=' || env[i][len] == '\0'))
		{
			if (env[i][len] == '=')
				return (env[i] + len + 1);
			else
				return ("");
		}
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
		if ((!ft_strncmp((*env)[i], name, len)) &&
			((*env)[i][len] == '=' || (*env)[i][len] == '\0'))
		{
			free((*env)[i]);
			if (value == NULL)
				(*env)[i] = ft_strdup(name);
			else
			{
				temp = ft_strjoin(name, "=");
				(*env)[i] = ft_strjoin(temp, value);
				free(temp);
			}
			return ;
		}
		i++;
	}
}

