/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vari.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:13:36 by ale               #+#    #+#             */
/*   Updated: 2025/05/10 17:32:21 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_lstclear_tok_mod(t_token **lst)
{
	t_token	*temp;

	if (lst == 0)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
	*lst = 0;
}

void	free_cmnds(char **cmnds)
{//forse non serve piu perche era per arr of matrx credo
	//un po' TESTATA da vedere sia giusta
	if (cmnds)
	{
		int i = 0;
		while (cmnds[i])
		{
			/* while(cmnds[i][j])
			{
				free(cmnds[i][j]);
				j++;
			} */
			free(cmnds[i]);
			i++;
		}
		free(cmnds); // Libera l'array degli argomenti
	}
}

/* void	arr_of_matrx_h_free(t_token **tokens, t_token **first, \
	char ****arr_of_matrx)
{
	free_cmnds(*arr_of_matrx);
	ft_lstclear_tok(&(*tokens)->next);
	(*tokens)->next = NULL;
	free((*tokens)->token);
	ft_lstclear_tok_mod(first);
} */
/*
void	arr_of_matrx_free(char *s, char **env)
{
	free_env(env);
	if (s)
		free(s);
	write(2, "malloc failed\n", 14);
	exit(1);
} */
