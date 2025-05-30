/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_h.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:00:37 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/29 16:53:06 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_mat(char **mat)
{
	int	i;

	i = 0;
	if (!mat)
		return ;
	while (mat[i])
		free(mat[i++]);
	free(mat);
}

void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	print_export_var(char *var)
{
	char	*equal_pos;
	int		name_len;

	equal_pos = ft_strchr(var, '=');
	if (equal_pos)
	{
		name_len = equal_pos - var;
		write(1, var, name_len);
		write(1, "=\"", 2);
		write(1, equal_pos + 1, ft_strlen(equal_pos + 1));
		write(1, "\"\n", 2);
	}
	else
	{
		write(1, var, ft_strlen(var));
		write(1, "\n", 1);
	}
}

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
		write(1, "declare -x ", 11);
		print_export_var(copy[i]);
		i++;
	}
	free_mat(copy);
}
