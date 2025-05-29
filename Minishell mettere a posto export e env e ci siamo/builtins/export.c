/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:12:23 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/29 16:56:48 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export_hh(char *args, char ***env)
{
	char	*name;
	char	*value;
	char	*cleaned;

	if (ft_strchr(args, '='))
	{
		name = ft_substr(args, 0, ft_strchr(args, '=') - args);
		value = ft_strchr(args, '=') + 1;
		cleaned = form_str(value);
		if (ft_getenv(name, *env))
			ft_setenv(name, cleaned, env);
		else
			ft_addenv(name, cleaned, env);
		free(name);
		free(cleaned);
	}
	else
	{
		if (!ft_getenv(args, *env))
			ft_addenv(args, NULL, env);
	}
}

void	ft_export_h(char *args)
{
	write(2, "Minishell: export: `", 21);
	write(2, args, ft_strlen(args));
	write(2, "`: not a valid identifier\n", 27);
}

void	ft_export(char **args, char ***env)
{
	int		i;

	if (!args[1])
	{
		print_export(*env);
		return ;
	}
	i = 1;
	while (args[i])
	{
		if (verify(args[i]) == 0)
			ft_export_hh(args[i], env);
		else
			ft_export_h(args[i]);
		i++;
	}
}
