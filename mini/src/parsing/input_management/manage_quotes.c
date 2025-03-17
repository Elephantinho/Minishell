/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:42:19 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:42:20 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_closed_quotes(char *input)
{
	int	i;
	int	j;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			j = i;
			while (input[++j])
			{
				if (input[j] == input[i])
				{
					i = j;
					break ;
				}
			}
			if (!input[j])
			{
				ft_putstr_fd("ERROR: Quotes must be closed\n", 2);
				return (0);
			}
		}
	}
	return (1);
}

char	*check_quotes(char *input, size_t *len)
{
	size_t	i;

	i = 1;
	while (input[i] && (input[i] != *input))
		i++;
	input += (i + 1);
	*(len) += (i + 1);
	return (input);
}

static size_t	count_len(char *value)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	count = 0;
	while (value[i])
	{
		if (value[i] == '\"' || value[i] == '\'')
		{
			j = i;
			while (value[++j] != value[i])
				count++;
			i = j;
		}
		else
			count++;
		i++;
	}
	return (count);
}

void	remove_quotes(t_parse *data)
{
	size_t	i;
	size_t	j;
	size_t	x;
	char	*str;

	str = ft_calloc((count_len(data->value) + 1), sizeof(char));
	i = 0;
	x = 0;
	while (data->value[i])
	{
		if (data->value[i] == '\"' || data->value[i] == '\'')
		{
			j = i;
			while (data->value[++j] != data->value[i])
				str[x++] = data->value[j];
			i = j;
		}
		else
			str[x++] = data->value[i];
		i++;
	}
	free (data->value);
	data->value = ft_strdup(str);
	free (str);
}
