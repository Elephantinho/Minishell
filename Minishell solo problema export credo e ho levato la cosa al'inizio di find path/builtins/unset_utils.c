/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:11:51 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/26 21:24:13 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (!(ft_isalpha(str[i]) || str[i] == '_'))
		return (0);
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	match_env_var(char *env_var, char *name)
{
	int	i;

	i = 0;
	while (name[i] && env_var[i] && name[i] == env_var[i])
		i++;
	if (name[i] == '\0' && (env_var[i] == '=' || env_var[i] == '\0'))
		return (1);
	return (0);
}

int	is_duplicate(char **args, int index)
{
	int	i;

	i = 1;
	while (i < index)
	{
		if (ft_strcmp(args[i], args[index]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	should_remove_var(char *env_var, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]) && !is_duplicate(args, i))
		{
			if (match_env_var(env_var, args[i]))
				return (1);
		}
		i++;
	}
	return (0);
}
