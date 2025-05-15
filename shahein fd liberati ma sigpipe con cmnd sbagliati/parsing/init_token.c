/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:38:22 by ale               #+#    #+#             */
/*   Updated: 2025/04/07 15:42:02 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//if we were inside quotes updates the token type
//to show we are now out of the quotes(NO_QUOTES)
//otherwise updates token type to show we are inside the quotes
void	update_token_type(int *token_type, int quotes_type)
{
	if (*token_type == quotes_type)
		*token_type = NO_QUOTES;
	else
		*token_type = quotes_type;
}

int	init_tok_type(char *s)
{
	if (s[0] == 39)
		return (SINGLE_QUOTES);
	else if (s[0] == 34)
		return (DOUBLE_QUOTES);
	else
		return (NO_QUOTES);
}

int	init_start(int tok_type)
{
	if (tok_type == SINGLE_QUOTES || tok_type == DOUBLE_QUOTES)
		return (1);
	else
		return (0);
}

void	oth_update_token_type(int *tok_type, char *s, int i, int *start)
{
	if (s[i] == 39)
		*tok_type = SINGLE_QUOTES;
	else if (s[i] == 34)
		*tok_type = DOUBLE_QUOTES;
	*start = i + 1;
}
