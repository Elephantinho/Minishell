/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambig_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:19:30 by ale               #+#    #+#             */
/*   Updated: 2025/05/21 23:26:19 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_ambig_redirect_h(char *s, int i, t_token **tks, char **env)
{
	while ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') \
			|(s[i] >= '0' && s[i] <= '9') || s[i] == '_' )
		i++;
	if (i > 1 && s[i] == '\0')
	{
		s = ft_substr(s, 1, i - 1);
		if (!s)
		{
			write(2, "malloc failed\n", 14);
			free_env(env);
			ft_lstclear_tok(tks);
			close_basic_fds_and_exit(1);//exit cosi va bene?
		}
		if (!ft_getenv(s, env))
		{
			write(2, "minishell: $", 12);
			write(2, s, i - 1);
			write(2, ": ambiguos redirect\n", 20);
			free_env(env);
			free(s);
			ft_lstclear_tok(tks);
			close_basic_fds_and_exit(1);//exit cosi va bene?
		}
		free(s);
	}
}

void	check_ambig_redirect(t_token **tks, char **env)
{
	char	*s;
	int		i;
	t_token	*tokens;
	int		prev_is_redirect;

	i = 0;
	tokens = *tks;
	prev_is_redirect = 0;
	while (tokens)
	{
		if (tokens->e_tk_type >= PIPE && tokens->e_tk_type <= APPEND)
			prev_is_redirect = 1;
		else if (tokens->e_tk_type == NORMAL && prev_is_redirect == 1)
		{
			s = tokens->token;
			if (s[0] == '$' && s[1] != '\0' && s[1] != '$' && s[1] != '?')
			{
				i++;
				check_ambig_redirect_h(s, i, tks, env);
			}
		}
		tokens = tokens->next;
	}
}
