/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:41:51 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:41:57 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parse(t_parse *data)
{
	t_parse	*current;

	if (data)
	{
		current = data;
		while (current)
		{
			if (current->value)
			{
				free (current->value);
				current->value = NULL;
			}
			data = data->next;
			free (current);
			current = NULL;
			current = data;
		}
	}
}
