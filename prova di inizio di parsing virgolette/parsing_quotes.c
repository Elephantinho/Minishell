/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:33:16 by ade-ross          #+#    #+#             */
/*   Updated: 2025/03/27 21:29:16 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

struct token_quotes;

enum	token_type_for_quotes
{
	NO_QUOTES,
	DOUBLE_QUOTES,
	SINGLE_QUOTES,
};

typedef struct	s_token_quotes
{
	char	*token;
	int		token_type_for_quotes;
	struct	s_token_quotes next;
}				t_token_quotes;

int	skip_whitespaces(char *s)
{
	//funzione non ancora testata, controlla che
	//siano giusti i whitespaces e che
	//non ce ne siano anche altri da aggiungere (tipo \n ?)
	int	i;

	i = 0;
	while (s[i] == 32 || s[i] == 9 || (s[i] >= 11 && s[i] <= 13))
	{
		i++;
	}
	return (i);
}

void	create_tokens(char *s)
{
	int	i;
	int	token_type;

	token_type = NO_QUOTES;
	while (s[i] != '\0')
	{
		if (s[i] == 39)
		{
			//da creare token con la parte prima a parte se siamo a i = 0
			token_type = SINGLE_QUOTES;
		}
		else if (s[i] == 34)
		{
			//da creare token con la parte prima a parte se siamo a i = 0
			token_type = DOUBLE_QUOTES;
		}
	}
}
