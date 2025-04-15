/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 01:57:50 by ale               #+#    #+#             */
/*   Updated: 2025/04/16 00:08:25 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_code;

int	handle_$qmark(void)
{
	int		exit_code;

	if (WIFEXITED(error_code)) {
		// Child terminated normally
		exit_code = WEXITSTATUS(error_code);
		return exit_code; // You can propagate the same exit code
	}
	else if (WIFSIGNALED(error_code)) {
		// Child terminated by a signal
		exit_code = WTERMSIG(error_code);
		return (128 + exit_code);
	}
	else if (WIFSTOPPED(error_code)) {
		// Child was stopped (not terminated)
		exit_code = WSTOPSIG(error_code);
		return (128 + exit_code); // Similar convention
	}
	else if (WIFCONTINUED(error_code)) {
		return 0; // No error
	}
	else {
		// This should rarely happen
		return 1; // Generic error
}
}

void	take_out_quotes(char **new_tok, int	i, int len, int *end_of_$string)
{
	static int	quotes_open = 0;
	int	j;

	if (len == -2)
	{
		quotes_open = 0;
		return ;
	}
	printf("len: %d\n", len);
	while ((*new_tok) != NULL && (*new_tok)[i] != '\0' && i < len)
	{
		check_quotes(*new_tok, i, &quotes_open);
		j = i - 1;
		//printf("000(*new_tok)[i]: %c i: %d, quotes_open: %d\n", (*new_tok)[i], i, quotes_open);
		if (((*new_tok)[i] == 39) && quotes_open != 2)
		{
			while ((*new_tok)[++j] != '\0')
				(*new_tok)[j] = (*new_tok)[j + 1];
			len--;
			*end_of_$string = *end_of_$string - 1;
			i--;
		}
		else if (((*new_tok)[i] == 34) && quotes_open != 1)
		{
			while ((*new_tok)[++j] != '\0')
				(*new_tok)[j] = (*new_tok)[j + 1];
			len--;
			*end_of_$string = *end_of_$string - 1;
			i--;
		}
		i++;
	//	printf("(*new_tok)[i]: %c i: %d, quotes_open: %d\n", (*new_tok)[i], i, quotes_open);
	}
}

char *expand_dollar_h(char *s, int *i, t_token **tks, char **env)
{
 	int		start;
	char	*env_content;
	char	*temp;
	char	*new_tok;

	/* (void)tks;
	(void) env; */


	(*i)++;
	start = *i;
	while ((s[*i] >= 'a' && s[*i] <= 'z') || (s[*i] >= 'A' && s[*i] <= 'Z') \
			|| (s[*i] >= '0' && s[*i] <= '9') || s[*i] == '_' )
		(*i)++;
//	printf("start: %d   i: %d\n", start, *i);
	if (*i <= start)//basta == in teoria
	{
		if (s[*i] == '$')
		{
			env_content = ft_itoa(getpid());
			if (!env_content)
			{
				write(2, "malloc failed\n", 14);
			//	free_env(env);//da levare credo
				ft_lstclear_tok(tks);
				exit(1);//exit cosi va bene?
			}
			(*i)++;
			printf("env_cont1: %s\n", env_content);
		}
		else if (s[*i] == '?')
		{
			env_content = ft_itoa(handle_$qmark());
			if (!env_content)
			{
				write(2, "malloc failed\n", 14);
				ft_lstclear_tok(tks);
				exit(1);//exit cosi va bene?
			}
			(*i)++;
			printf("env_cont2: %s\n", env_content);
		}
		else
		{
			new_tok = ft_strdup(s);
			if (!new_tok)
			{
				write(2, "malloc failed\n", 14);
				ft_lstclear_tok(tks);
				exit(1);//exit cosi va bene?
			}
			return (new_tok);
		}
	}
	else if (*i > start)
	{
		temp = ft_substr(s, start, *i - start);
		if (!temp)
		{
			write(2, "malloc failed\n", 14);
			ft_lstclear_tok(tks);
			exit(1);//exit cosi va bene?
		}
		printf("temp: %s\n", temp);
		env_content = ft_getenv(temp, env);
		free(temp);
		if (env_content)
		{
			env_content = ft_strdup(env_content);
			if (!env_content)
			{
				write(2, "malloc failed\n", 14);
				ft_lstclear_tok(tks);
				exit(1);//exit cosi va bene?
			}
		}
		printf("env_cont: %s\n", env_content);
	}
	printf("start: %d   i: %d\n", start, *i);
		if (start > 1)
		{
			temp = ft_substr(s, 0, start - 1);
			if (!temp)
			{
				free(env_content); //credo ci vada
				write(2, "malloc failed\n", 14);
			//	free_env(env);//da levare credo
				ft_lstclear_tok(tks);
				exit(1);//exit cosi va bene?
			}
			printf("temp2: %s\n", temp);
			new_tok = ft_strjoin(temp, env_content);
			printf("new_tok: %s\n", new_tok);
			free(env_content);
			free(temp);
		//	take_out_quotes(&new_tok);
			printf("new_tok1: %s\n", new_tok);
		}
		else
		{
			new_tok = env_content;
		}
		if (s[*i] != '\0')
		{
			temp = ft_substr(s, *i, *i - ft_strlen(s));
			if (!temp)
			{
				write(2, "malloc failed\n", 14);
			//	free_env(env);//da levare credo
				ft_lstclear_tok(tks);
				exit(1);//exit cosi va bene?
			}
		env_content = ft_strjoin(new_tok, temp);
		free(temp);
		*i = ft_strlen(new_tok);
		free(new_tok);
	//	take_out_quotes(&env_content);
		}
		else
			return ((*i = ft_strlen(new_tok)), new_tok);
		printf("FINenv_cont: %s\n", env_content);
		return(env_content);

	return (NULL);
}

void	expand_dollar(t_token **tks, char **env)
{
	char	*s;
	int		i;
	t_token	*start;
	int		quotes_open;
	int		i_before_$;
	int		deleted_quotes_until;
	t_token	*prev;
	//da gestire ancora che se si aprono le viroglette singole non deve fare i dollari
	//e dento alla funzionona mi sa bisogna aggiungere lì la parte che leva le virgolette
	//sia singole che doppie
	prev = NULL;
	start = *tks;
	while (*tks)
	{
		i = 0;
		if ((*tks)->e_tk_type == NORMAL) //forse si puo anche levare questo if
		{
			s = (*tks)->token;
			deleted_quotes_until = 0;
			quotes_open = 0;
			take_out_quotes(&((*tks)->token), 0, -2, &i);//serve solo ad azzerare quotes_open
			while(s != NULL && s[i] != '\0')
			{
				while(s[i] != '$' && s[i] != '\0')
				{
					check_quotes(s, i, &quotes_open);
					//printf("i: %d, quotes_open: %d\n", i, quotes_open);
					i++;
				}
				if (s[i] == '$' && quotes_open != SINGLE_QUOTES)
				{
					i_before_$ = i;
					s = expand_dollar_h(s, &i, tks, env);
					printf("S: %s\n", s);
					if (s == NULL || s[0] == '\0')
					{
						printf("000\n");
						if (prev != NULL)
						{
							prev->next = (*tks)->next;
							ft_lstdelone_tok(*tks);
							*tks = prev;
						}
						else
						{
							(*tks) = (*tks)->next;
							ft_lstdelone_tok(start);
							start = NULL;
						}
						printf("aa\n");
					}
					else
					{
						free((*tks)->token);
						(*tks)->token = s;
						take_out_quotes(&((*tks)->token), deleted_quotes_until, i_before_$, &i);
						deleted_quotes_until = i;
					}
				}
				if (s != NULL && s[i] == '$' && quotes_open == SINGLE_QUOTES)
					i++;
			}
			printf("S0: %s\n", s);
		//	printf("((*tks)->token): %s\n", ((*tks)->token));
			if (s != NULL)
				take_out_quotes(&((*tks)->token), deleted_quotes_until, ft_strlen((*tks)->token), &i);
			printf("S1: %s\n", s);
		}
		prev = *tks;
		if (start != NULL)
			*tks = (*tks)->next;
		else
			start = *tks;
	}
	*tks = start;
}

