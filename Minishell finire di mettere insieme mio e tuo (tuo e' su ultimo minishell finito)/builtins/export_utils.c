/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:26:05 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/27 17:09:01 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_without_quotes(char *dst, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] != '\'' && src[i] != '"')
			dst[j++] = src[i];
		i++;
	}
	dst[j] = '\0';
}

char	*form_str(char *str)
{
	int		len;
	char	*clean;

	len = count_clean_length(str);
	clean = malloc(len + 1);
	if (!clean)
		return (NULL);
	copy_without_quotes(clean, str);
	return (clean);
}

void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_env(char **env)
{
	int	i;
	int	sorted;

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

char	**ft_copy_matrix(char **matrix)
{
	int		i;
	char	**copy;

	i = 0;
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
