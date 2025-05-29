/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:57:16 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/29 17:02:53 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*create_new_env_entry(char *name, char *value)
{
	char	*temp;
	char	*new_var;

	if (value == NULL)
		return (ft_strdup(name));
	temp = ft_strjoin(name, "=");
	new_var = ft_strjoin(temp, value);
	free(temp);
	return (new_var);
}

char	**ft_addenv(char *name, char *value, char ***env)
{
	char	**new_env;
	int		i;
	char	*new_var;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while ((*env)[i])
	{
		new_env[i] = ft_strdup((*env)[i]);
		i++;
	}
	new_var = create_new_env_entry(name, value);
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free_env(*env);
	(*env) = new_env;
	return (new_env);
}
