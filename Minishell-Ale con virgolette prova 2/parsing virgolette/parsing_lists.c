/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lists.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:33:48 by ale               #+#    #+#             */
/*   Updated: 2025/04/07 15:34:37 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token_quotes	*ft_lstlast_quotes(t_token_quotes *lst)
{
	if (lst == 0)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

t_token_quotes	*ft_lstnew_quotes(void *content, int token_type)
{
	t_token_quotes	*new;

	new = malloc(sizeof(t_token_quotes));
	if (new == 0)
		return (NULL);
	new->next = NULL;
	new->token = content;
	new->e_token_type_for_quotes = token_type;
	return (new);
}

void	ft_lstadd_back_quotes(t_token_quotes **lst, t_token_quotes *new)
{
	t_token_quotes	*last;

	if (lst == 0 || new == 0)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast_quotes(*lst);
	last->next = new;
}

void	ft_lstclear_quotes(t_token_quotes **lst)
{
	t_token_quotes	*temp;

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
