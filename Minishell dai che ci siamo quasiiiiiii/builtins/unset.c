/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:37:04 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/24 21:09:01 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**build_new_env(char **env, char **args)
{
	int		i;
	int		j;
	int		new_size;
	char	**new_env;

	new_size = count_new_env_size(env, args);
	new_env = malloc(sizeof(char *) * (new_size + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (!should_remove_var(env[i], args))
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env[j])
			{
				while (j-- > 0)
					free(new_env[j]);
				free(new_env);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

void	print_invalid_identifiers(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			write(2, "Minishell: unset: `", 20);
			j = 0;
			while (args[i][j])
				write(2, &args[i][j++], 1);
			write(2, "`: not a valid identifier\n", 28);
		}
		i++;
	}
}

void	ft_unset(char **args, char ***env)
{
	char	**new_env;

	if (!args || !args[1])
		return ;
	print_invalid_identifiers(args);
	new_env = build_new_env(*env, args);
	if (!new_env)
		return ;
	free_mat(*env);
	*env = new_env;
}
