/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:33:21 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/27 15:33:43 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verify(char *str)
{
	int	i;

	if (!str || !((str[0] >= 'a' && str[0] <= 'z')
			|| (str[0] >= 'A' && str[0] <= 'Z') || str[0] == '_'))
		return (-1);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
			return (-1);
		i++;
	}
	return (0);
}

int	count_clean_length(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			len++;
		i++;
	}
	return (len);
}

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

void	print_export_line(char *var)
{
	char	*equal_pos;
	int		name_len;

	equal_pos = ft_strchr(var, '=');
	write(1, "declare -x ", 11);
	if (equal_pos)
	{
		name_len = equal_pos - var;
		write(1, var, name_len + 1);
		write(1, "\"", 1);
		write(1, equal_pos + 1, ft_strlen(equal_pos + 1));
		write(1, "\"\n", 2);
	}
	else
	{
		write(1, var, ft_strlen(var));
		write(1, "\n", 1);
	}
}
