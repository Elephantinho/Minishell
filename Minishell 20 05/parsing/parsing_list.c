/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:48:49 by ale               #+#    #+#             */
/*   Updated: 2025/04/15 19:05:33 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*ft_lstlast_tok(t_token *lst)
{
	if (lst == 0)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

t_token	*ft_lstnew_tok(void *content, int token_type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == 0)
		return (NULL);
	new->next = NULL;
	new->token = content;
	new->e_tk_type = token_type;
	return (new);
}

void	ft_lstadd_back_tok(t_token **lst, t_token *new)
{
	t_token	*last;

	if (lst == 0 || new == 0)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast_tok(*lst);
	last->next = new;
}

void	ft_lstclear_tok(t_token **lst)
{
	t_token	*temp;

	if (lst == 0)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->token);
		free(*lst);
		*lst = temp;
	}
	*lst = 0;
}

void	ft_lstdelone_tok(t_token *lst)
{
	if (lst == 0)
		return ;
	free(lst->token);
	free(lst);
}
