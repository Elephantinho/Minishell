/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:01:29 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/24 23:47:11 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int verify(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (-1);
	if (!((str[i] >= 'a' && str[i] <= 'z') ||
		(str[i] >= 'A' && str[i] <= 'Z') ||
		str[i] == '_'))
		return (-1);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') ||
			(str[i] >= 'A' && str[i] <= 'Z') ||
			(str[i] >= '0' && str[i] <= '9') ||
			str[i] == '_' ||
			str[i] == '"' ||
			str[i] == '\''))
			return (-1);
		i++;
	}
	return (0);
}

int exisit(char **env, char *arg)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	while (env && env[i])
	{
		if (strncmp(env[i], arg, len) == 0 &&
			(env[i][len] == '=' || env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

void free_mat(char **mat)
{
	int i;

	i = 0;
	if (!mat)
		return ;
	while (mat[i])
	{
		free(mat[i]);
		i++;
	}
	free(mat);
}

char **ft_copy_matrix(char **matrix)
{
	int i;
	char **copy;

	i = 0;
	if (!matrix)
		return (NULL);
	while (matrix[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		copy[i] = strdup(matrix[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
