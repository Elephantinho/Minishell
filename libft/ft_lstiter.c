/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 00:01:57 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/30 19:48:56 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
void funct(void *content)
{
	free(content);
	content = ft_strdup("halo");
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
	ft_lstiter(copy, funct);
	while(copy)
	{
		printf("%s\n",(char *) copy->content);
		copy = copy->next;
	}
}*/
