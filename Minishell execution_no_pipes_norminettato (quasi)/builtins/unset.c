/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:37:04 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/26 17:36:09 by mshahein         ###   ########.fr       */
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
	//int	len;

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
			write(2, "`: not a valid identifier\n", 27);
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
	free_env(*env);
	*env = new_env;
}



