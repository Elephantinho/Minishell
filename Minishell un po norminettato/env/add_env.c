/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:57:16 by mshahein          #+#    #+#             */
/*   Updated: 2025/03/22 20:23:36 by ade-ross         ###   ########.fr       */
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
	(*env) = new_env;
	return (new_env);
}
