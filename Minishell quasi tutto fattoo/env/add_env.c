/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:57:16 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/23 17:30:04 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_addenv(char *name, char *value, char ***env)
{
	char	**new_env;
	int		i;
	char	*temp;
	char	*new_var;

	i = 0;
	new_env = NULL;
	new_var = NULL;
	temp = NULL;
	while ((*env)[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*env)[i])
	{
		new_env[i] = ft_strdup((*env)[i]);
		i++;
	}
	if(value == NULL)
		new_var = ft_strdup(name);
	else
		{
			temp = ft_strjoin(name, "=");
			new_var = ft_strjoin(temp, value);
			free(temp);
		}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free_env(*env);
	(*env) = new_env;
	return (new_env);
}
