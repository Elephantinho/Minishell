/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_out_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:33:36 by ale               #+#    #+#             */
/*   Updated: 2025/04/20 19:18:06 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	take_out_quotes_h(char **new_tk, int *i, int *len, int *end_of_doll_st)
{
	int	j;

	j = *i - 1;
	while ((*new_tk)[++j] != '\0')
		(*new_tk)[j] = (*new_tk)[j + 1];
	*len = *len -1;
	*end_of_doll_st = *end_of_doll_st - 1;
	*i = *i - 1;
}

void	take_out_quotes(char **new_tok, int i, int len, int *end_of_doll_st)
{
	static int	quotes_open = 0;

	if (len == -2)
	{
		quotes_open = 0;
		return ;
	}
	while ((*new_tok) != NULL && (*new_tok)[i] != '\0' && i < len)
	{
		check_quotes(*new_tok, i, &quotes_open);
		if (((*new_tok)[i] == 39) && quotes_open != 2)
		{
			take_out_quotes_h(new_tok, &i, &len, end_of_doll_st);
		}
		else if (((*new_tok)[i] == 34) && quotes_open != 1)
		{
			take_out_quotes_h(new_tok, &i, &len, end_of_doll_st);
		}
		i++;
	}
}
