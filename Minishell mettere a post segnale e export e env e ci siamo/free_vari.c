/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vari.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:13:36 by ale               #+#    #+#             */
/*   Updated: 2025/05/27 20:29:05 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// void	ft_lstclear_mod_arr_lst(t_token **arr_of_lists)
// {
// 	int		i;
// 	//t_token	*temp;
// 	i = 0;
// 	/* if (!arr_of_lists || *arr_of_lists)
// 		return ; */
// 		printf("aaa\n");
// 		int j = 0;
// 		while(arr_of_lists[j] != NULL)
// 	{
// 		printf("listaaabbb %d\n", j);
// 		printf("str%d: (%s)\n", j, (char *)((arr_of_lists[j])->token));
// 		//ft_lstsiter_tok(arr_of_lists[j], prnt);
// 		j++;
// 	}
// 		//printf("(arr_of_lists): %s\n", ((arr_of_lists))->token);
// 	/* while ((arr_of_lists)[i])
// 	{printf("bbb\n");
// 		while ((arr_of_lists)[i])
// 		{
// 			temp = ((arr_of_lists))[i]->next;
// 			free((arr_of_lists)[i]);
// 			(arr_of_lists)[i] = temp;
// 		}
// 		i++;
// 	}
// 	free(arr_of_lists); */
// }
void	close_basic_fds_and_exit(int exit_code)
{
	close(0);
	close(1);
	close(2);
	exit(exit_code);
}

void	ft_lstclear_tok_mod(t_token **lst)
{
	t_token	*temp;

	if (lst == NULL)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void	free_cmnds(char ***cmnds)
{
	int	i;

	if (*cmnds)
	{
		i = 0;
		while ((*cmnds)[i])
		{
			free((*cmnds)[i]);
			i++;
		}
		free(*cmnds);
	}
	*cmnds = NULL;
}

void	free_for_exit_no_pipes(char ***args, char **env, t_exec_no_pipes *st)
{
	//if (st->s)
	//	free(st->s);
	free_cmnds(args);
	free_env(env);
	close_fds_for_exit_no_pipes(st);
}

void	free_for_exit(char ***args, t_token **arr_of_lists, char **env)
{
	free_cmnds(args);
	free_env(env);
	free(arr_of_lists);
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
