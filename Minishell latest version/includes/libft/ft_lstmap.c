/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:37:08 by ade-ross          #+#    #+#             */
/*   Updated: 2024/11/27 18:06:41 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;

	temp = NULL;
	new = temp;
	while (lst)
	{
		temp = ft_lstnew((*f)(lst->content));
		if (!temp)
			ft_lstclear(&new, (*del));
		else
			ft_lstadd_back(&new, temp);
		lst = lst->next;
	}
	return (new);
}
/*
// forse meglio fare con return(null) nell'if
// che con if else nel while

void *change(void *content)
{
	return(content = "hola");
}

void delete(void *content)
{
	free(content);
}
int	main()
{
	t_list *try = ft_lstnew(ft_strdup("ciaoo"));

	try ->next = ft_lstnew(ft_strdup("uffa"));
	t_list *copy = try;
	while(try)
	{
		printf("%s", (char *)try->content);
		try = try->next;
	}
	copy = ft_lstmap(copy, change, delete);
	while(copy)
	{
		printf("%s",(char *) copy->content);
		copy = copy->next;
	}
}
*/
