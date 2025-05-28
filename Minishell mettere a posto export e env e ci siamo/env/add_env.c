/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:57:16 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/28 01:08:59 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_addenv(char *name, char *value, char ***env)
{
	char	**new_env;
	int		i;
	char	*temp;

	i = 0;
	new_env = NULL;
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
	temp = ft_strjoin(name, "=");
	new_env[i] = ft_strjoin(temp, value);
	new_env[i + 1] = NULL;
	free(temp);
	free_env(*env);
	(*env) = new_env;
	return (new_env);
}
