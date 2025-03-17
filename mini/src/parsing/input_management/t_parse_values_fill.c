/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_parse_values_fill.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:43:43 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 17:45:00 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_len(char *input)
{
	size_t	len;

	len = 0;
	if (!check_closed_quotes(input))
		return (0);
	while (*input && (*input != ' ' && *input != '\n' && *input != '\t'
			&& *input != '|' && *input != '<' && *input != '>'))
	{
		if (*input == '\"' || *input == '\'')
			input = check_quotes(input, &len);
		else
		{
			len++;
			input++;
		}
	}
	if (len == 0 && (*input == '|' || *input == '<' || *input == '>'))
	{
		len = 1;
		if ((*input == '<' && *(input + 1) == '<')
			|| (*input == '>' && *(input + 1) == '>'))
			len = 2;
	}
	return (len);
}

static int	get_values(t_parse *data, char *input)
{
	t_parse	*new_element;
	size_t	size;

	while (input && *input)
	{
		while (*input && (*input == ' ' || *input == '\t' || *input == '\n'))
			input++;
		if (!*input)
			break ;
		new_element = malloc (sizeof(t_parse));
		size = token_len(input);
		new_element->value = ft_stringlcopy(new_element->value, input, size);
		new_element->type = T_GENERAL;
		data->next = new_element;
		data = data->next;
		if (!size)
		{
			data->next = NULL;
			return (0);
		}
		input += size;
	}
	data->next = NULL;
	return (1);
}

static char	*first_value(t_parse *data, char *input)
{
	size_t	size;

	size = token_len(input);
	if (!size)
		return (NULL);
	data->value = ft_stringlcopy(data->value, input, size);
	data->type = T_GENERAL;
	data->next = NULL;
	return (input + size);
}

int	fill_t_parse_values(char *input, t_parse *data, t_token *tok)
{
	while (*input && (*input == ' ' || *input == '\t' || *input == '\n'))
		input++;
	if (input)
		input = first_value(data, input);
	if (!input)
	{
		tok->env->exit_stat = 1;
		return (0);
	}
	if (input && *input)
	{
		if (!get_values(data, input))
		{
			tok->env->exit_stat = 1;
			return (0);
		}
	}
	return (1);
}
