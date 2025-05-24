/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:48:25 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/24 23:48:15 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sort_env(char **env)
{
	int	sorted;
	int	i;

	if (!env)
		return ;
	sorted = 0;
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

void	print_export(char **env)
{
	int		i;
	int		j;
	int		flag;
	char	quote;
	char	*str;
	char	**copy;

	i = 0;
	quote = '"';
	if (!env)
		return ;
	str = NULL;
	copy = ft_copy_matrix(env);
	if (!copy)
		return ;
	sort_env(copy);
	while (copy[i])
	{
		if (strncmp(copy[i], "_=", 2) == 0)
		{
			i++;
			continue;
		}
		flag = 0;
		j = 0;
		write(1, "declare -x ", 11);
		while (copy[i][j])
		{
			if (copy[i][j] == '=' && flag == 0)
			{
				write(1, "=", 1);
				write(1, &quote, 1);
				flag = 1;
				j++;
				continue;
			}
			write(1, &copy[i][j], 1);
			j++;
		}
		if (flag)
			write(1, &quote, 1);
		write(1, "\n", 1);
		i++;
	}
	free_mat(copy);
}

// args[0] = "export", args[1..] variabili
// env è puntatore a matrice ambiente (modificabile)
void ft_export(char **args, char ***env)
{
	int i;
	int count;
	char **tmp;
	int j;

	i = 1;
	count = 0;
	if (!args[i])
	{
		print_export(*env);
		return ;
	}

	while (args[i])
	{
		if (verify(args[i]) != 0)
		{
			dprintf(2, "Minishell: export: '%s' : not a valid identifier\n", args[i]);
		}
		else
		{
			count++;
		}
		i++;
	}

	tmp = malloc(sizeof(char *) * (count + 1));
	if (!tmp)
		return ;

	i = 1;
	j = 0;
	while (args[i])
	{
		if (verify(args[i]) == 0)
		{
			tmp[j] = ft_strdup(args[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;

	*env = matrix_join(*env, tmp, (j + (int)(*env ? 0 : 0)));

	free_mat(tmp);
}


