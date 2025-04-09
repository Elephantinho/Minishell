/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 21:31:52 by ale               #+#    #+#             */
/*   Updated: 2025/04/08 21:37:07 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft/get_next_line_bonus.h"

enum	e_quotes_type
{
	NO_QUOTES,
	SINGLE_QUOTES,
	DOUBLE_QUOTES,
};

void			update_token_type(int *token_type, int quotes_type);
int				init_tok_type(char *s);
int				init_start(int tok_type);
void			oth_update_token_type(int *tok_type, char *s, int i, \
				int *start);
