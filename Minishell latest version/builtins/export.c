/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:48:25 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/07 22:54:39 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export(char **args, char ***env)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	if (!args[1])
	{
		print_env(*env);
		return ;
	}
	while (args[++i])
	{
		if (ft_strchr(args[i], '='))
		{
			name = ft_substr(args[i], 0, ft_strchr(args[i], '=') - args[i]);
			value = ft_strchr(args[i], '=') + 1;
			if (ft_getenv(name, *env))
				ft_setenv(name, value, env);
			else
				*env = ft_addenv(name, value, env);
			free(name);
		}
	}
}

int	verify(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (ft_isdigit(str[0]))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	verify_only_equal(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
