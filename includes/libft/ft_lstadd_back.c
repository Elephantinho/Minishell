/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 23:17:46 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/27 00:16:33 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == 0 || new == 0)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}
/*
int	main()
{
	t_list	* l;
	t_list	*l1;
	t_list	* l2;

	l = ft_lstnew(ft_strdup("mamma"));
	l1 = ft_lstnew(ft_strdup("miaa"));
	ft_lstadd_back(&l, l1);
	l2 = l->next;
	printf("%s",(char *) l->content);
	printf("%s",(char *) l->next->content);
	printf("%s",(char *) l2->content);
}*/
