/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:00:31 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/29 16:32:22 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verify(char *str)
{
	int	i;

	if (!str || !((str[0] >= 'a' && str[0] <= 'z') \
		|| (str[0] >= 'A' && str[0] <= 'Z') || str[0] == '_'))
		return (-1);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') \
			|| (str[i] >= 'A' && str[i] <= 'Z') \
			|| (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
			return (-1);
		i++;
	}
	return (0);
}

void	form_str_h(char *str, int *len)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			(*len)++;
		i++;
	}
}

char	*form_str(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*clean;

	i = 0;
	j = 0;
	len = 0;
	form_str_h(str, &len);
	clean = malloc(len + 1);
	if (!clean)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			clean[j++] = str[i];
		i++;
	}
	clean[j] = '\0';
	return (clean);
}

void	sort_env(char **env)
{
	int	i;
	int	sorted;

	i = 0;
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
