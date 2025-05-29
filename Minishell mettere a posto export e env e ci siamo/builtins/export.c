/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:12:23 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/29 16:15:26 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_export(char **env)
{
	int		i;
	char	*equal_pos;
	char	**copy;
	int		name_len;

	i = 0;
	copy = ft_copy_matrix(env);
	if (!copy)
		return ;
	sort_env(copy);
	while (copy[i])
	{
		write(1, "declare -x ", 11);
		equal_pos = ft_strchr(copy[i], '=');
		if (equal_pos)
		{
			name_len = equal_pos - copy[i];
			write(1, copy[i], name_len);
			write(1, "=\"", 2);
			write(1, equal_pos + 1, ft_strlen(equal_pos + 1));
			write(1, "\"\n", 2);
		}
		else
		{
			write(1, copy[i], ft_strlen(copy[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	free_mat(copy);
}

void	ft_export(char **args, char ***env)
{
	int		i;
	char	*name;
	char	*value;
	char	*cleaned;

	if (!args[1])
	{
		print_export(*env);
		return ;
	}
	i = 1;
	while (args[i])
	{
		if (verify(args[i]) == 0)
		{
			if (ft_strchr(args[i], '='))
			{
				name = ft_substr(args[i], 0, ft_strchr(args[i], '=') - args[i]);
				value = ft_strchr(args[i], '=') + 1;
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
				if (!ft_getenv(args[i], *env))
					ft_addenv(args[i], NULL, env);
			}
		}
		else
		{
			write(2, "Minishell: export: `", 21);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "`: not a valid identifier\n", 27);
		}
		i++;
	}
}
