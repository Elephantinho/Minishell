/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:58:47 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/24 21:00:07 by mshahein         ###   ########.fr       */
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
	int	len;

	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]) && !is_duplicate(args, i))
		{
			len = ft_strlen(args[i]);
			if (match_env_var(env_var, args[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

int	count_new_env_size(char **env, char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (env[i])
	{
		if (!should_remove_var(env[i], args))
			count++;
		i++;
	}
	return (count);
}
