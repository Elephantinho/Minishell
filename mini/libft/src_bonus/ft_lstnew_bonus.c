/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:19:01 by mchiaram          #+#    #+#             */
/*   Updated: 2023/11/03 19:19:56 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = (t_list *) malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}

/*void	del(void *element)
{
	free(element);
}

void	print_list(t_list *head)
{
	while (head)
	{
		printf("%d\n", *(int *)(head->content));
		head = head->next;
	}
}

void	*lstmap_function(void *content)
{
	int	*n;

	n = (int *)content;
	*n -= 10;
	return (content);
}

void	lstiter_function(void *content)
{
	int	*n;

	n = (int *)content;
	*n += 10;
}

int	main(void)
{
	int		*n;
	int		i;
	t_list	*head;
	t_list	*new_element;
	t_list	*temp;
	t_list	*prev;
	
	i = 0;;
	head = NULL;
	while (i < 5)
	{
		n = malloc(sizeof(i) * 1);
		*n = i;
		new_element = ft_lstnew(n);
		ft_lstadd_back(&head, new_element);
		*n = i++;
	}
	printf("List:\n");
	print_list(head);
	printf("List of %d elements\n\n", ft_lstsize(head));
	i = 42;
	n = malloc(sizeof(i) * 1);
	*n = i;
	new_element = ft_lstnew(n);
	ft_lstadd_front(&head, new_element);
	printf("Added '%d' to the front of the list:\n", i);
	print_list(head);
	printf("List of %d elements\n\n", ft_lstsize(head));
	i = 3;
	temp = head;
	if (temp && *(int *)(temp->content) == i)
	{
		head = temp->next;
		ft_lstdelone(temp, del);
		printf("Deleted %i from the list\n", i);
	}
	else
	{
		while (temp && *(int *)(temp->content) != i)
		{
			prev = temp;
			temp = temp->next;
		}
		if (!temp)
			printf("value not found inside the list\n");
		else
		{
			prev->next = temp->next;
			ft_lstdelone(temp, del);
			printf("Deleted %i from the list\n", i);
		}
	}
	print_list(head);
	printf("List of %d elements\n\n", ft_lstsize(head));
	i = 0;
	temp = head;
	if (temp && *(int *)(temp->content) == i)
	{
		ft_lstclear(&temp, del);
		head = NULL;
		printf("Deleted from the element %i of the list\n", i);
	}
	else
	{
		while (temp && *(int *)(temp->content) != i)
		{
			prev = temp;
			temp = temp->next;
		}
		if (!temp)
			printf("value not found inside the list\n");
		else
		{
			ft_lstclear(&temp, del);
			prev->next = NULL;
			printf("Deleted from the element %i of the list\n", i);
		}
	}
	print_list(head);
	printf("List of %d elements\n\n", ft_lstsize(head));
	ft_lstiter(head, lstiter_function);
	printf("Added 10 to each element of the list\n");
	print_list(head);
	ft_lstmap(head, lstmap_function, del);
	printf("\nDecreased each element by 10\n");
	print_list(head);
	return (0);
}*/

/*				---MAN DESCRIPTION---

	Allocates (with malloc(3)) and returns a new node.
	The member variable ’content’ is initialized with
	the value of the parameter ’content’. The variable
	’next’ is initialized to NULL.

	---RETURN VALUE---
	The new node
*/