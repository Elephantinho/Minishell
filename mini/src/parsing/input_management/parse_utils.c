/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:42:25 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:42:27 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_var(t_parse *data, t_token *tok, size_t i)
{
	char	*str;
	char	*var_val;

	str = ft_substr(data->value, i, ft_strlen(data->value));
	var_val = expand_var(tok, str);
	free (str);
	str = ft_substr(data->value, 0, (i - 1));
	if (var_val)
	{
		str = ft_freejoin(str, var_val);
		free (var_val);
	}
	while (data->value[i] && (ft_isalnum(data->value[i])
			|| data->value[i] == '_'))
		i++;
	var_val = ft_substr(data->value, i, ft_strlen(data->value));
	str = ft_freejoin(str, var_val);
	free (var_val);
	free (data->value);
	data->value = ft_strdup(str);
	free (str);
}

void	manage_new_rd(t_redir *rd, t_parse *data, t_token *tok)
{
	t_redir	*new_rd;

	while (rd->next)
		rd = rd->next;
	if (rd && rd->name)
	{
		new_rd = malloc(sizeof(t_redir));
		new_rd->type = data->type;
		new_rd->name = ft_strdup(data->next->value);
		rd->next = new_rd;
		rd = rd->next;
		rd->next = NULL;
		tok->nredir++;
	}
	else
	{
		rd->type = data->type;
		rd->name = ft_strdup(data->next->value);
		rd->next = NULL;
		tok->nredir++;
	}
}
