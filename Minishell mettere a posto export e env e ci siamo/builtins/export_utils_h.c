/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_h.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:00:37 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/29 16:28:25 by mshahein         ###   ########.fr       */
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
