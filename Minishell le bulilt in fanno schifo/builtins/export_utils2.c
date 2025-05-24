/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:02:46 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/24 21:06:58 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	append_or_replace(char **matrix, char *arg)
{
	int	pos;

	pos = exisit(matrix, arg);
	if (pos != -1)
	{
		free(matrix[pos]);
		matrix[pos] = strdup(arg);
		return (1);
	}
	return (0);
}

char	**matrix_join(char **env, char **args, int new_size)
{
	int		i;
	int		j;
	int		k;
	char	**new;

	i = 0;
	j = 0;
	k = 0;
	new = malloc(sizeof(char *) * (new_size + 1));
	if (!new)
		return (NULL);
	while (k <= new_size)
	{
		new[k] = NULL;
		k++;
	}
	k = 0;
	while (env && env[i])
	{
		new[k] = strdup(env[i]);
		i++;
		k++;
	}
	j = 0;
	while (args[j])
	{
		if (!append_or_replace(new, args[j]))
		{
			new[k] = strdup(args[j]);
			k++;
		}
		j++;
	}
	new[k] = NULL;
	free_mat(env);
	return (new);
}

void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
