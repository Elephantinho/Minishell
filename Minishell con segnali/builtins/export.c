/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:48:25 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/20 22:07:44 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verify(char *str)
{
	int	i;

	if (!str || !((str[0] >= 'a' && str[0] <= 'z') ||
		(str[0] >= 'A' && str[0] <= 'Z') || str[0] == '_'))
		return (-1);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') ||
			(str[i] >= 'A' && str[i] <= 'Z') ||
			(str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
			return (-1);
		i++;
	}
	return (0);
}

char	*form_str(char *str)
{
	int		i = 0, j = 0, len = 0;
	char	*clean;

	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			len++;
		i++;
	}
	clean = malloc(len + 1);
	if (!clean)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			clean[j++] = str[i];
		i++;
	}
	clean[j] = '\0';
	return (clean);
}

void	swap(char **a, char **b)
{
	char *tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_env(char **env)
{
	int	i;
	int	sorted = 0;

	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (env[i] && env[i + 1])
		{
			if (ft_strcmp(env[i], env[i + 1]) > 0)
			{
				swap(&env[i], &env[i + 1]);
				sorted = 0;
			}
			i++;
		}
	}
}

char	**ft_copy_matrix(char **matrix)
{
	int		i = 0;
	char	**copy;

	while (matrix[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		copy[i] = ft_strdup(matrix[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	free_mat(char **mat)
{
	int	i = 0;

	if (!mat)
		return ;
	while (mat[i])
		free(mat[i++]);
	free(mat);
}

void	print_export(char **env)
{
	int		i = 0;
	char	*equal_pos;
	char	**copy = ft_copy_matrix(env);

	if (!copy)
		return ;
	sort_env(copy);
	while (copy[i])
	{
		write(1, "declare -x ", 12);
		equal_pos = ft_strchr(copy[i], '=');
		if (equal_pos)
		{
			int name_len = equal_pos - copy[i];
			write(1, copy[i], name_len + 1); // VAR=
			write(1, "\"", 1);
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
					ft_addenv(args[i], "", env);
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
