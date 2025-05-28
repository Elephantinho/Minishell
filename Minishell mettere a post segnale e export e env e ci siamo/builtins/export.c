/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:33:20 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/26 21:55:15 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_export(char **env)
{
	int		i;
	char	**copy;

	i = 0;
	copy = ft_copy_matrix(env);
	if (!copy)
		return ;
	sort_env(copy);
	while (copy[i])
	{
		print_export_line(copy[i]);
		i++;
	}
	free_mat(copy);
}

void	print_export_error(char *arg)
{
	write(2, "Minishell: export: `", 21);
	write(2, arg, ft_strlen(arg));
	write(2, "`: not a valid identifier\n", 27);
}

void	handle_assignment(char *arg, char ***env)
{
	char	*value;
	char	*cleaned;
	char	*name;

	name = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	value = ft_strchr(arg, '=') + 1;
	cleaned = form_str(value);
	if (!name || !cleaned)
		return ;
	if (ft_getenv(name, *env))
		ft_setenv(name, cleaned, env);
	else
		ft_addenv(name, cleaned, env);
	free(name);
	free(cleaned);
}

void	handle_no_assignment(char *arg, char ***env)
{
	if (!ft_getenv(arg, *env))
		ft_addenv(arg, "", env);
}

void	ft_export(char **args, char ***env)
{
	int	i;

	i = 0;
	if (!args[1])
	{
		print_export(*env);
		return ;
	}
	while (args[i])
	{
		if (verify(args[i]) == 0)
		{
			if (ft_strchr(args[i], '='))
				handle_assignment(args[i], env);
			else
				handle_no_assignment(args[i], env);
		}
		else
			print_export_error(args[i]);
		i++;
	}
}
