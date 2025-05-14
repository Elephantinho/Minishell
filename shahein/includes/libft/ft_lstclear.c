/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 23:35:00 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/30 19:56:37 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (lst == 0 || del == 0)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = 0;
}
/*
void funct(void *content)
{
	free(content);
}
int	main()
{
	t_list	*uno;
	t_list	*due;
	t_list	*tre;

	uno = ft_lstnew(ft_strdup("ciao"));
	due = ft_lstnew(ft_strdup("cio"));
	uno->next = due;
	tre = ft_lstnew(ft_strdup("ci"));
	due->next = tre;
	tre->next = NULL;
	t_list *copy = uno;
	while(uno)
	{
		printf("%s\n",(char *) uno->content);
		uno = uno->next;
	}
	ft_lstclear(&copy, funct);
	while(copy)
	{
		printf("%s\n",(char *) copy->content);
		copy = copy->next;
	}
} */
