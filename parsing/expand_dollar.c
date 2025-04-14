/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 01:57:50 by ale               #+#    #+#             */
/*   Updated: 2025/04/14 02:10:59 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *expand_dollar_h(char *s, int i, t_token **tks, char **env)
{
 	int		start;
	char	*env_content;
	char	*temp;
	char	*new_tok;

	/* (void)tks;
	(void) env; */

	if (s[i + 1] == '$')
		return (NULL);//get pid somehow
	else if (s[i + 1] == '?')
		return (NULL);//get_last_errorcode_somehow
	else
	{
		i++;
		start = i;
		while ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') \
				|(s[i] >= '0' && s[i] <= '9') || s[i] == '_' )
			i++;
		if (i <= start)//basta == in teoria
			;//lascia solo $
		else if (i > start)
		{
			//espandi dollaro prendendo da env
			temp = ft_substr(s, start, i - start);
			if (!temp)
			{
				write(2, "malloc failed\n", 14);
			//	free_env(env);//da levare credo
				ft_lstclear_tok(tks);
				exit(1);//exit cosi va bene?
			}
			printf("temp: %s\n", temp);
			env_content = ft_getenv(temp, env);
			printf("env_cont: %s\n", env_content);
			free(temp);
			printf("start: %d   i: %d\n", start, i);
			if (start > 1)
			{
				temp = ft_substr(s, 0, start - 1);
				if (!temp)
				{
					write(2, "malloc failed\n", 14);
				//	free_env(env);//da levare credo
					ft_lstclear_tok(tks);
					exit(1);//exit cosi va bene?
				}
				printf("temp2: %s\n", temp);
				new_tok = ft_strjoin(temp, env_content);
				printf("new_tok: %s\n", new_tok);
				free(temp);
			}
			else
			{
				if (env_content)
				{
					new_tok = ft_strdup(env_content);
					if (!new_tok)
					{
						write(2, "malloc failed\n", 14);
					//	free_env(env);//da levare credo
						ft_lstclear_tok(tks);
						exit(1);//exit cosi va bene?
					}
				}
				else
					new_tok = NULL;
			}
			if (s[i] != '\0')
			{
			temp = ft_substr(s, i, i - ft_strlen(s));
			if (!temp)
			{
				write(2, "malloc failed\n", 14);
			//	free_env(env);//da levare credo
				ft_lstclear_tok(tks);
				exit(1);//exit cosi va bene?
			}
			env_content = ft_strjoin(new_tok, temp);
			free(temp);
			free(new_tok);
			}
			else
				return (new_tok);
			return(env_content);
		}
	}
	return (NULL);
}

void	expand_dollar(t_token **tks, char **env)
{
	char	*s;
	int		i;
	t_token	*tokens;
	//int		is_in_sing_quotes;

	//da gestire ancora che se si aprono le viroglette singole non deve fare i dollari
	//e dento alla funzionona mi sa bisogna aggiungere lì la parte che leva le virgolette
	//sia singole che doppie
	tokens = *tks;
	while (*tks)
	{
		i = 0;
		if ((*tks)->e_tk_type == NORMAL) //forse si puo anche levare questo if
		{
			s = (*tks)->token;
			while(s[i] != '\0')
			{
			while(s[i] != '$' && s[i] != '\0')
				i++;
			if (s[i] == '$')
			{
				s = expand_dollar_h(s, i, tks, env);
				free((*tks)->token);
				(*tks)->token = s;
			}
			i++;
			}
		}
		*tks = (*tks)->next;
	}
	*tks = tokens;
}
